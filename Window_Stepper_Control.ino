/* Window blind control closes blinds at night and opens them in the morning.
   This process is timed and needs tuned based on time of year & location.
   Photoresistor script: LINKTOLATERPROJECT
   Power Arduino at desired open time, with blinds closed.
   Buttons allow blinds to be opened/closed manually.
   
 * YourDuino.com Example Software Sketch
   Small Stepper Motor and Driver V1.4 11/30/2013
   http://arduino-direct.com/sunshop/index.php?l=product_detail&p=126 */

/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
//32 steps per revolution of internal motor in 4-step mode
#define MotorRev 32
//32*64 steps per revolution of output shaft after gear reduction
#define OutputRev 2048
//Number of revolutions required to open/close blinds to desired position
#define ReqRev 2
//Blinds open @ 8am & close @ 5pm. 9h*3600s/h = 32,400s
#define WaitToClose 9*3600
//Blinds close @ 5pm & open @ 8am. 15h*3600s/h = 54,000s 
#define WaitToOpen 15*3600
 

/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(MotorRev, 8, 10, 9, 11);

/*-----( Declare Variables )-----*/
int  StepsToTake;
//true = open, false = closed
bool state = false;

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
// Nothing  (Stepper Library sets pins as outputs)
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  StepsToTake  =  OutputRev * ReqRev;  // Open blinds
  small_stepper.setSpeed(500);   
  small_stepper.step(StepsToTake);
  state = true;
  delay(WaitToClose);
  
  StepsToTake  =  - OutputRev * ReqRev;  // Close blinds  
  small_stepper.setSpeed(500);
  small_stepper.step(StepsToTake);
  state = false;
  delay(WaitToOpen);
}
