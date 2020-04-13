// Includiamo la libreria servo
#include<Servo.h>

// Costanti utili al codice
#define FIRST_PIN 2
#define POS_0 90.
#define MAX_DELTA_DEGREE 90.
#define MAX_MOTORS 12
#define MAX_INPUT 127
#define FIRST_CONTROLLER 22
#define CC_MIDI 176

// Dichiaro i servo motori
Servo servoMotor[MAX_MOTORS];

// Il segnale midi è composto da tre byte che salveremo sulle seguenti variabili
byte statusByte;
byte controllerNumber;
byte controllerValue;

// Esegui solo una volta
void setup() {
  // Inizializzo motori
  initializeMotors();
  // Inizializzo porta seriale
  Serial.begin(115200);
}

// Per sempre
void loop() {
  // Aspetto finche non arriva qualcosa
  while (Serial.available() < 3 );
  // Leggi midi ed esegui movimenti
  readAndExecute();
}

void readAndExecute() {

  // Almeno una volta (in quanto ho già aspettatto)
  do {
    // Se la porta seriale è ancora disponibile
    if (Serial.available()) {
      // Leggi i byte
      statusByte = Serial.read();
      controllerNumber = Serial.read();
      controllerValue = Serial.read();
      // Se lo status byte è "change control"
      if (statusByte == CC_MIDI) {
        // Per ogni motorino
        for ( int i = 0; i < MAX_MOTORS; i++) {
          // Controlla se il controllo è riferito al motorino
          if (controllerNumber == i + FIRST_CONTROLLER) {
            // Se lo è portalo sulla posizione desiderata
            servoMotor[i].write(POS_0 + controllerValue * MAX_DELTA_DEGREE / MAX_INPUT);
          }
        }
      }
    }
  }
  // Prosegui finche ricevi qualcosa
  while (Serial.available() > 2);
}

void initializeMotors() {
  for (int i = 0; i < MAX_MOTORS; i++) {
    servoMotor[i].attach(FIRST_PIN + i);
    servoMotor[i].write(POS_0);
  }
}
