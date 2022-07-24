#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"

using namespace std; 

int main ( int argc, char** argv ) {
    //g = GM/r(t)^2
    //use height starting at surface of earth
    //find time when height = distance btwn earth and moon - the 2 radii
    //-m(t)g(t) = dm/dt * dh/dt + m(d^2h/dt^2) 
    //mf = mi - dm/dt * dt until mf = mass of rocket
    //assume dm/dt = negative and constant look one up
    //escape velocity sqrt(2GM/r) M - mass of earth

    double h[3][2];//h'', h', and h final and initial
    double time[2];
    double g, G, M, Re, Rm; // g = GM/r^2
    double F, a, v, m; // = dm/dt*v+m*dv/dt
    double wetMass, dryMass;
    double dmdt, isp; // dmdt(isp) = (mf-mi)/isp
    //isp = thrust/(dmdt*g0)    g0=9.8 look up thrust and impulse 

    ofstream myfile;
    myfile.open("thetavt.csv");
    myfile << "time,theta" <<endl;


    for (time[0] = 0; time[0] < time[1]; time[0] += h ) { //loop from t=0 to t=time[1] in steps of 'h'

        //do the Euler solution
        theta[2][0] = -(g/L)*sin(theta[0][0]) - damping*theta[1][0]; //no small-angle approximation
        theta[1][1] = theta[1][0] + h * theta[2][0]; //theta-dot_n+1 = theta-dot_n + h * theta-double-dot
        theta[0][1] = theta[0][0] + h * theta[1][1]; //theta_n+1 = theta_n + h * theta-dot_n
        //Euler-Cromer vs. Euler changes theta[1][0] to theta[1][1], i.e., theta-dot_n to theta-dot_n+1

        myfile << time[0] << "," << theta[0][0]*(180./M_PI) << endl; //write to screen the current time, and current angle (in deg.)
        
        theta[0][0] = theta[0][1]; //replace theta_n with theta_n+1
        theta[1][0] = theta[1][1]; //replace first time deriv of theta
        
    } //close the loop

    return 0;
}

