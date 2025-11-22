#include "serial.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static int serial_fd = -1;

void Serial_Setup(const char* fileName) {
struct termios tty;

    // Open the serial port
    serial_fd = open(fileName, O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd < 0) {
        perror("Error opening serial port");
        return;
    }

    // Get current terminal attributes
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("Error getting terminal attributes");
        close(serial_fd);
        serial_fd = -1;
        return;
    }

    // Set baud rate to 115200
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    // Configure 8N1
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8 data bits
    tty.c_cflag &= ~PARENB;                    // No parity
    tty.c_cflag &= ~CSTOPB;                    // 1 stop bit
    tty.c_cflag |= CLOCAL | CREAD;             // Enable receiver, ignore modem control lines

    // Set raw input/output mode
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    tty.c_oflag &= ~OPOST;                          // Raw output

    // Set read timeout
    tty.c_cc[VMIN] = 0;  // Minimum number of characters to read (non-blocking)
    tty.c_cc[VTIME] = 10; // Timeout in deciseconds (1 second)


    // Apply the settings
    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("Error setting terminal attributes");
        close(serial_fd);
        serial_fd = -1;
        return;
    }
}

size_t Serial_Write(const void* data, size_t length) {
 if (serial_fd < 0) {
        fprintf(stderr, "Serial port not initialized\n");
        return 0;
    }

    ssize_t bytes_written = write(serial_fd, data, length);
    tcdrain(serial_fd);
    if (bytes_written < 0) {
        perror("Error writing to serial port");
        return 0;
    }

    return (size_t)bytes_written;
}

size_t Serial_Read(void* data, size_t length) {
if (serial_fd < 0) {
        fprintf(stderr, "Serial port not initialized\n");
        return 0;
    }

    ssize_t bytes_read = read(serial_fd, data, length);
    if (bytes_read < 0) {
        perror("Error reading from serial port");
        return 0;
    }

    return (size_t)bytes_read;
}
