#include "Status.h"

void Status::event(float * buffer)
{


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
