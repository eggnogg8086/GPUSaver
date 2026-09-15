# Description
Intended to be used with an arduino connected to a 240v ac relay to disconnect power when a "shoot-through" vrm failure occurs and mitigate damage to the gpu asic or any untrusted power rail connected to sensitive silicon

the arduino sense pin must be connected to the problematic vrm section after the inductor 

# Future plans:
<ul>
  <li>Add fast switching and cheap sacrifical mosfet that will short the output to ground for faster reaction time</li>
    <li>Multiple voltage monitoring</li>
    <li>Add back temperature sensing, multichannel if possible </li>
    <li>Seperate detector and relay and use 2.4ghz wireless connection for ease of probing/installation
  </li>
</ul>
