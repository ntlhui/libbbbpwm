#include "PWM.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char** argv){
	PWM testPwm (PWM_P8_13, 40);
	testPwm.setOnTime(1000000);
	uint32_t onTime = 1000000;
	while(true){
		cin >> onTime;
		testPwm.setOnTime(onTime);
	}
}