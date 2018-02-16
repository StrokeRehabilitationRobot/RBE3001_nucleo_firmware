#include "PidServer.h"

void PidServer::event(float * buffer){

  //printf("\nPid Server Event");
  bool skipLink = false;
  for(int i=0; i<myPumberOfPidChannels;i++)
  {

    float position = myPidObjects[i]->GetPIDPosition();

    // read values from the packet buffer
    float setpoint        = buffer[(i*3)+0];
    //printf("Link: %i  angle %f \n\r", i,setpoint );
    float velocityTarget  = buffer[(i*3)+1];
    float forceTarget     = buffer[(i*3)+2];
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
      // printf("\n Index %i Interpolation Set = %f ,  Start = %f , setTime = %f , startTime = %f",
      // i,
      // myPidObjects[i]->state.interpolate.set,
      // myPidObjects[i]->state.interpolate.start,
      // myPidObjects[i]->state.interpolate.setTime,
      // myPidObjects[i]->state.interpolate.startTime
      // );
   }else{
    //  printf("\r\nPacket write ignored, index %i to %f is already %f",i,setpoint,myPidObjects[i]->state.interpolate.set);
     skipLink=true;
   }
  //  if(skipLink){
  //    for (int i=0;i<15;i++){
  //      printf("\r\nPacket write ignored, value %i to %f ",i,buffer[i]);
  //    }
   //}
  }

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
  int avgSize = 10;
  float avgLoad;
  float avgVel;
  float avgPos;
  //printf("\nPid Server Event");
  for(int i=0; i<myPumberOfPidChannels;i++)
  {

	avgLoad = 0;
	avgPos  = 0;
	avgVel  = 0;
    for(unsigned int read = 0; read < avgSize; read++)
    {
    	avgLoad += myPidObjects[i]->loadCell->read();
    }
    float torque = avgLoad/avgSize;
    float position = myPidObjects[i]->GetPIDPosition();
    float velocity =myPidObjects[i]->getVelocity();

    // write upstream packets
    buffer[(i*3)+0] = position;
    buffer[(i*3)+1] = velocity;
    buffer[(i*3)+2] = torque;

  }
  // for(int i=0; i<15;i++){
  //
  //   buffer[i]=i+0.01;
  //
  // }
}


