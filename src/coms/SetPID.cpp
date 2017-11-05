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

		uint8_t * buff = (uint8_t *)buffer;
		for(int i=4; i<64;i++)
		{
			buff[i]=7;
		}


}
