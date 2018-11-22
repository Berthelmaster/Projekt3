#include "UART.h"
#include <iostream>



int main(int argc, char const *argv[]) {

	UART uart;
	char message[] = "Hej";

	//char msg[] = {0x01};

	while (1) {
		uart.writeChar(message);
		//uart.writeBinary(msg, 1);
		printf("%s\n", uart.readChar());
		//std::cout << uart.readChar() << std::endl;
	}

	return 0;
}
