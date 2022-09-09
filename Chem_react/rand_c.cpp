//
//  rand_c.cpp
//  Chem_react
//
//  Created by Andrew Diggs on 5/5/22.
//

#include "rand_c.hpp"
#include <iostream>
#include <chrono>
#include <random>



static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
std::minstd_rand0 gen (seed);

Rand& Rand::Get(){
    static Rand inst;
    return inst;
}

double Rand::r_u_d(double lb, double ub){
    std::uniform_real_distribution<double> test_dist(lb, ub);
    return test_dist(gen);
    
}


double Rand::trap_rate(){
    std::normal_distribution<double> trap(1.2, 0.2);
    return rate(trap(gen));
}

double Rand::return_rate(){
    std::exponential_distribution<double> ret(0.4);
    return rate(ret(gen));
}

double Rand::escape_rate(){
    std::normal_distribution<double> esc(0.6, 0.2);
    return rate(esc(gen));
}

double Rand::get_time(double rt){
    double tau = Rand::Get().r_u_d(0.0, 1.0);
    return (1.0/rt)*log(1.0/tau);
    
}
