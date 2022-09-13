//
//  main.cpp
//  Chem_react
//
//  Created by Andrew Diggs on 5/3/22.
//

#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "rand_c.hpp"
#include "Reax.hpp"
/*
 I want to solve
 d[a]/dt = -k1*[a] + k2*[b]
 d[[b]/dt = -k2*[b] + k1*[a]
 */

void write_dat(std::fstream&, Reax*, double&);
void init(std::string);


template<typename T>
void print_stuff(T value){
    std::cout << value << std::endl;
}

void print_stuff(float arr[][2], int rows){
    for (int i =0; i< rows; i++){
        for (int j = 0; j < 2; j++){
            std::cout << arr[i][j] << " ";
        }
       std::cout << std::endl;
    }
}


void write_dat(std::fstream& f, double ni, double nf , double& time){
    if (f.is_open()) {
        f << ni << " " << nf << " " << time << std::endl;
    }
    else{exit(2);}
    
}





int main(int argc, const char * argv[]) {

    
    std::string in_file;
    std::string out;
    for (int w = 0; w < argc; w++) {
        if (ITEM(argv[w], "-out")) {
            out = argv[w+1];
            out.append(".txt");
            continue;
        }
        
        else if (ITEM(argv[w], "-in")){
            in_file = argv[w + 1];
            continue;
        }
        else{continue;}
    }
    
    
    std::fstream outfile;
    outfile.open(out, std::ios::out);
    System my_sys(in_file);
    int i = 0;
    while(my_sys.get_time() < Params::Get().get_time()) {
        if (!(i%10000)) {
            //std::cout << "RUNNING..." << std::endl;
            
        }
        my_sys.get_event();
        i++;
    }
    my_sys.print_bar();
    my_sys.print_res();
    outfile.close();
    
     
    return 0;
}
