//
//  Reax.hpp
//  Chem_react
//
//  Created by Andrew Diggs on 9/6/22.
//

#ifndef Reax_hpp
#define Reax_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include "rand_c.hpp"
#include "ValidIO.hpp"

class Params{
    
private:
    
    int NUM_RES;
    float NUM_ATOMS;
    float** BAR;
    
    
    float MAX_TIME;
    float ATTEMPT_FREQUENCY;
    float TEMP;
    Params();
    ~Params();
public:
    Params(const Params&) = delete;
    static Params& Get();
    //setters
    void set_params(std::string in_file);
    void set_temp(float temp);
    void set_time(float time);
    void set_freq(float freq);
    //getters
    int get_res();
    float get_atoms();
    float** get_barriers();
    float get_temp();
    float get_time();
    float get_freq();
};

class Reax {
    
private:
    
    float m_k;
    float* m_from;
    float* m_to;
    void set_k(float E);
    
public:

    Reax();
    Reax(float Ea, float* e_to, float* e_from);
    ~Reax();
    float get_rate();
    void event(double time);
    
};


class System{
private:
    int m_num_res;
    int m_num_reacs;
    float m_num_atoms;
    
    float m_reservoirs[50];
    float m_barriers[50][2];
    float m_time;
    
    
    void set_evals();
    void set_res();
    void set_reax();
    
    
public:
    System();
    System(std::string in_file);
    ~System();
    
    Reax reactions[100];
    
    int num_res();
    int num_reacs();
    
    void step_time(double dt);
    float get_time();
    
    float total_rate();
    void get_event();
    
    
    
    
    void print_res();
    void print_bar();
};


bool ITEM(std::string str, std::string reg_ex);
unsigned int word_to_int(std::string word);
float rate(float E);



#endif /* Reax_hpp */
