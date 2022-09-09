//
//  Reax.cpp
//  Chem_react
//
//  Created by Andrew Diggs on 9/6/22.
//

#include "Reax.hpp"




Reax::Reax():
m_k(0.0)
{
    m_to = nullptr;
    m_from = nullptr;
}

Reax::Reax(float Ea, float* e_to, float* e_from):
m_to(e_to), m_from(e_from)
{
    if (Ea > 0.01) {
        set_k(Ea);
    }
    else{m_k = 0.0;}
}


Reax::~Reax(){
    
}

void Reax::set_k(float E) {
    m_k = rate(E);
    return;
}

float Reax::get_rate(){
    return m_k * (*m_from);
}



void Reax::event(double time){
    float delta = get_rate() * time;
    if (delta > *m_from) {
        *m_to+=*m_from;
        *m_from=0.0;
    }
    else{
        *m_from-=delta;
        *m_to+=delta;
    }
    return;
}


System::System():
m_num_res(5), m_num_reacs(10), m_time(0.0){
    
    set_res();
    set_evals();
    set_reax();


}

System::System(std::string in_file): m_time(0.0) {
    std::ifstream infile (in_file);
    std::string line;
    std::string name;
    std::string item;
    std::stringstream ss;
    int wrd;
    float param;
    if (infile.is_open()){
        while (getline(infile,line)) {
            if(ITEM(line, "#ITEM")){
                ss << line;
                ss >> item >> name;
                wrd = word_to_int(name);
                
                switch (wrd) {
                    case 569:
                        std::cout << "NUM_RES =?" << name << std::endl;
                        infile >> m_num_res;
                        m_num_reacs = 2*m_num_res;
                        break;
                    case 723:
                        std::cout << "NUM_ATOMS =?" << name << std::endl;
                        infile >> m_num_atoms;
                        set_res();
                        break;
                    case 602:
                        std::cout << "BARRIERS =?" << name << std::endl;
                        if (m_num_res != 0){
                            for (int j = 0; j<m_num_res; j++){
                                infile >> m_barriers[j][0] >> m_barriers[j][1];
                            }
                            
                        }
                        break;
                        
                    case 303:
                        std::cout << "TIME =?" << name << std::endl;
                        infile >> param;
                        Params::Get().set_time(param);
                        break;
                    case 310:
                        std::cout << "TEMP =?" << name << std::endl;
                        infile >> param;
                        Params::Get().set_temp(param);
                        break;
                    case 690:
                        std::cout << "FREQUENCY =?" << name << std::endl;
                        infile >> param;
                        Params::Get().set_freq(param);
                        break;
                        
                    default:
                        break;
                }
                
                ss.clear();

            }
        }
    }
    else{std::cout << "file did not open" << std::endl; exit(4);}
    set_reax();
}


System::~System() { 
    
}

void System::set_params(std::string word,std::ifstream& infile){
    std::string line;
    std::stringstream ss;
    int wrd = word_to_int(word);
    float param;
    
    switch (wrd) {
        case 569:
            std::cout << "NUM_RES =?" << word << std::endl;
            getline(infile,line);
            if (!line.empty()) {
                ss << line;
                ss >> m_num_res;
                m_num_reacs = 2*m_num_res;
                ss.clear();
                break;
            }
            else{exit(5);}
        case 723:
            std::cout << "NUM_ATOMS =?" << word << std::endl;
            infile >> m_num_atoms;
            set_res();
            break;
        case 602:
            std::cout << "BARRIERS =?" << word << std::endl;
                for (int j = 0; j<m_num_res; j++){
                    getline(infile,line);
                    if (!line.empty()) {
                        ss << line;
                        if (!ss.) {
                            <#statements#>
                        }
                        continue;
                    }
                    else{
                        std::cout << "Number of barriers does not match numer of reservoirs\n Better check your input file!!" << std::endl;
                        exit(5);
                    }
                }
            break;
            
        case 303:
            std::cout << "TIME =?" << word << std::endl;
            if(infile >> param){
                Params::Get().set_time(param);
            }
            break;
        case 310:
            std::cout << "TEMP =?" << word << std::endl;
            if(infile >> param){
                Params::Get().set_temp(param);
            }
            break;
        case 690:
            std::cout << "FREQUENCY =?" << word << std::endl;
            if(infile >> param){
                Params::Get().set_freq(param);
            }
            break;
            
        default:
            break;
    }
    
}


