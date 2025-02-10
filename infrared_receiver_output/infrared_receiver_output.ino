#include <IRremote.h> // Include the IRremote library

#define RECV_PIN 7 // Set the IR receiver pin

void setup() {
  Serial.begin(9600); // Start the serial monitor
  Serial.println("Press any button"); // Print a message to the serial monitor
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) { // Check if a signal is received
    Serial.print("HEX: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print the HEX value
    Serial.print("DEC: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData); // Print the decimal value
    IrReceiver.resume(); // Prepare for the next signal
  }
}
