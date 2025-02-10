# Controlling LEDs using an IR Remote and Arduino UNO R3

🎓 School Project<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; This project was developed as part of the Electronic Devices and Analog Electronics course by Lucian Popescu and Anamaria Ciocan, students in Information Engineering,

📌 Project Overview<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; This project demonstrates how to control multiple LEDs using an Arduino UNO R3 and an IR remote. Various lighting modes, including individual LED control, simultaneous illumination, and dynamic effects like blinking and fading, are implemented.

🎯 Features<br />
- Individual LED Control – Toggle Red, White, and Green LEDs independently
- Simultaneous LED Activation – Turn on all LEDs at once
- Christmas Mode – LEDs cycle through colors in a festive sequence
- Blink Mode – LEDs blink at an adjustable speed
- Fade Mode – LEDs smoothly transition brightness levels

🔧 Components Used<br />
- Arduino UNO R3 – Microcontroller to control the circuit<br />
- IR Receiver (VS1838B KY-022) – Detects signals from the IR remote<br />
- IR Remote Control – Sends commands to the Arduino<br />
- LEDs (Red, White, Green) – Display lighting effects<br />
- 220Ω Resistors – Limit current flow<br />
- Breadboard & Jumper Wires – Assemble the circuit<br />

🖥️ Software & Libraries<br />
- Arduino IDE – Used to write and upload code
- IRremote Library – Decodes IR signals from the remote
- Tinkercad – Simulated the circuit before implementation

📌 Circuit Wiring<br />
1. LEDs Wiring<br />
   - Red LED->D6 (PWM)<br />
   - White LED->D10 (PWM)<br />
   - Green LED->D9 (PWM)<br />
   
2. IR Receiver Wiring<br />
   - IR Receiver Signal->D7
   - IR Receiver VCC->5V
   - IR Receiver GND->GND

⚙️ Installation & Usage<br />
1. Assemble the Circuit following the wiring diagram<br />
2. Install the IRremote Library in Arduino IDE<br />
3. Upload the Code to the Arduino UNO R3<br />
4. Use the IR Remote to switch between different LED modes<br />

🚀 Future Improvements<br />
 - Implement Bluetooth control for extended range
 - Add RGB LEDs for more dynamic effects
 - Develop a GUI for easier mode selection

📚 References<br />
- Arduino Official Docs<br />
- IRremote Library<br />
- Tinkercad<br />
