#ifndef SERIAL_H
#define SERIAL_H

#include <boost/asio.hpp>
#include "shared.h"
#include <string>
#include <exception>

#define UPPER_MOTOR 100
#define LOWER_MOTOR -100

#define UPPER_SERVO 45
#define LOWER_SERVO -45

static boost::asio::io_service io;
static boost::asio::serial_port serial(io);

void initialize() {
	std::string num = "0";
	for(int i = 0; i < 5; i++){

		try{
			serial.open("/dev/ttyACM" + static_cast<std::string>(num));
			break;
		} catch(std::exception &e){
			std::cout << "trying " << num << " failed, continuing" << std::endl;
			num[0]++;
		}
	
	}
	if(num[0] == '5')
		throw(std::exception());
	std::cout << "opened port ACM" << num << std::endl;

	serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
	usleep(1000000);
}

void get_message(int motor, int servo, char* a) {
	a[0] = SHARED_KEY;
	a[1] = (char)motor;
	a[2] = (char)servo;
}

// assumed that initialize is called
void sendMsg(int motor, int servo, char* str) {
	assert(servo <= UPPER_SERVO && servo>= LOWER_SERVO);
	assert(motor <= UPPER_MOTOR && motor >= LOWER_SERVO);

	char toSend[3];

	get_message(motor, servo, toSend);

	int retval = boost::asio::write(serial,boost::asio::buffer(toSend,sizeof(toSend)));
	if(retval <= 0)
		std::cout << "serial write failed: " << retval << std::endl;
	    //usleep(100000);

	//try
	//{
		boost::asio::read(serial, boost::asio::buffer(str, 5));
		//std::cout << "got here" << std::endl;
		std::cout << "feedback in serial.h is " << str << std::endl;
	//
	//catch (const boost::system::system_error &e1)
	//{
	//}
}

#endif
