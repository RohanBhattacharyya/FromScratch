#include "vex.h"
#include "init.cpp"
void armgrab(){
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
}