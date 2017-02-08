//Instructions for tuning the Window_Stepper_Control script-------------------------------//
These instructions cover tuning the script to match the appropriate Arduino pins used, timing requirements, and blind contraints. Scroll down for troubleshooting setup.

1. Manually adjust blinds to the open state. Determine how many motor revolutions are required to close the blinds and set this value for "ReqRev".

2. "WaitToClose" is the amount of milliseconds the blinds will stay in their open state. For example, if they were to open at 8am and close at 5pm that would be 9h*3600s/h*1000ms/s = 32,400ms.

3. "WaitToOpen" is the amount of milliseonds the blinds will stay in their closed state. For example, if the were to close at 5 pm and open at 8am that would be 15h*3600s/h*1000ms/s = 54,000ms.

4. "ButtonOpen" and "ButtonClose" need to be assigned numbers matching digital I/O pins on the Arduino. Default uses pins 12 and 13 which will be defines as inputs later.

5. "small_stepper" is an instance of the stepper class, specifying the number of steps and the pins the motor is attached to. 'The pin connections need to be 4 pins connected to Motor driver In1, In2, In3, In4 and then the pins entered here in the sequence 1-3-2-4 for proper sequencing'. Default uses pins 8, 10, 9, 11.

6. Motor speed is not seen as a variable and is left out of the upper portion of code. If desired the speed can be changed in the line "small_stepper.setSpeed(<integer>)" by replacing <integer>. This line exists under each if statement that operates the toggling of the blinds.



//Notes for Testing-----------------------------------------------------------------------//
It is impractical to wait a whole day to see if the system works. To make troubleshooting easier do the following:

1. Stepper motors produce high torque but turn slowly, it is recommended to reduce "ReqRev" to save time.

2. Comment out the lines defining "WaitToClose" and "WaitToOpen". Uncomment the testing lines defining these and set the numbers to a desired time. The default testing times are 5s and 10s.

3. Uncomment the "Serial.begin" and two "Serial.println" functions in the setup() section.

4. Uncomment the two "Serial.println" functions under the two if sections in the main loop.