#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"

//#define DEBUG_MODE

using namespace std;
double rand_uniform ( long rand_int );
double randU ();
int iseed = 1;
double rand_exp ( double tau );
double rand_gauss ( double u, double v );

int main ( int argc, char** argv ) {

#ifdef DEBUG_MODE

  cout << "Hello!" << endl;
  int a = 1 + atoi(argv[1]);
  cout << "Hi!" << endl;

#endif

  cout << RAND_MAX << endl;
  for ( int i = 0; i < 100; i++ ) {
    cout << rand_uniform(rand()) << "\t" << randU() << "\t" << rand_exp(1.) << "\t" << rand_gauss(rand_uniform(rand()),rand_uniform(rand())) << endl;
  }

  double exampleNum = randU();
  char digits[9]; //another way to define a string, similar to "string"
  sprintf ( digits, "%.6f", exampleNum ); //there is an itoa like atoi but no ftoa like atof function
  cout << exampleNum << ": " << endl;
  cout << digits[0] << " " << digits[1] << " " << digits[2] << endl;
  int firstDigit = digits[2] - '0';
  cout << firstDigit << endl; //back to number again!
  
  //Next: debug with cout statements, renaming files, everyone know what a hist is? Mention if/else for 0.1-..
  return 1; //just keeping you on your toes :)

}

double rand_uniform ( long rand_int ) {

  return double(rand_int) / (double)RAND_MAX;

}

double randU () {

  long imax = 2147483647;
  double xmax_inv = 1./double(imax);
  iseed *= 65539;
  if ( iseed < 0 )
    iseed += imax + 1;
  double x = double(iseed) * xmax_inv;
  return x;
  
}

double rand_exp ( double tau ) {

  return -tau*log(rand_uniform(rand()));

}

double rand_gauss ( double u, double v ) {

  return sqrt(-2.*log(u))*cos(2*M_PI*v);

}
