#include "PWM.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char** argv){
	PWM testPwm (PWM_P8_13, 50);
	testPwm.setOnTime(500000);
	testPwm.setPolarity(PWM_PULSE_HIGH);
	uint32_t onTime = 500000;
	while(true){
		cin >> onTime;
		testPwm.setOnTime(onTime);
	}
}
