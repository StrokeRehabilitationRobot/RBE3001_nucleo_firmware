#ifndef  Torque_server
#define Torque_server
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>        // std::abs
#include "AS5050.h"
#include "mbed.h"
#include "Servo.h"
#include "PinNames.h"
extern float prevous_readings[3];

class TorqueServer: public PacketEventAbstract{
private:
	PIDimp* * myPidObjects;
   int myPumberOfPidChannels;
   Servo vibrator = Servo(PB_9, 5);
   //AnalogOut aout(PA_4);
   public:

  // Packet ID needs to be set
  TorqueServer (PIDimp* * pidObjects, int numberOfPidChannels )
   : PacketEventAbstract( 39){
    myPidObjects=pidObjects;
    myPumberOfPidChannels=numberOfPidChannels;
  }
  //User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float * buffer);

};


#endif /* end of include guard: Pid_server */
