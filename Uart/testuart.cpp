#include "UART.h"
#include <iostream>



int main(int argc, char const *argv[]) {

	UART uart;
	char message[] = "Hej";

	char msg[] = {1,2,3,4,5,6,7,8};

	while (1) {
//		uart.writeChar(message);
	uart.writeBinary(msg, 8);
		printf("%s\n", uart.readChar());
		//std::cout << uart.readChar() << std::endl;
	}

	return 0;
}
