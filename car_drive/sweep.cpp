/*
   COMPILE WITH
   g++ -o serialTest main.cpp -lboost_system
 */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <exception>
#include <thread>
#include "drc_serial.h"

using namespace std;

int main(int argc, char** argv) {
	initialize();


	int steering  = 0;
	int motor = 0; 
	char str[100];
	char c = 's';
	int value;

//	sendMsg(SERVO, 45, str);

	while(1) {
		steering = (steering + 5) % 90;
		motor = (motor + 1) % 20;
		std::cout << "steering:" << steering << ", motor: " << motor << std::endl;

		sendMsg(steering - 45, motor + 70, str);
		usleep(100000);
//		std::cin >> c >> value;
		std::cout << "steering: " << steering << std::endl;

	}
	serial.close();
}