void System::set_res(){
    m_reservoirs[0] = m_num_atoms;
    for (int i = 1; i< m_num_res; i++){
        m_reservoirs[i] = 0.0;
    }
    
}

void System::set_evals(){
    float e_vals[10][2] ={
        {2.9, 1.15},
        {0.27, 0.41},
        {0.41, 0.41},
        {0.41, 0.41},
        {1.9, 2.9}
        
    };
    for (int i = 0; i< m_num_res; i++){
        m_barriers[i][0] = e_vals[i][0];
        m_barriers[i][1] = e_vals[i][1];
    }
    
    
}


void System::set_reax(){
    int back, forward, count;
    for (int i = 0; i< m_num_res; i++){
        count = 2*i;
        if(i==0){
            back = m_num_res-1;
            forward = i+1;
        }
        else if (i==(m_num_res - 1)){
            back = i-1;
            forward = 0;
            
        }
        else{
            back = i-1;
            forward = i+1;
        }
        reactions[count] = Reax(m_barriers[i][0], &m_reservoirs[back], &m_reservoirs[i]);
        reactions[count + 1] = Reax(m_barriers[i][1], &m_reservoirs[forward], &m_reservoirs[i]);
    }
}

int System::num_res() { 
    return m_num_res;
}

int System::num_reacs() { 
    return  m_num_reacs;;
}

void System::step_time(double dt) {
    m_time += dt;
}

float System::get_time() { 
    return m_time;
}

float System::total_rate() { 
    float tot = 0.0;
    for (int i =0; i< m_num_reacs; i++) {
        tot+=reactions[i].get_rate();
    }
    return tot;
}

void System::get_event() {
    float tot = this -> total_rate();
    double tau = Rand::Get().get_time(tot);
    this -> step_time(tau);
    double rand_rate = Rand::Get().r_u_d(0.0, tot);
    double cum_rate = 0.0;
    for (int i =0; i<m_num_reacs; i++) {
        cum_rate+= reactions[i].get_rate();
        if (cum_rate < rand_rate) {
            continue;
        }
        else{
            reactions[i].event(tau);
            return;
        }
    }
    return;
}



void System::print_res(){
    for (int i = 0; i<m_num_res; i++) {
        std::cout << m_reservoirs[i] << std::endl;
    }
}


void System::print_bar(){
    for (int i = 0; i<m_num_res; i++) {
        std::cout << m_barriers[i][0]
        << " " << m_barriers[i][1] << std::endl;
    }
}



bool ITEM(std::string str, std::string reg_ex){
    std::regex reg(reg_ex);
    std::smatch m;
    std::regex_search(str, m, reg);
    return !m.empty();
}


unsigned int word_to_int(std::string word){
    unsigned int wta = 0;
    for (int i = 0; i<word.size(); i++){
        wta+=word[i];
    }
    return wta;
    
}


Params::Params()
: MAX_TIME(0.0), TEMP(room_T), ATTEMPT_FREQUENCY(ARH)
{}

Params &Params::Get() { 
    static Params inst;
    return inst;
}



float Params::get_temp(){
    return TEMP;
}
float Params::get_time(){
    return MAX_TIME;
}
float Params::get_freq(){
    return ATTEMPT_FREQUENCY;
}

void Params::set_temp(float temp) { 
    this -> TEMP = temp;
}

void Params::set_time(float time) { 
    this->MAX_TIME = time;
}

void Params::set_freq(float freq) { 
    this->ATTEMPT_FREQUENCY = freq;
}


float rate(float E){
    return Params::Get().get_freq()*exp((-1.0*E) / B(Params::Get().get_temp()));
}


