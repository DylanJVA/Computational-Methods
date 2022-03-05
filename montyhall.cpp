#include "stdio.h"
#include "math.h"
#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main() {
    default_random_engine generator;
    uniform_int_distribtion<int> distribution(0,1,2);

    for (long i = 0; i < 100000; i++) {
        int win = distribution(generator);//    00  01  10
        int pick = distribution(generator);//   10  00  01
        int loss = ~(win ^ pick);//             01  10  00
    }
}