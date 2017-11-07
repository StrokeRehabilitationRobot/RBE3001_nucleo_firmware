#ifndef MYPID_BOWLER_H
#define MYPID_BOWLER_H
#include <PID_Bowler.h>
#include "AS5050.h"
#include "Servo.h"
#include "RunEvery.h"
<<<<<<< HEAD
#include "AnalogIn.h"
=======

>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git
#define kp 0.005
#define ki 0
#define kd 0
#define vkp 1

#define vkd 0
<<<<<<< HEAD
class PIDimp : public PIDBowler
{
=======
#define SENSOR_SUM 4.0
class PIDimp : public PIDBowler{
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git
public:
  PIDimp(){}

  // constructor taking in the hardware objects
<<<<<<< HEAD
  PIDimp(Servo * myServo, AS5050 * myEncoder, AnalogIn* load);
=======
  PIDimp(Servo * myServo, AS5050 * myEncoder, AnalogIn * myLoadCell );
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git
  // these are implementations of the abstract functions
  float getPosition();
  void setOutputLocal( float);
  float resetPosition( float);
  void onPidConfigureLocal();
  void MathCalculationPosition( float);
  void MathCalculationVelocity( float);
  PidLimitEvent* checkPIDLimitEvents();
  float getMs();
  // These are parts of the concrete class
  AS5050 * encoder;
  Servo * servo;
<<<<<<< HEAD
  //My functions
  float getTorque();
  AnalogIn* load;

=======
  AnalogIn * loadCell;
  double gravityCompTerm=0;
private:
  float runningValues[(int)SENSOR_SUM];
  float runningTotal;
  int runningTotalIndex;
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git

};
#endif
