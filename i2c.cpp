#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define bufsize 3

int main(int argc, char *argv[])
{
    system("modprobe i2c-dev 2> /dev/null");

    int fd, num_rd;
    char buf[bufsize];
    int status = 0;
    int length = 3;			//<<< Number of bytes to write
    buf[0] = 0x10000000;
    buf[1] = 0x31;
    buf[2] = 0x00000000;

    fd = open("/dev/i2c-1", O_WRONLY); //Åbner I2C
    ioctl(fd, 0x0703, 0b0111100);  //Sætter adresse

    while(1)
    {
      //----- WRITE BYTES -----
      if (write(fd, buf, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
      {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
      }
    }

    status = close(fd);
    if (status == -1)
        printf("1Failed to close with err: %s\n", strerror(errno));

    return 0;
}
