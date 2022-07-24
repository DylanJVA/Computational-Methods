//Dylan VanAllen APHY477Y HW1
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include <climits>
#include <fstream>
#include <unistd.h>

using namespace std;

int kemper_increment(int x);

int main (int argc, char** argv) {
    double sum_alt = 0; 
    int i = 1; 
    //To write partial sums data to file
    ofstream myfile;
    myfile.open ("alt_partial_sums.csv");
    myfile << "# terms,total sum\n";

    //Alternating harmonic series
    while (i<75) {
        //Add this element to the sum
        sum_alt+=pow(-1,i+1)/double(i);
        myfile << to_string(i)+","+to_string(sum_alt)+"\n";
        //increment to get next term
        i++;
    }
    myfile.close();
    printf("After %i terms, the alternating series converged to %.5f\n",i-1,sum_alt);

    //here is the kempner 'depleted' harmonic series
    double sum_kemp = 0;
    //double partial_sums_kemp[100];
    
    i=1; int num_terms=1;
    myfile.open ("kemp_partial_sums.csv");
    myfile << "# terms,total sum\n";
    while(num_terms < 100000000000) {
        sum_kemp += 1/double(i);
        int size = int(log10(num_terms));
        //Write to file only a certain number of terms based on the current known size
        if (num_terms % int(pow(10,size)) == 0) {
            myfile << to_string(num_terms)+","+to_string(sum_kemp)+"\n";
        }
        //set i = to the next term
        i=kemper_increment(i+1);
        num_terms++;
    }
    printf("After %i terms, the depleted harmonic series converged to %.5f\n",num_terms-1,sum_kemp);
}

//function to get the next element in the kempner series
int kemper_increment(int x) {
    string str = to_string(x);
    int i = str.find("9");
    //if there is no 9, this is an acceptable element of the series
    if (i == string::npos){
        return x;
    }
    else {
        int place_from_last = str.length()-1 - i;
        //Should add 10^(number of places from last digit that the 9 is at) to not waste time adding 1 every iteration
        //Recursive for numbers such as 889: add 1 get 890 add 10 get 900 add 100 get 1000
        return kemper_increment(x+pow(10,place_from_last));
    }
}

