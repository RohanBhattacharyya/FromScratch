/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Rohan                                                     */
/*    Created:      10/9/2024, 4:20:06 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <math.h>
using namespace vex;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
motor arm = motor(PORT8, ratio18_1, false);
distance sensor = distance(PORT20);
motor claw = motor(PORT3, ratio18_1, false);
motor fRight = motor(PORT4, ratio18_1, true);
motor fLeft = motor(PORT10, ratio18_1, false);
motor bRight = motor(PORT2, ratio18_1, true);
motor bLeft = motor(PORT9, ratio18_1, false);
controller Controller = controller(primary);
distance sensor2 = distance(PORT19);

double rotation_degrees = 360;




int main() {

    fRight.setVelocity(100, percent);
    bRight.setVelocity(100, percent);
    fLeft.setVelocity(100, percent);
    bLeft.setVelocity(100, percent);
    arm.setPosition(0, degrees);
    arm.setBrake(hold);
    arm.setVelocity(25,percent);
    claw.setVelocity(100, percent);
    //coast, brake, hold
    claw.setPosition(0, degrees);
    arm.setPosition(0, degrees);
    bool scanned = false;
    double frspeed = 0;
    double flspeed = 0;
    double brspeed = 0;
    double blspeed = 0;
    bool manualoverride =false;
    bool stopped = false;

    claw.spinFor(reverse,2, seconds);
    while (true){
        if (sensor.objectDistance(mm) <=60 && !manualoverride && !scanned){
            claw.spin(forward);
            // claw.stop();
            Brain.Screen.print("Scanned");
            scanned = true;
            arm.spin(forward);
        }
        if (arm.position(degrees) >= 300 && !stopped){
            arm.stop();
            stopped = true;
            Brain.Screen.print("Stopped");
        }
        if (stopped && scanned && sensor2.objectDistance(inches) <=4){
            claw.spin(reverse);
            fLeft.spin(reverse);
            fRight.spin(reverse);
            bRight.spin(reverse);
            bLeft.spin(reverse);
            wait(2, seconds);
            arm.spin(reverse);
        }
        







        // if (sensor2.objectDistance(mm) <= 60 && sensor2.objectDistance(mm) >= 5 && arm.position(degrees) >= 180){
        //     scanned = true;
        // } else{
        //     scanned = false;
        // }
        // if (sensor.objectDistance(mm) <= 60){
        //     if (scanned == true){
        //         arm.spin(reverse);
        //     } else {
        //         arm.spin(forward);
        //     }
        //     claw.spin(forward);
        // } 
        // else {
        //     claw.spin(reverse);
        // }
        // if (Controller.ButtonA.pressing()){
        //     manualoverride = true;
        //     scanned=false;
        // }else{
        //     manualoverride = false;
        // }
        if (Controller.ButtonL2.pressing()){
            arm.spin(forward);
        } 
        else if (Controller.ButtonL1.pressing()){
            arm.spin(reverse);
        }
        if (Controller.ButtonB.pressing()){
            arm.stop();
        }

        if (Controller.ButtonR2.pressing()){
            claw.spin(reverse);
        }
        else if (Controller.ButtonR1.pressing()){
            claw.spin(forward);
        } 
        frspeed = Controller.Axis3.position();
        brspeed = Controller.Axis3.position();
        flspeed = Controller.Axis3.position();
        blspeed = Controller.Axis3.position();
        if (Controller.Axis4.position() < 0){
            frspeed += fabs(Controller.Axis4.position()* 1.2);
            brspeed += fabs(Controller.Axis4.position()* 1.2);
            flspeed -= fabs(Controller.Axis4.position());
            blspeed -= fabs(Controller.Axis4.position());
        } else if (Controller.Axis4.position() > 0){
            flspeed += Controller.Axis4.position()* 1.2;
            blspeed += Controller.Axis4.position()* 1.2;
            frspeed -= Controller.Axis4.position();
            brspeed -= Controller.Axis4.position();
        }
        
        flspeed += Controller.Axis1.position();
        frspeed -= Controller.Axis1.position();
        brspeed += Controller.Axis1.position();
        blspeed -= Controller.Axis1.position();

        fRight.spin(forward, frspeed, rpm);
        fLeft.spin(forward, flspeed, rpm);
        bRight.spin(forward, brspeed, rpm);
        bLeft.spin(forward, blspeed, rpm);

    }

}
