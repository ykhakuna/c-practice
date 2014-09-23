/*
 * logfile.h
 *
 *  Created on: Sep 22, 2014
 *      Author: yk
 */

#ifndef LOGFILE_H_
#define LOGFILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FILE_MAX_SIZE (1*1024)
#define MAX_FILE_NUM 3
#define TIME_LENGTH 22 //time format length

void get_local_time(char *buffer);

long get_file_size(char *filename);

void write_log_file(char *filename, char *buffer);
//void write_log_file(char *filename, char *buffer, int thread_id);

#endif /* LOGFILE_H_ */
