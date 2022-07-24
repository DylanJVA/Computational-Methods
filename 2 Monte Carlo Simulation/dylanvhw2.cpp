//Dylan VanAllen APHY477Y HW2
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <random>

using namespace std;

int main() {

    default_random_engine generator;
    uniform_int_distribution<int> gender_distribution(0,1);
    int count_both_boys = 0;
    int num_trials = 1E5;  

    //Case A: I have two children, at least one of which is a son. What is the probability I have a two boys?
    for(int i = 0; i < num_trials*100; i++) {
        int child_one, child_two; //variables to hold gender of each child
        //Get samples untilI have at least one son
        do {
            child_one = gender_distribution(generator);
            child_two = gender_distribution(generator);
        } while (child_one + child_two == 0);

        if (child_one + child_two == 2) 
            count_both_boys++;
    }
    printf("Out of %i trials where someone has at least one son, %i of them had 2 boys. P = %i/%i = %0.3f\n",num_trials,count_both_boys,count_both_boys,num_trials,double(count_both_boys)/num_trials);

    //Case B: I have two children, at least one of which is a son born on tuesday. What is the probability I have a two boys?
    uniform_int_distribution<int> weekday_distribution(1,7);
    count_both_boys = 0;
    for(int i = 0; i < num_trials; i++) {
        int child_one, child_two; 
        int child_one_day, child_two_day; //variables to hold weekday of birth of each child
        do {
            child_one = gender_distribution(generator);
            child_one_day = weekday_distribution(generator);
            child_two = gender_distribution(generator);
            child_two_day = weekday_distribution(generator);
            //check if either child one or child two is a boy born on tuesday, if not resample
        } while(!(child_one && child_one_day == 2) && !(child_two && child_two_day == 2));
                
        if (child_one + child_two == 2) 
            count_both_boys++;
    }
    printf("Out of %i trials where someone has at least one son born on tuesday, %i of them had 2 boys. P = %i/%i = %0.3f\n",num_trials,count_both_boys,count_both_boys,num_trials,double(count_both_boys)/num_trials);

    //Show that with more information it converges to 1/2
    
    ofstream myfile;
    myfile.open ("prob_two_boys.csv");
    myfile << "j,P(BB|I)\n";
    for (int j = 1; j < 50; j++) {
        //assume we know three things: I have two children, at least one is a boy, and a third fact specifying knowledge about the boy without which there would be j equally likely options
        uniform_int_distribution<int> distribution(0,j);
        count_both_boys = 0;
        for(int i = 0; i < num_trials; i++) {
            int child_one, child_two; 
            int child_one_info, child_two_info; //variables to hold weekday of birth of each child
            do {
                child_one = gender_distribution(generator);
                child_one_info = distribution(generator);
                child_two = gender_distribution(generator);
                child_two_info = distribution(generator);
                //check if either child one or child two is a boy meeting the requirement, if not resample
                //I use 0 
            } while(!(child_one && child_one_info == 0) && !(child_two && child_two_info == 0));

            if (child_one + child_two == 2) 
                count_both_boys++;
        }
    myfile << to_string(j)+","+to_string(double(count_both_boys)/num_trials)+"\n";
    }
    myfile.close();
    return 0;


}
    
