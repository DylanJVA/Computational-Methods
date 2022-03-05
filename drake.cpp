
#include <iostream>
#include <random>

using namespace std;

double rand_exp ( double mfp, double rUni ) {
  return -mfp * log ( rUni );
}

int main ( ) {
  
  int N;
  double Rstar, fp, Ne, fl, fi, fc, L;
  
  default_random_engine generator;
  
  for ( long i = 0; i < 1e5L; i++ ) {
    //in poisson dist mean = std
    poisson_distribution<int> distribution(7.0);
    //Rstar is # stars born per year
    Rstar = (double)distribution(generator);
    //fraction of stars with planets 
    fp = 1.0;
    //uniform random between 0.1 and 0.3
    uniform_real_distribution<double> distribution2(0.1,0.3);
    //fraction of exoplanets with env suitable for life
    Ne = distribution2(generator);
    
    uniform_real_distribution<double> distribution3(0.0,1.0);
    double rUni = distribution3(generator);
    //fraction of planets with life
    //exponentially unlikely
    fl = rand_exp ( 1.0, rUni );
    //fraction of planets with life that is intelligent
    //assumed to be ten times more expinentially unlikely
    rUni = distribution3(generator);
    fi = rand_exp ( 10., rUni );
    //fraction of planets that can communicate, completely unknown
    fc = distribution3(generator);
    //assume that civilizations communicate for 1000 +- 100 years
    normal_distribution<double> distribution4(1000.,100.);
    rUni = distribution4(generator);
    if ( rUni < 0. ) rUni = 0.;
    L = rUni;
    //best practice of casting double -> int (human rounding)
    N = (int)floor(Rstar * fp * Ne * fl * fi * fc * L + 0.5);    
    cout << N << endl;

  }

  return 0;

}
