//Dylan VanAllen APHY477Y HW4
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

//The function I will integrate
double f( double x ) {
    return 1/x;
}
//The upper bounding line of the random coordinates
double g(double x, double b) {
    return (1/b-1)/(b-1)*x+1-(1/b-1)/(b-1);
}
//The same line as a function of y
double g_inv(double y, double b) {
    return (y-1+(1/b-1)/(b-1))*(b-1)/(1/b-1);
}
int main ( int argc, char** argv ) {
    default_random_engine generator;
    double area;
    int coords_per_trial = 1E6L;
    double areas[int(double(coords_per_trial)/10)];
    double b;
    //the goal is to integrate f(x) = 1/x from a = 1 to b until we get b such that the integral = 1
    //Begin with little knowledge of b, random between 1 and 10
    double x_min = 1; double x_max = 10;
    double precision = 1E-6L;
    //begin monte carlo estimation of e
    
    //Keep integrating and changing b until |area-1|<=precision
    while (abs(area-1)>precision) {
        //b will be randomly selected between x_min and x_max
        uniform_real_distribution<double> b_limits(x_min,x_max);
        b = b_limits(generator);

        int in = 0; 
        for (int i = 1; i <= coords_per_trial; i++) {
            //algorithm to produce uniform random points in the triangle
            uniform_real_distribution<double> y_limits(0,1);
            double y = 1-sqrt(y_limits(generator));
            uniform_real_distribution<double> x_limits(0,1-y);
            double x = x_limits(generator);
            //scale and shift coordinates to be 
            y = (1-1/b)*y+1/b;
            x = (b-1)*x+1;
    
            //count trials under the curve
            if (y < f(x)) in++;
            if (i%10==0)
                //for printing the convergence (only last iteration will not get overwritten)
                areas[int(double(i)/10)-1]=double(in)/double(i)*.5*(1-1/b)*(b-1)+1/b*(b-1);
        }
        //area is fraction of points under the curve * area of triange 
        // + small area under the curve that I had cut out of the bounding box
        area = double(in)/double(coords_per_trial)*.5*(1-1/b)*(b-1)+1/b*(b-1);
        //if the area is bigger than 1 I know to try a smaller b, adjust b limits
        if (area > 1) x_max = b;
        //same if area is smaller than 1
        else if (area < 1) x_min = b;
        //of course if it integrates exactly to 1 I am done
        else break;
    }
    printf("Final b value (approx. value of e): %.12f\n",b);

    ofstream myfile;
    //print Area V Num Points in that last iteration
    myfile.open ("avn.csv");
    myfile << "# Points,Area" << endl;
    for (int i = 0; i < double(coords_per_trial)/10;i++) {
        myfile << 10*(i+1) << "," << areas[i] << endl;
    }
    myfile.close();

    myfile.open ("avr.csv");
    myfile << "# Rectangles,Area" <<endl;
    precision = 1E-5L;
    //dx will be the step size in the Riemann integration
    double dx = 0.1;
    //number of rectangles is the width of the integration bounds divided by the step size
    int n = (M_E-1)/dx;
    area = 0;
    while (abs(area-1)>precision) {
        area = 0;
        //add rectangles of width dx and height f(x) over bounds of integration for Riemann integration
        for (double x = 1; x < M_E; x+=dx)
            area += f(x)*dx;
        myfile << n << "," << area << endl; //to plot area v num rectangles
        dx/=2;
        n = int((M_E-1)/dx);
    }
    printf("Integral of 1/x from 1 to e with Riemann integration: %.12f\n",area);
    
    return 0;
}