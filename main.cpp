#include <iostream>
#include <math.h>
#include <vector>
std::pair<float,float> layer_calc(float base_alt, float base_temp,float base_press, float true_alt,float a,float g0,float r){
    if (a!=0.){
    float new_temp = base_temp + a*(true_alt-base_alt);
    float new_press = base_press*pow(((base_temp + a*(true_alt-base_alt))/base_temp),-g0/(a/1000)/r);
    return std::make_pair(new_temp,new_press);
    }
    else{
        float new_press = base_press*exp((-g0*(true_alt-base_alt)*1000/r/base_temp));
        return std::make_pair(base_temp,new_press);
    }
}

int main()
{float true_alt;
float g0 = 9.80665;
float r = 287.;
 std::cout<<"What is your Altitude: "<<std::endl;
 std::cin >> true_alt;
float alt_layers[8] = {0,11,20,32,47,51,71,84.852};
float a_vals[7] = {-6.5,0,1,2.8,0,-2.8,-2};
std::vector<float> base_temps = {288.15};
std::vector<float> base_press = {101325.};
bool running = true;
int i = 0;
while (running){
    if (true_alt/1000 <alt_layers[i+1]){
        std::pair<float,float> temp_press = layer_calc(alt_layers[i],base_temps[i],base_press[i],true_alt/1000,a_vals[i],g0,r);
        float density = temp_press.second/temp_press.first/r;
        std::cout<<base_press[i]<<std::endl;
        std::cout<<base_temps[i]<<std::endl;
        std::cout<< "Temp: "<<temp_press.first<<std::endl;
        std::cout<<"Pressure: "<<temp_press.second<<std::endl;
        std::cout<< "Density: "<<density<<std::endl;
        running = false;
    }
    else{
        std::pair<float,float> temp_press = layer_calc(alt_layers[i],base_temps[i],base_press[i],alt_layers[i+1],a_vals[i],g0,r);
        base_temps.push_back(temp_press.first);
        base_press.push_back(temp_press.second);

        i++;
    }
}



return 0;
}

