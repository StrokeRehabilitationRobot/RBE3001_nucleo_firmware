#include "TorqueServer.h"

void TorqueServer::event(float * buffer){

  //printf("\nPid Server Event");
  bool skipLink = false;
  for(int i=0; i<myPumberOfPidChannels;i++){

    float position = myPidObjects[i]->GetPIDPosition();

    // read values from the packet buffer
    float setpoint        = myPidObjects[i]->GetPIDPosition();
    float velocityTarget  = myPidObjects[i]->getVelocity();
    float forceTarget     = buffer[i];
    myPidObjects[i]->gravityCompTerm=forceTarget;

    //perform state update
    float timeOfMotion=0;
    if(velocityTarget>0)
     timeOfMotion=(std::abs(setpoint-position)/velocityTarget)*1000;// convert from Tics per second to miliseconds
    bool newUpdate = !myPidObjects[i]->bound(setpoint,
      myPidObjects[i]->state.interpolate.set,
      0.01,
     0.01);


    if(newUpdate){

      __disable_irq();    // Disable Interrupts
      myPidObjects[i]->SetPIDEnabled( true);

      myPidObjects[i]->SetPIDTimed(setpoint, timeOfMotion);// go to setpoint in timeBetweenPrints ms, linear interpolation
      __enable_irq();

   }else{
    //  printf("\r\nPacket write ignored, index %i to %f is already %f",i,setpoint,myPidObjects[i]->state.interpolate.set);
     skipLink=true;
   }

  }

  //controlls the handle vibrator
  if( buffer[9] )
  {
	  vibrator = 0.7;
  }
  else
  {
	  vibrator = 0.5;
  }

  uint8_t * buff = (uint8_t *)buffer;
  for(int i=4; i<64;i++){
    buff[i]=0;
  }

   float avgPos = 0;
   float avgVel = 0;
   float avgTau = 0;
   float torque = 0;
   float position = 0;
   float velocity = 0;
   int avgSize = 10;

   //printf("\nPid Server Event");
   for(int i=0; i<myPumberOfPidChannels;i++)
   {
 	avgPos = 0;
 	avgVel = 0;
 	avgTau = 0;

 	for(int j = 0; j  < avgSize; j++ )
 	{
 		torque = myPidObjects[i]->loadCell->read();
 		position = myPidObjects[i]->GetPIDPosition();
 		velocity = (prevous_readings[i] - position)/0.0025;

 		avgPos = position/avgSize;
 		avgVel = velocity/avgSize;

 	}


     prevous_readings[i] = position;


     // write upstream packets
     buffer[(i*3)+0] = avgPos;
     buffer[(i*3)+1] = avgVel;
     buffer[(i*3)+2] = torque;

   }

 }

