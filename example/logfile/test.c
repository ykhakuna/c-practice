/*
 * test.c
 * test for writing log files
 *  Created on: Sep 22, 2014
 *      Author: yk
 */

#include "logfile.h"

int main(int argc, char** argv) {
	int i;
	for (i = 0; i < 14; ++i) {
		char buffer[32];
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "====> %d\n", i);
		write_log_file("log",buffer);

		usleep(100);

	}
	// system("pause");
	return 0;
}
