//
//  rand_c.hpp
//  Chem_react
//
//  Created by Andrew Diggs on 5/5/22.
//

#ifndef rand_c_hpp
#define rand_c_hpp

#include <stdio.h>
#include "Reax.hpp"
#define ARH 1.0e+13*604800.0
#define kb 8.617e-5
#define B(T) (kb*T)
#define room_T 300.0

class Rand{
public:
    Rand(const Rand&) = delete;
    
    static Rand& Get();
    double r_u_d(double, double);
    int r_uni_int(int, int);
    double trap_rate();
    double return_rate();
    double escape_rate();
    double get_time(double);
    
    void set_temp(float temp);
private:
    Rand() {}
    float m_temp;

};



#endif /* rand_c_hpp */
