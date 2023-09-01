/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car Lesson5 Wifi Control
 * CopyRight www.osoyoo.com
 * ___________________________________________________________________
 *
 * Control del robot desde una Raspberry utilizando I2C.
 * Adaptación para Taller de Robótica Proyecto PAPIME PE104223
 * @author blackzafiro
 *
 */
#include <Wire.h>
const int SLAVE_ADDRESS = 0x8; // Hexadecimal entre 8 y 127

#define speedPinR 3            // Front Wheel PWM pin connect Model-Y M_B ENA 
#define RightMotorDirPin1 24   // Front Right Motor direction pin 1 to Model-Y M_B IN1 (K1)
#define RightMotorDirPin2 22   // Front Right Motor direction pin 2 to Model-Y M_B IN2 (K1)
#define LeftMotorDirPin1  47   // Front Left Motor direction pin 1 to Model-Y M_B IN3  (K3)
#define LeftMotorDirPin2  46   // Front Left Motor direction pin 2 to Model-Y M_B IN4  (K3)
#define speedPinL 5            // Front Wheel PWM pin connect Model-Y M_B ENB

#define speedPinRB 6           // Rear Wheel PWM pin connect Left Model-Y M_A ENA 
#define RightMotorDirPin1B 53  // Rear Right Motor direction pin 1 to Model-Y M_A IN1 (K1)
#define RightMotorDirPin2B 52  // Rear Right Motor direction pin 2 to Model-Y M_A IN2 (K1) 
#define LeftMotorDirPin1B  51  // Rear Left Motor direction pin 1 to Model-Y M_A IN3  (K3)
#define LeftMotorDirPin2B  50  // Rear Left Motor direction pin 2 to Model-Y M_A IN4  (K3)
#define speedPinLB 7           // Rear Wheel PWM pin connect Model-Y M_A ENB

class Wheel {
private:
  const int SPEED_PIN;
  const int FORWARD_PIN;
  const int BACKWARD_PIN;

public:
  Wheel(int sp, int fp, int bp) : SPEED_PIN(sp), FORWARD_PIN(fp), BACKWARD_PIN(bp) {}

  void initPins() {
    pinMode(FORWARD_PIN, OUTPUT); 
    pinMode(BACKWARD_PIN, OUTPUT); 
    pinMode(SPEED_PIN, OUTPUT);

    stop();
  }

  void moveForward(int speed) {
    printStatus("mF ");

    digitalWrite(FORWARD_PIN, HIGH);
    digitalWrite(BACKWARD_PIN, LOW); 
    analogWrite(SPEED_PIN, speed);
  }

  void moveBackward(int speed) {
    printStatus("mB");

    digitalWrite(FORWARD_PIN, LOW);
    digitalWrite(BACKWARD_PIN, HIGH); 
    analogWrite(SPEED_PIN, speed);
  }

  void stop() {
    printStatus("S");
    analogWrite(SPEED_PIN, 0);
  }

  // Auxiliar para depurar pines.
  void printStatus(String name) {
    Serial.print(name);
    Serial.print(" ");
    Serial.print(FORWARD_PIN);
    Serial.print(" ");
    Serial.print(BACKWARD_PIN);
    Serial.print(" ");
    Serial.println(SPEED_PIN);
  }
};

const Wheel WHEELS[4] = {
  Wheel(speedPinL,  LeftMotorDirPin1,   LeftMotorDirPin2),
  Wheel(speedPinR,  RightMotorDirPin1,  RightMotorDirPin2),
  Wheel(speedPinLB, LeftMotorDirPin1B,  LeftMotorDirPin2B),
  Wheel(speedPinRB, RightMotorDirPin1B, RightMotorDirPin2B)
};

enum WheelId {
  FL = 0,
  FR,
  BL,
  BR
};

// Mueve cada llanta una vez hacia adelante y hacia atrás.
void testWheels() {
  int delTime = 1000;
  int speed = 70;
  for(int i = 0; i < 4; i++) {
    WHEELS[i].moveForward(speed);
    delay(delTime);
    WHEELS[i].stop();
    delay(delTime);
    WHEELS[i].moveBackward(speed);
    delay(delTime);
    WHEELS[i].stop();
    delay(delTime);
  }
}

void setup() {
  // Depurado usando un puerto serial
  Serial.begin(9600);

  // Se sube al camión I2C como esclavo con la dirección indicada
  Wire.begin(SLAVE_ADDRESS);

  for(int i = 0; i < 4; i++) {
    WHEELS[i].initPins();
  }

  //testWheels()

  // Se ejecuta al recibir datos
  Wire.onReceive(receiveEvent);

  // Llama requestEvent cuando se soliciten datos
  Wire.onRequest(requestEvent);
}
  
// Función que se ejecuta cuando el maestro va a enviar información.
void receiveEvent(int howMany) {
  sprintf(buf, "Received %d:\n", howMany);
  Serial.print(buf);
  int ava;
  while (ava = Wire.available()) {
    char c = Wire.read(); // receive byte as a character
    sprintf(buf, "Wire read %d: %d=%c\n", ava, c, c);
    Serial.print(buf);
    //digitalWrite(LED_PIN, c);
  }
}

// Función que se ejecuta cuando el maestro solicita información.
void requestEvent() {

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}
