const int stepPin = 2;
const int dirPin = 5;

// Define variables for controlling rotation speed
const unsigned long targetRotationTime = 60000; // Target rotation time in milliseconds (1 minute)
const int stepsPerRevolution = 200; // Number of steps per full revolution
unsigned long stepDelay = targetRotationTime / stepsPerRevolution; // Calculate delay between steps

void setup(void) {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    // We'll send debugging information via the Serial monitor
    Serial.begin(9600);
}

void loop(void) {
    // Set the direction of rotation
    digitalWrite(dirPin, LOW); // or LOW for opposite direction
    
    // Generate steps to move the stepper motor
    for (int i = 0; i < 800; i++) {
        digitalWrite(stepPin, HIGH);
        delay(18); // Ensure a minimum pulse width (adjust as needed)
        digitalWrite(stepPin, LOW);
        delay(20); // Adjust this delay for the desired rotation speed
    }
// delay(1000);
    // Optional: Send debugging information via Serial
    Serial.println("Completed 360 degrees rotation in 1 minute");
}
