#include <IRremote.h> // Include the IRremote library

#define RECV_PIN 7    // Pin for the IR receiver
#define RED_LED 6     // Pin for the red LED (supports PWM)
#define WHITE_LED 10  // Pin for the white LED (supports PWM)
#define GREEN_LED 9   // Pin for the green LED (supports PWM)

// Define the HEX codes for each button
#define OFF 0xE916FF00       // Button 0 (OFF)
#define RED 0xF30CFF00       // Button 1 (RED)
#define WHITE 0xE718FF00     // Button 2 (WHITE)
#define GREEN 0xA15EFF00     // Button 3 (GREEN)
#define ALL_ON 0xF708FF00    // Button 4 (ALL ON)
#define CHRISTMAS 0xE31CFF00 // Button 5 (CHRISTMAS mode)
#define BLINK 0xA55AFF00     // Button 6 (BLINK mode)
#define FADE 0xBD42FF00      // Button 7 (FADE mode)
#define UP 0xF609FF00        // UP arrow (increase speed)
#define DOWN 0xF807FF00      // DOWN arrow (decrease speed)

int activeMode = -1;      // Tracks the current mode (-1 = no active mode)
String currentAction = ""; // Description of the current action
String pastAction = "";    // Description of the previous action

// Speed settings for Fade and Blink modes
int fadeSpeed = 30;        // Initial speed for Fade mode (ms per step)
int blinkSpeed = 500;      // Initial speed for Blink mode (ms per state change)
const int minSpeed = 10;   // Minimum speed (lower bound for delay)
const int maxSpeed = 1000; // Maximum speed (upper bound for delay)

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(9600);
  Serial.println("Waiting for remote signals...");
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Initialize the IR receiver
}

void loop() {
  if (IrReceiver.decode()) 
  {
    unsigned long command = IrReceiver.decodedIRData.decodedRawData;

    // Map the command to the corresponding button
    String buttonPressed = getButtonName(command);

    // Adjust speed for Fade and Blink modes
    if (command == UP) {
      pastAction = currentAction;
      increaseSpeed();
      currentAction = "Increased speed";
      printAction(buttonPressed);
      IrReceiver.resume();
      return;
    } else if (command == DOWN) {
      pastAction = currentAction;
      decreaseSpeed();
      currentAction = "Decreased speed";
      printAction(buttonPressed);
      IrReceiver.resume();
      return;
    }

    // Check if the same mode is selected
    if (getModeFromCommand(command) == activeMode) {
      stopActiveMode();
      activeMode = -1;
      currentAction = "Stopped active mode";
      printAction(buttonPressed);
      IrReceiver.resume();
      return;
    }

    // If an unknown command is received, keep the current mode
    if (getModeFromCommand(command) == -1) {
      currentAction = "Unknown command received, maintaining current mode";
      printAction(buttonPressed);
      IrReceiver.resume();
      return;
    }

    // Stop the current mode before switching to a new one
    stopActiveMode();

    // Activate the new mode based on the received command
    pastAction = currentAction;
    activeMode = getModeFromCommand(command);
    switch (activeMode) {
      case 0:
        currentAction = "Turned OFF all LEDs";
        turnOffAll();
        break;
      case 1:
        currentAction = "Turned ON Red LED";
        turnOnRed();
        break;
      case 2:
        currentAction = "Turned ON White LED";
        turnOnWhite();
        break;
      case 3:
        currentAction = "Turned ON Green LED";
        turnOnGreen();
        break;
      case 4:
        currentAction = "Turned ON all LEDs";
        turnOnAll();
        break;
      case 5:
        currentAction = "Activated Christmas Mode";
        break;
      case 6:
        currentAction = "Activated Blink Mode";
        break;
      case 7:
        currentAction = "Activated Fade Mode";
        break;
      default:
        currentAction = "Unknown command";
        break;
    }

    printAction(buttonPressed);
    IrReceiver.resume(); // Prepare the receiver for the next signal
  }

  // Execute the active mode
  if (activeMode == 5) {
    christmasMode();
  } else if (activeMode == 6) {
    blinkMode();
  } else if (activeMode == 7) {
    fadeMode();
  }
}


