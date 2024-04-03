const int stepPin1 = 2; // Outer Shaft
const int dirPin1 = 5; // Outer Shaft

const int stepPin2 = 3; // Inner Shaft
const int dirPin2 = 6; // Inner Shaft

unsigned long start, finished, elapsed;

// Define variables for controlling rotation speed
const unsigned long targetRotationTime = 60000; // Target rotation time in milliseconds (1 minute)
const int stepsPerRevolution = 200; // Number of steps per full revolution
unsigned long stepDelay = targetRotationTime / stepsPerRevolution; // Calculate delay between steps

void setup(void) {
    pinMode(stepPin1, OUTPUT); // Outer Shaft
    pinMode(dirPin1, OUTPUT); // Outer Shaft
    pinMode(stepPin2, OUTPUT); // Inner Shaft
    pinMode(dirPin2, OUTPUT); // Inner Shaft
    // We'll send debugging information via the Serial monitor
    Serial.begin(9600);
    Serial.println("start");
}

void loop(void) {
  start=millis();
    // Set the direction of rotation
    digitalWrite(dirPin1, LOW); // or LOW for opposite direction
    digitalWrite(dirPin2, LOW); // or LOW for opposite direction
    
    // Generate steps to move the stepper motor
    for (int i = 0; i < 40; i++) {
        digitalWrite(stepPin1, HIGH); // Outer Shaft
        digitalWrite(stepPin2, HIGH); // Inner Shaft
        delay(1125); // Ensure a minimum pulse width (adjust as needed)
        digitalWrite(stepPin1, LOW); // Outer Shaft
        digitalWrite(stepPin2, LOW); // Inner Shaft
        delay(1125); // Adjust this delay for the desired rotation speed
    }
    
// delay(1000);
    // Optional: Send debugging information via Serial
    // Serial.println("Completed 360 degrees rotation in 1 minute");

    // millis

  finished=millis();
  elapsed=finished-start;
  Serial.print(elapsed);
  Serial.println(" milliseconds elapsed");
  Serial.println();
}
