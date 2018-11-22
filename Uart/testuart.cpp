#include "UART.h"
#include <iostream>



int main(int argc, char const *argv[]) {

	UART uart;
	char message = 'H';

	//char msg[] = {0x01};

	while (1) {

		std::cout << "Status er: " << uart.receivestatus() << std::endl;
		uart.sendCoffeorder('7', 30, '1', 14);
	}

	return 0;
}
