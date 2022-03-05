#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"
#include "float.h"

double rand_uniform ( );
//func of x you want to integrate
double integrand ( double x );
using namespace std;

int main ( int argc, char** argv ) {

  long N = 100; //N=8 or h=0.125 is the winner (for Simpson's rule!)
  double left, right, midpt, trap, simp;
  double yL, yR, yM, a, b, h, xI, xF, xM;
  
  a = 0.; b = 1.; h = (b-a)/double(N);
  
  xI = a; left = 0.; right = 0.; midpt = 0.; trap = 0.; simp = 0.;
  cout << "Left-hand" << "\t" << "Right-hand" << "\t" << "Midpoint" << "\t" << "Trapezoid" << "\t" << "Simpson" << endl;
  for ( long i = 0; i < N; i++ ) {
    

    xF = xI + h;
    yL = integrand(xI);
    yR = integrand(xF);
    xM = (xI+xF)/2.;
    yM = integrand(xM);
    
    left += yL*h;
    right += yR*h;
    midpt += yM*h;
    trap += (yL+yR)*(h/2.);
    simp += (h/6.)*(yL+4.*yM+yR);
    
    printf("%.15f\t%.15f\t%.15f\t%.15f\t%.15f\n",left,right,midpt,trap,simp);

    xI = xF;
    
  }
  
  /*double x, y, area[2] = {0.,0.}, points = 2e10;
  double total = (b-a)*(1.-0.);
  for ( unsigned long long i = 0; i <= points; i++ ) {
    
    x = a + ( b - a ) * rand_uniform();
    y = 0 + ( 1 - 0 ) * rand_uniform();//y=ymin+(ymax-ymin)*rand just use uniform_real_distribution
    
    if(y < integrand(x)) area[0]++; //von Neumann
    else area[1]++;
    if ( !(i % 1000000) )
      fprintf(stderr,"%llu\t%.12f\n",i,(area[0]/(area[0]+area[1]))*total);
    
  }*/
  
  return 0; //not doing Simpson's 3/8 rule or adaptive-step or Taylor
  
}

double rand_uniform ( ) {
  
  return (double)rand() / (double)RAND_MAX;
  
}

double integrand ( double x ) {
  
  return exp(-pow(x,2.));
  //return pow(x,x);
  //return tgamma(x+1.);
  
}
