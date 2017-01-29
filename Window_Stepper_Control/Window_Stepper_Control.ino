/* Window blind control closes blinds at night and opens them in the morning.
   This process is timed and needs tuned based on time of year & location.
   Photoresistor script: LINKTOLATERPROJECT
   Power Arduino at desired open time, with blinds closed.
   Buttons allow blinds to be opened/closed manually.
   
 * YourDuino.com Example Software Sketch
   Small Stepper Motor and Driver V1.4 11/30/2013
   http://arduino-direct.com/sunshop/index.php?l=product_detail&p=126
   
 * Button functionality can be found at:
   https://www.arduino.cc/en/Tutorial/Button

 * Blink without Delay usage can be found at:
   https://learn.adafruit.com/multi-tasking-the-arduino-part-1/using-millis-for-timing
   */

/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
//32 steps per revolution of internal motor in 4-step mode
#define MotorRev 32
//32*64 steps per revolution of output shaft after gear reduction
#define OutputRev 2048
//Number of revolutions required to open/close blinds to desired position
#define ReqRev 2
//Blinds open @ 8am & close @ 5pm. 9h*3600s/h*1000ms/s = 32,400s
//#define WaitToClose 9*3600*1000
//Blinds close @ 5pm & open @ 8am. 15h*3600s/h*1000ms/s = 54,000s 
//#define WaitToOpen 15*3600*1000

//Delete this and two next lines when done w/ testing
#define WaitToClose 5000
#define WaitToOpen 10000

//Pins used for push buttons
const int ButtonOpen = 12;
const int ButtonClose = 13;

/*-----( Declare Variables )-----*/
int StepsToTake;
bool blindstate = false; //true = open, false = closed
bool buttonopen = false;
bool buttonclose = false;
long prevmil = 0;
//Keep track of the last automatic event. 0=closed, 1 = opened.
int lastautoevent = 0;

/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(MotorRev, 8, 10, 9, 11);

void setup()
{
  Serial.begin(9600);
  //Set button pin modes to input
  pinMode(buttonopen, INPUT);
  pinMode(buttonclose, INPUT);
  //Serial.println("Setup Complete");
}

void loop()
{
  unsigned long currentmil = millis();
  if (((currentmil - prevmil) >= WaitToOpen) && (lastautoevent == 0))
  {
    StepsToTake  =  OutputRev * ReqRev;  // Open blinds
    small_stepper.setSpeed(500);   
    small_stepper.step(StepsToTake);
    //Change tracker variables
    blindstate = true;
    lastautoevent = 1;
    prevmil = millis();
  }
  else if (((currentmil - prevmil) >= WaitToClose) && (lastautoevent == 1))   
  {
    StepsToTake  =  - OutputRev * ReqRev;  // Close blinds  
    small_stepper.setSpeed(500);
    small_stepper.step(StepsToTake);
    //Change tracker variables
    blindstate = false;
    lastautoevent = 0;
    prevmil = millis();
  }
}
