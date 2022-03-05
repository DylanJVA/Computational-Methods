#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"
#include "float.h"

#define POINTS 1e9L

using namespace std; long double rand_uniform ( );

int main ( int argc, char** argv ) {

  unsigned long long int in = 0ull; unsigned long long int out = 0ull;
  long double x,y,z, radius;
  long double volume, total;
  
  for ( unsigned long long int i = 0ull; i <= POINTS; i++ ) {
    
    x = rand_uniform()-0.5L;
    y = rand_uniform()-0.5L;
    z = rand_uniform()-0.5L;
    
    radius = sqrt ( pow (x,2.) + pow(y,2.) + pow(z,2.) );
    
    if ( radius <= 0.5L ) in++;
    else out++;
    
    volume = (long double)in;
    total = volume + (long double)out;

    cout.precision(51);
    if ( i % 10000 ) { ; }
    else
      cout << i << "\t" << (volume/total)/((4.L/3.L)*pow(0.5L,3.L)) << endl;
    
  }
  
  return 0;
  
}

long double rand_uniform () {
  
  return (long double)rand() / (long double)RAND_MAX;
  
}