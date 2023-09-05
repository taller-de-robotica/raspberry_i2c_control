/*
  Car.h - Library for controling the wheels of an omnidirectional car.
  Created by Verónica E. Arriola, September 4, 2023.
*/
#ifndef Car_h
#define Car_h

#include "Arduino.h"

class Wheel {
public:
  Wheel(int sp, int fp, int bp);

  void begin();

  void moveForward(int speed);

  void moveBackward(int speed);

  void stop();

  // Auxiliar para depurar pines.
  void printStatus(String name);
private:
  const int SPEED_PIN;
  const int FORWARD_PIN;
  const int BACKWARD_PIN;
};

enum WheelId
{
  FL = 0,
  FR,
  BL,
  BR
};

class Car
{
public:
  static const int NUM_WHEELS = 4;

  Car(const Wheel wheels[NUM_WHEELS]);

  void begin();

  // Mueve cada llanta una vez hacia adelante y hacia atrás.
  void testWheels();

  void moveForward(int speed);
  void moveBackward(int speed);

  void stop();
private:
  const Wheel *_wheels;
};

#endif