void printAction(String buttonPressed) {
  Serial.print("Command: ");
  Serial.println(buttonPressed);
  Serial.print("Previous Action: ");
  Serial.println(pastAction);
  Serial.print("Current Action: ");
  Serial.println(currentAction);

  if (activeMode == 6) { // Blink mode
    Serial.print("Blink Speed: ");
    Serial.print(blinkSpeed);
    Serial.print(" ms (Min: ");
    Serial.print(minSpeed);
    Serial.print(" ms, Max: ");
    Serial.print(maxSpeed);
    Serial.println(" ms)");
  } else if (activeMode == 7) { // Fade mode
    Serial.print("Fade Speed: ");
    Serial.print(fadeSpeed);
    Serial.print(" ms (Min: ");
    Serial.print(minSpeed);
    Serial.print(" ms, Max: ");
    Serial.print(maxSpeed);
    Serial.println(" ms)");
  }

  Serial.println("------------------------");
}

String getButtonName(unsigned long command) {
  switch (command) {
    case OFF: return "0 (OFF)";
    case RED: return "1 (Red)";
    case WHITE: return "2 (White)";
    case GREEN: return "3 (Green)";
    case ALL_ON: return "4 (All On)";
    case CHRISTMAS: return "5 (Christmas Mode)";
    case BLINK: return "6 (Blink Mode)";
    case FADE: return "7 (Fade Mode)";
    case UP: return "UP (Increase Speed)";
    case DOWN: return "DOWN (Decrease Speed)";
    default: return "Unknown";
  }
}

// Map a command to its corresponding mode
int getModeFromCommand(unsigned long command) {
  switch (command) {
    case OFF: return 0;
    case RED: return 1;
    case WHITE: return 2;
    case GREEN: return 3;
    case ALL_ON: return 4;
    case CHRISTMAS: return 5;
    case BLINK: return 6;
    case FADE: return 7;
    default: return -1;
  }
}

void stopActiveMode() {
  analogWrite(RED_LED, 0);
  analogWrite(WHITE_LED, 0);
  analogWrite(GREEN_LED, 0);
}

void turnOffAll() { analogWrite(RED_LED, 0); analogWrite(WHITE_LED, 0); analogWrite(GREEN_LED, 0); }
void turnOnRed() { analogWrite(RED_LED, 255); analogWrite(WHITE_LED, 0); analogWrite(GREEN_LED, 0); }
void turnOnWhite() { analogWrite(RED_LED, 0); analogWrite(WHITE_LED, 255); analogWrite(GREEN_LED, 0); }
void turnOnGreen() { analogWrite(RED_LED, 0); analogWrite(WHITE_LED, 0); analogWrite(GREEN_LED, 255); }
void turnOnAll() { analogWrite(RED_LED, 255); analogWrite(WHITE_LED, 255); analogWrite(GREEN_LED, 255); }

void christmasMode() {
  static unsigned long lastChange = 0;
  static int step = 0;

  if (millis() - lastChange >= 300) { 
    lastChange = millis();

    switch (step) {
      case 0:
        analogWrite(RED_LED, 255);
        analogWrite(WHITE_LED, 0);
        analogWrite(GREEN_LED, 0);
        break;
      case 1:
        analogWrite(RED_LED, 0);
        analogWrite(WHITE_LED, 255);
        analogWrite(GREEN_LED, 0);
        break;
      case 2:
        analogWrite(RED_LED, 0);
        analogWrite(WHITE_LED, 0);
        analogWrite(GREEN_LED, 255);
        break;
    }

    step = (step + 1) % 3;
  }
}

void blinkMode() {
  static unsigned long lastBlink = 0;
  static bool isOn = false;

  if (millis() - lastBlink >= blinkSpeed) {
    lastBlink = millis();
    isOn = !isOn;

    if (isOn) {
      turnOnAll();
    } else {
      turnOffAll();
    }
  }
}

void fadeMode() {
  static int brightness = 0;
  static int step = 5;
  static bool fadingOut = false;

  analogWrite(RED_LED, brightness);
  analogWrite(WHITE_LED, brightness);
  analogWrite(GREEN_LED, brightness);

  brightness += fadingOut ? -step : step;

  if (brightness <= 0 || brightness >= 255) {
    fadingOut = !fadingOut;
  }

  delay(fadeSpeed);
}

void increaseSpeed() {
  if (activeMode == 6 && blinkSpeed > minSpeed) {
    blinkSpeed -= 10;
  } else if (activeMode == 7 && fadeSpeed > minSpeed) {
    fadeSpeed -= 10;
  }
}

void decreaseSpeed() {
  if (activeMode == 6 && blinkSpeed < maxSpeed) {
    blinkSpeed += 10;
  } else if (activeMode == 7 && fadeSpeed < maxSpeed) {
    fadeSpeed += 10;
  }
}
