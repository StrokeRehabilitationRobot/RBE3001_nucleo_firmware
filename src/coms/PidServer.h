#ifndef  Pid_server
#define Pid_server
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>        // std::abs

class PidServer: public PacketEventAbstract{
private:
<<<<<<< HEAD
  PIDimp* * myPidObjects;
=======
	PIDimp* * myPidObjects;
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git
   int myPumberOfPidChannels;
public:
  // Packet ID needs to be set
  PidServer (PIDimp* * pidObjects, int numberOfPidChannels )
<<<<<<< HEAD
   : PacketEventAbstract( PidServerID){
=======
   : PacketEventAbstract( 37){
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git
    myPidObjects=pidObjects;
    myPumberOfPidChannels=numberOfPidChannels;
  }
  //User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float * buffer);
};


#endif /* end of include guard: Pid_server */
