/**
 * RBE3001 - Nucleo Firmware
 *
 * Welcome! This is the main file of your Nucleo C++ firmware.
 *
 * Instructions
 * ------------
 * The code below starts all the control and communication loops that we will be
 * using to control the arm. Please, take some time to familiarize yourself with the
 * workflow of the program.
 *
 * This program has two distinct running modes:
 * **Dummy mode** enables code testing/debugging when no arm is attached to the board.
 * **Physical mode** sends control signals to an attached arm.
 *
 * The running mode can be selected at compile time by commenting/uncommenting the
 * DUMMYMODE macro below.
 *
 */
#include "main.h"
#define  DOFs  3    // this macro defines the number of joints of the robotic arm
//#define  DUMMYMODE
#define  SERIALDEBUG

/*
 * ======= PART 1: Global Variables and definition of ancillary functions =====
 */
Ticker pidTimer;           // implements a timer
static PIDimp * pid[DOFs]; // pointer to PID controllers (one for each link)
HIDSimplePacket coms;      // HID packet handlers

// The following array contains home positions for the encoder values.
float homePosition[3] = {396,129,2669};

void runPid() {
	// update all positions fast and together
	for (int i = 0; i < DOFs; i++)
		pid[i]->updatePosition();
	// next update all control outputs
	for (int i = 0; i < DOFs; i++)
		pid[i]->updateControl();
}


/*
 * ======= PART 2: Main file ==================================================
 */
int main() {

	printf("\r\n\r\n Top of Main \r\n\r\n");

#if defined(DUMMYMODES)
	pid[0] = (PIDimp*) new DummyPID();
	pid[1] = (PIDimp*) new DummyPID();
	pid[2] = (PIDimp*) new DummyPID();
#else
	SPI * spiDev = new SPI(MOSI, MISO, CLK);
	pid[0] = new PIDimp(new Servo(SERVO_1, 5), new AS5050(spiDev, ENC_1),new AnalogIn(LOAD_1)); // mosi, miso, sclk, cs
	pid[1] = new PIDimp(new Servo(SERVO_2, 5), new AS5050(spiDev, ENC_2),new AnalogIn(LOAD_2)); // mosi, miso, sclk, cs
	pid[2] = new PIDimp(new Servo(SERVO_3, 5), new AS5050(spiDev, ENC_3),new AnalogIn(LOAD_3)); // mosi, miso, sclk, cs
#endif

   RunEveryObject* print = new RunEveryObject(0,500);
	// Invert the direction of the motor vs the input
	//pid[0]->state.config.Polarity = true;
	for (int i = 0; i < DOFs; i++) {
		pid[i]->state.config.Enabled = false;   // disable PID to start with
	}
	wait_ms(500);   // Cosines delay
	pidTimer.attach(&runPid, 0.0025);
	// capture 100 ms of encoders before starting
	wait_ms(100);
	for (int i = 0; i < DOFs; i++) {
		//reset after encoders have been updated a few times
		pid[i]->InitilizePidController();
#if defined(DUMMYMODES)
		pid[i]->ZeroPID();   // set the current encoder value to 0
							 // this should be replaced by calibration routine
#else
		//apply calibrations
		pid[i]->pidReset(pid[i]->GetPIDPosition() - homePosition[i]);
#endif
		if (pid[i]->GetPIDPosition() > 3000) {
			pid[i]->pidReset(pid[i]->GetPIDPosition() - 4095);
		}
		pid[i]->SetPIDEnabled(true);              // Enable PID to start control
		pid[i]->SetPIDTimed(pid[i]->GetPIDPosition(), 1000);
	}


	/**
	 * Place additional coms device here. Make sure that you include the header file for you
	 * coms device. Folllow the tempplate below.
	 * coms.attach(new device(pid, numerOfPid)
	 */
	coms.attach(new PidServer(pid, DOFs));
	coms.attach(new PidConfigServer(pid, DOFs));
	coms.attach(new PDVelocityConfigServer(pid, DOFs));
	coms.attach(new VelocityTarget(pid, DOFs));

	printf("\r\n\r\n Starting Core \r\n\r\n");


	/**
	 * This is the main loop of the program.
	 * coms.server() is called every iteration where is calls every attached coms device
	 * and reads data hid and sends data back up.
	 * IMPORTANT:
	 * remove the print lines to speed up the read/write operation.
	 */
	while (1) {
		coms.server();
		int link =1;
		if (print->RunEvery(pid[link]->getMs()) > 0) {
			/**
			 * This prints out the values of the load cells and encoders.
			 * Use them to calibrate your arm.
			 */
			/*
			printf("\r\nEncoder Value = %f , %f , %f", pid[0]->GetPIDPosition(),
					pid[1]->GetPIDPosition(), pid[2]->GetPIDPosition());
			printf("\r\nLoad Value = %f , %f , %f", pid[0]->loadCell->read(),
					pid[1]->loadCell->read(), pid[2]->loadCell->read());
			 2*/
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
