#include <iostream>
#include <random>
#include <fstream>
using namespace std; 

double f(double x) {
    double a = 1, b = 0, c = sqrt(.5);
    return a*exp(-1*(x-b)*(x-b)/(2*c*c));
}

int main() {
    default_random_engine generator;
    double a = 0, b = 1;
    uniform_real_distribution<double> limits(a,b);
    int in = 0;
    for (int i = 0; i < 1E8L; i++ ) {
        double x = limits(generator);
        double y = limits(generator);
        if(y<f(x)) in++;
    }
    cout << double(in)/1E8L;
}