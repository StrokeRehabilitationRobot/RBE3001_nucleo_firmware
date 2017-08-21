#include "PidConfigServer.h"

void PidConfigServer::event(float * buffer){

  for(int i=0; i<myPumberOfPidChannels;i++){
    // read values from the packet buffer
    float p        = buffer[(i*3)+0];
    float i  = buffer[(i*3)+1];
    float d     = buffer[(i*3)+2];
    // Set the PID constants
    myPidObjects[i]->setPIDConstants(p, i, d);

  }

}
