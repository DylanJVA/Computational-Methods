#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"

using namespace std; //lets you do cout instead of std::cout e.g.

int main ( int argc, char** argv ) { //arguments optional

  double theta[3][2], time[2], g, L, h; //declare all variables
  char str[80]; double temp, damping;

  FILE *file = fopen("pendulum.txt","r"); //open file with settings
  for ( int i = 0; i < 7; i++ ) { //loop over lines and read them
    fscanf ( file, "%s %lf", str, &temp ); //read file line by line
    switch ( i ) { //store different lines as different variables
    case 0:
      g = temp; //acceleration due to gravity
      break;
    case 1:
      L = temp; //length of pendulum
      break;
    case 2:
      theta[0][0] = temp; //initial angle (theta)
      break;
    case 3:
      theta[1][0] = temp; //initial change in angle (deriv theta-dot)
      break;
    case 4:
      time[1] = temp; //max time you want to reach (sec.) with initial assumed to be zero
      break;
    case 5:
      h = temp; //step size in time in seconds for diff eq. solving
      break;
    case 6:
      damping = temp; //the damping term
      break;
    } //close the switch
  } fclose ( file ); //close the file
  
  //cout << g << " " << L << " " << theta[0][0] << " " << theta[1][0] << " " << time[1] << " " << h << endl; sleep(10);
  
  theta[0][0] *= (M_PI/180.); //convert from degrees into radians for use with the C++ trigonometric functions
  theta[1][0] *= (M_PI/180.); //ditto for the first (time) derivative of the angle

  ofstream myfile;
  myfile.open("thetavt.csv");
  myfile << "time,theta" <<endl;

  for ( time[0] = 0.; time[0] < time[1]; time[0] += h ) { //loop from t=0 to t=time[1] in steps of 'h'

    //do the Euler solution
    theta[2][0] = -(g/L)*sin(theta[0][0]) - damping*theta[1][0]; //no small-angle approximation
    theta[1][1] = theta[1][0] + h * theta[2][0]; //theta-dot_n+1 = theta-dot_n + h * theta-double-dot
    theta[0][1] = theta[0][0] + h * theta[1][1]; //theta_n+1 = theta_n + h * theta-dot_n
    //Euler-Cromer vs. Euler changes theta[1][0] to theta[1][1], i.e., theta-dot_n to theta-dot_n+1

    myfile << time[0] << "," << theta[0][0]*(180./M_PI) << endl; //write to screen the current time, and current angle (in deg.)
    
    theta[0][0] = theta[0][1]; //replace theta_n with theta_n+1
    theta[1][0] = theta[1][1]; //replace first time deriv of theta
    
  } //close the loop
  
  return 1; //as usual end of program with a return of an integer

}
//end of main function