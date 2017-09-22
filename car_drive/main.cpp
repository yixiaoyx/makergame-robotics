/*
   COMPILE WITH
   g++ -o serialTest main.cpp -lboost_system
 */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <exception>
#include "drc_serial.h"

int main(int argc, char** argv) {
	initialize();

	std::cout << "enter <motor> <steering>  \n>";
	char str[100] = {0};

	while(1) {
		int motor, steering;
		std::cout << "> ";
		std::cin >> motor >> steering;
		printf("motor %d, steering %d\n", motor, steering);

		char feedback[100] = {0};
		sendMsg(motor, steering, feedback);
	 	//usleep(1000);
		std::cout << "raw feedback: " << feedback << "\n";
		std::cout << "extracted feedback: " << extractFeedback(feedback) << "\n";
	}

	sendMsg(MOTOR, 0, str);
	serial.close();
}
