#include "main.h"
<<<<<<< HEAD
#include "mbed.h" //added for 6
=======
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git
#define  numberOfPid  3
//#define DUMMYLINKS
// reportLength max size is 64 for HID


Ticker pidTimer;
static PIDimp* pid[numberOfPid];
HIDSimplePacket coms;
<<<<<<< HEAD

float  calibrations[3] = {1845,2022,1203}; //Team-08
//float  calibrations[3] = {114,784,-10};
AnalogOut aout(DAC_PIN);
=======
//float calibrations[3] = { 1878.750000, 2103.250000, 988.000000 }; // team 3
float  calibrations[3] = {1448.750000 , 232.250000 ,0};
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git

void runPid() {
	// update all positions fast and together
	for (int i = 0; i < numberOfPid; i++)
		pid[i]->updatePosition();
	// next update all control outputs
	for (int i = 0; i < numberOfPid; i++)
		pid[i]->updateControl();
}

int main() {
	printf("\r\n\r\n Top of Main \r\n\r\n");

#if defined(DUMMYLINKS)
	pid[0] = (PIDimp*) new DummyPID();
	pid[1] = (PIDimp*) new DummyPID();
	pid[2] = (PIDimp*) new DummyPID();
#else
<<<<<<< HEAD
   SPI * spiDev = new SPI(MOSI, MISO, CLK);
   pid[0] = new PIDimp( new Servo(SERVO_1, 5),
                         new AS5050(spiDev, ENC_1),new AnalogIn(LOAD_1));  // mosi, miso, sclk, cs
   pid[1] = new PIDimp( new Servo(SERVO_2, 5),
                         new AS5050(spiDev, ENC_2),new AnalogIn(LOAD_2));  // mosi, miso, sclk, cs
   pid[2] = new PIDimp( new Servo(SERVO_3, 5),
                         new AS5050(spiDev, ENC_3),new AnalogIn(LOAD_3));  // mosi, miso, sclk, cs
=======
	SPI * spiDev = new SPI(MOSI, MISO, CLK);
	pid[0] = new PIDimp(new Servo(SERVO_1, 5), new AS5050(spiDev, ENC_1),new AnalogIn(LOAD_1)); // mosi, miso, sclk, cs
	pid[1] = new PIDimp(new Servo(SERVO_2, 5), new AS5050(spiDev, ENC_2),new AnalogIn(LOAD_2)); // mosi, miso, sclk, cs
	pid[2] = new PIDimp(new Servo(SERVO_3, 5), new AS5050(spiDev, ENC_3),new AnalogIn(LOAD_3)); // mosi, miso, sclk, cs
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git
#endif

<<<<<<< HEAD
   // Invert the direction of the motor vs the input
   //pid[0]->state.config.Polarity = true;
   for (int i=0;i<numberOfPid;i++){
     pid[i]->state.config.Enabled=false;// disable PID to start with
   }
   wait_ms(500);// Cosines delay
   pidTimer.attach(&runPid, 0.005);
   // capture 100 ms of encoders before starting
   wait_ms(100);
	for (int i = 0; i < numberOfPid; i++) {
		//reset after encoders have been updated a few times
		pid[i]->InitilizePidController();
#if defined(DUMMYLINKS)
		pid[i]->ZeroPID();   // set the current encoder value to 0
							 // this should be replaced by calibration routine
#else
		//apply calibrations
		pid[i]->pidReset(pid[i]->GetPIDPosition()-calibrations[i]);
#endif
		if(pid[i]->GetPIDPosition()>3000) {
			pid[i]->pidReset(pid[i]->GetPIDPosition()-4095);
		}
		pid[i]->SetPIDEnabled(true);              // Enable PID to start control
		pid[i]->SetPIDTimed(pid[i]->GetPIDPosition(), 1000);
	}

   /*
   // Run PID controller calibration
   // only one can be run at a time, and the control loop needs to wait
   // until the calibration is done before advancing to the next
   pid[0]->runPidHysterisisCalibration();
   // Run a homing procedure down where 123 is the value of the encoder at home
   pid[0]->startHomingLink( CALIBRARTION_home_down, 123);
   // Run a homing procedure up  where 123 is the value of the encoder at home
   pid[0]->startHomingLink( CALIBRARTION_home_up, 123);
   // Run a homing procedure to scale the velocity outputs  where 123 is the value of the encoder at home
   pid[0]->startHomingLink( CALIBRARTION_home_velocity, 123);
   */
   coms.attach(new PidServer (pid, numberOfPid ));
   coms.attach(new SetPID (pid, numberOfPid ));

   printf("\r\n\r\n Starting Core \r\n\r\n");
=======
>>>>>>> branch 'master' of git@github.com:madhephaestus/Kevins_RBE3001_nucleo_firmware.git
   RunEveryObject* print = new RunEveryObject(0,500);
	// Invert the direction of the motor vs the input
	//pid[0]->state.config.Polarity = true;
	for (int i = 0; i < numberOfPid; i++) {
		pid[i]->state.config.Enabled = false;   // disable PID to start with
	}
	wait_ms(500);   // Cosines delay
	pidTimer.attach(&runPid, 0.0025);
	// capture 100 ms of encoders before starting
	wait_ms(100);
	for (int i = 0; i < numberOfPid; i++) {
		//reset after encoders have been updated a few times
		pid[i]->InitilizePidController();
#if defined(DUMMYLINKS)
		pid[i]->ZeroPID();   // set the current encoder value to 0
							 // this should be replaced by calibration routine
#else
		//apply calibrations
		pid[i]->pidReset(pid[i]->GetPIDPosition() - calibrations[i]);
#endif
		if (pid[i]->GetPIDPosition() > 3000) {
			pid[i]->pidReset(pid[i]->GetPIDPosition() - 4095);
		}
		pid[i]->SetPIDEnabled(true);              // Enable PID to start control
		pid[i]->SetPIDTimed(pid[i]->GetPIDPosition(), 1000);
	}


	coms.attach(new PidServer(pid, numberOfPid));
	coms.attach(new PidConfigServer(pid, numberOfPid));
	coms.attach(new PDVelocityConfigServer(pid, numberOfPid));
	coms.attach(new VelocityTarget(pid, numberOfPid));

	printf("\r\n\r\n Starting Core \r\n\r\n");
	while (1) {
		coms.server();
		int link =1;
		if (print->RunEvery(pid[link]->getMs()) > 0) {
			printf("\r\nEncoder Value = %f , %f , %f", pid[0]->GetPIDPosition(),
					pid[1]->GetPIDPosition(), pid[2]->GetPIDPosition());
			printf("\r\nLoad Value = %f , %f , %f", pid[0]->loadCell->read(),
					pid[1]->loadCell->read(), pid[2]->loadCell->read());

			if (pid[link]->state.vel.enabled) {
				printf("\e[1;1H\e[2J\n\r\n\r\t Velocity set=   %f ticks/seCond\
						\n\r\t vel.lastPosition=      %f ticks\
						\n\r\t GetPIDPosition()=      %f ticks\
						\n\r\t getVelocity()=         %f ticks/seCond \ 
						\n\r\t vel.currentOutputVel=    %f \
						\n\r\t state.Output=    %f \
						\n\r\t state.OutputSet=    %f \
						\n\r\t state.vel.timeDiff=    %f \
						\n\r\t state.vel.velocityDiff=    %f\
						\n\r\t state.vel.posDiff=    %f\
						\n\r\t state.vel.proportional=    %f\
						\n\r\t state.config.V.P=    %f\
						\n\r\t state.config.V.D=    %f",
						pid[link]->state.vel.unitsPerSeCond,
						pid[link]->state.vel.lastPosition,
						pid[link]->GetPIDPosition(),
						pid[link]->getVelocity(),
						pid[link]->state.vel.currentOutputVel,
						pid[link]->state.Output,
						pid[link]->state.OutputSet,
						pid[link]->state.vel.timeDiff,
						pid[link]->state.vel.velocityDiff,
						pid[link]->state.vel.posDiff,
						pid[link]->state.vel.proportional,
						pid[link]->state.config.V.P,
						pid[link]->state.config.V.D);
			}
		}

	}
}
