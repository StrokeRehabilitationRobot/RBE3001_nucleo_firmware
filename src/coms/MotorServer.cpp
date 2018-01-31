#include "MotorServer.h"

void MotorServer::event(float * buffer)
{

  //printf("\nPid Server Event");

  for(int i=0; i<myPumberOfPidChannels;i++)
  {
	  if(buffer[i])
		  myPidObjects[i]->servo->enable();
	  else
		  myPidObjects[i]->servo->disable();
  }
  for(int i=0; i<myPumberOfPidChannels;i++)
   {

     float torque = myPidObjects[i]->loadCell->read();
     float position = myPidObjects[i]->GetPIDPosition();
     float velocity =myPidObjects[i]->getVelocity();

     // write upstream packets
     buffer[(i*3)+0] = position;
     buffer[(i*3)+1] = velocity;
     buffer[(i*3)+2] = torque;

   }

  // }
}


