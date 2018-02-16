#include "Status.h"

void Status::event(float * buffer)
{


  uint8_t * buff = (uint8_t *)buffer;
  for(int i=4; i<64;i++){
    buff[i]=0;
  }



  //printf("\nPid Server Event");
  for(int i=0; i<myPumberOfPidChannels;i++)
  {

    float torque = myPidObjects[i]->loadCell->read();
    float position = myPidObjects[i]->GetPIDPosition();
    float velocity = (prevous_readings[i] - myPidObjects[i]->getVelocity())/0.0025;
    prevous_readings[i] = position;


    // write upstream packets
    buffer[(i*3)+0] = position;
    buffer[(i*3)+1] = velocity;
    buffer[(i*3)+2] = torque;

  }

}


