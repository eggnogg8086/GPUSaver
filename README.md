# Description
Intended to be used with an arduino connected to a 240v ac relay to disconnect power when a "shoot-through" vrm failure occurs and mitigate damage to the gpu asic or any untrusted power rail connected to sensitive silicon

the arduino sense pin must be connected to the problematic vrm section after the inductor 

# Future plans:
-Add fast switching and cheap sacrifical mosfet that will short the output to ground for faster reaction time
-Multiple voltage monitoring
-add back temperature sensing, multichannel if possible
-Seperate detector and relay and use 2.4ghz wireless connection for ease of probing/installation
