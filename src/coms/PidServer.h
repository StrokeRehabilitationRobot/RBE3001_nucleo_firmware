
/**
 * The Pid server extends PacketEventAbstract.
 * This class is used to run pid on setpoints sent down from
 * the upstream. The packet should match the structure provided.
 * The command ID for this class is 37.
 * That means when a packet is formed it needs to be sent with a ID 37
 */

#ifndef  Pid_server
#define Pid_server
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>        // std::abs

class PidServer: public PacketEventAbstract{
private:
	PIDimp* * myPidObjects;
   int myPumberOfPidChannels;
public:
  // Packet ID needs to be set
  PidServer (PIDimp* * pidObjects, int numberOfPidChannels )
   : PacketEventAbstract( 37){
    myPidObjects=pidObjects;
    myPumberOfPidChannels=numberOfPidChannels;
  }
  //User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float * buffer);
};


#endif /* end of include guard: Pid_server */
