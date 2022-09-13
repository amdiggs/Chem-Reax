//
//  ValidIO.cpp
//  Chem_react
//
//  Created by Andrew Diggs on 9/9/22.
//

#include "ValidIO.hpp"

Valid::Valid(){}
Valid::~Valid(){}

bool Valid::match(std::string input, std::string m_type){
    std::regex reg (m_type);
    return std::regex_match(input,reg);
}

bool Valid::match_int(std::string input){
    return match(input, m_dig);
}
bool Valid::match_float(std::string input){
    return match(input, m_float) || match(input, m_exp_float);
    
}
bool Valid::match_space(std::string input){
    return match(input, m_space);
}


bool Valid::match_comment(std::string input){
    return  match(input, m_comment);
}



int Valid::get_int(std::string int_str){
    if(match_int(int_str)){
        return std::atoi(int_str.c_str());
    }
    else{std::cout << int_str << " is not compatable with type int"  << std::endl; exit(2);}
    
    
}

float Valid::get_float(std::string fl_str){
    
 if(match_float(fl_str)){
     return std::atoi(fl_str.c_str());
 }
 else{std::cout << fl_str << " is not compatable with type float" << std::endl; exit(2);}
}



