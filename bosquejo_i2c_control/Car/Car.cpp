#include "Arduino.h"
#include "Car.h"


// Wheel

Wheel::Wheel(int sp, int fp, int bp) : SPEED_PIN(sp), FORWARD_PIN(fp), BACKWARD_PIN(bp) {} 

void Wheel::begin()
{
    pinMode(FORWARD_PIN, OUTPUT);
    pinMode(BACKWARD_PIN, OUTPUT);
    pinMode(SPEED_PIN, OUTPUT);

    stop();
}

void Wheel::moveForward(int speed)
{
    printStatus("mF ");

    digitalWrite(FORWARD_PIN, HIGH);
    digitalWrite(BACKWARD_PIN, LOW);
    analogWrite(SPEED_PIN, speed);
}

void Wheel::moveBackward(int speed)
{
    printStatus("mB");

    digitalWrite(FORWARD_PIN, LOW);
    digitalWrite(BACKWARD_PIN, HIGH);
    analogWrite(SPEED_PIN, speed);
}

void Wheel::stop()
{
    printStatus("S");
    analogWrite(SPEED_PIN, 0);
}

void Wheel::printStatus(String name)
{
    Serial.print(name);
    Serial.print(" ");
    Serial.print(FORWARD_PIN);
    Serial.print(" ");
    Serial.print(BACKWARD_PIN);
    Serial.print(" ");
    Serial.println(SPEED_PIN);
}


// Car
Car::Car(const Wheel wheels[NUM_WHEELS]) : _wheels(wheels){}

void Car::begin()
{
    for(int i = 0; i < NUM_WHEELS; i++)
    {
      _wheels[i].begin();
    }
 }

  // Mueve cada llanta una vez hacia adelante y hacia atrás.
void Car::testWheels()
{
    int delTime = 1000;
    int speed = 70;
    for(int i = 0; i < NUM_WHEELS; i++)
    {
        _wheels[i].moveForward(speed);
        delay(delTime);
        _wheels[i].stop();
        delay(delTime);
        _wheels[i].moveBackward(speed);
        delay(delTime);
        _wheels[i].stop();
        delay(delTime);
    }
}

void Car::moveForward(int speed)
{
    for(int i = 0; i < NUM_WHEELS; i++)
    {
        _wheels[i].moveForward(speed);
    }
}

void Car::moveBackward(int speed)
{
    for(int i = 0; i < NUM_WHEELS; i++)
    {
        _wheels[i].moveBackward(speed);
    }
}

void Car::stop()
{
    for(int i = 0; i < NUM_WHEELS; i++)
    {
      _wheels[i].stop();
    }
}

