#include "SetPID.h"

void SetPID::event(float * buffer)
{

	for(int i=0; i<myPumberOfPidChannels;i++)
	{
			// read values from the packet buffer
			float Kp    = buffer[(i*3)+0];
			float Ki    = buffer[(i*3)+1];
			float Kd    = buffer[(i*3)+2];
			myPidObjects[i]->setPIDConstants( Kp, Ki, Kd);
		}
		// Set gripper to 10th float value

	for(int i=0; i<myPumberOfPidChannels;i++){


	    // write upstream packets
	    buffer[(i*3)+0] = 1;
	    buffer[(i*3)+1] = 1;
	    buffer[(i*3)+2] = 1;

	  }


}
