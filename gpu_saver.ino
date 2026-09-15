#define RELAY_PIN 10
#define BUTTON_PIN 11

#define FULL_SCALE 16.0
#define TRIP_VOLTAGE 1.65

const uint16_t tripADC =
    TRIP_VOLTAGE * 1023.0 / FULL_SCALE;

const uint16_t resetADC = 5;      // ~0V

volatile uint16_t adcValue = 0;

enum State {
    IDLE,
    WAIT_FOR_RELAY,
    RUNNING,
    FAULT
};

volatile State state = IDLE;

unsigned long relayStartTime = 0;

void setup()
{
    Serial.begin(115200);

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    digitalWrite(RELAY_PIN, LOW);

    // ---------- ADC ----------
    ADMUX = (1 << REFS0) | 5;          // AVcc, A5
    ADCSRA =
        (1 << ADEN) |
        (1 << ADATE) |
        (1 << ADIE) |
        (1 << ADSC) |
        (1 << ADPS2);                  // prescaler = 16

    ADCSRB = 0;                        // free-running

    sei();
}

ISR(ADC_vect)
{
    adcValue = ADC;

    switch (state)
    {
        case RUNNING:
            if (adcValue > tripADC)
            {
                PORTB &= ~(1 << PB2);      // Relay OFF immediately
                state = FAULT;
            }
            break;

        case FAULT:
            if (adcValue <= resetADC)
            {
                state = IDLE;
            }
            break;

        default:
            break;
    }
}

void loop()
{
    switch (state)
    {
        case IDLE:

            if (digitalRead(BUTTON_PIN) == LOW)
            {
                PORTB |= (1 << PB2);       // Relay ON immediately
                relayStartTime = millis();
                state = WAIT_FOR_RELAY;
            }

            break;

        case WAIT_FOR_RELAY:

            // Wait for relay contacts to physically close
            if (millis() - relayStartTime >= 10)
            {
                state = RUNNING;
            }

            break;

        case RUNNING:
            // Nothing needed.
            // Protection happens inside the ADC interrupt.
            break;

        case FAULT:
            // Wait until ADC interrupt clears the fault.
            break;
    }

    static unsigned long lastPrint = 0;

    if (millis() - lastPrint >= 500)
    {
        lastPrint = millis();

        Serial.print("Voltage: ");
        Serial.print(adcValue * FULL_SCALE / 1023.0, 2);

        Serial.print("  State: ");

        switch (state)
        {
            case IDLE: Serial.println("IDLE"); break;
            case WAIT_FOR_RELAY: Serial.println("WAIT"); break;
            case RUNNING: Serial.println("RUNNING"); break;
            case FAULT: Serial.println("FAULT"); break;
        }
    }
}