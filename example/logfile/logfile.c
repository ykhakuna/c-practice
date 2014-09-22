/*
 logfile: write the log from threads or process
 inittial format:
 ID:time:msg
 */
#include "logfile.h"
void get_local_time(char *buffer) {
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", (timeinfo->tm_year + 1900),
			(timeinfo->tm_mon + 1), (timeinfo->tm_mday), timeinfo->tm_hour,
			timeinfo->tm_min, timeinfo->tm_sec);
}

long get_file_size(char *filename) {
	long length = 0;
	FILE *fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("unable to open the logfile");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fclose(fp);
	fp = NULL;
	return length;
}

void write_log_file(char *filename, char *buffer) {
	FILE *fp = NULL;
	if (NULL != filename && NULL != buffer) {
		long length = get_file_size(filename);
		if ((length + sizeof(buffer) + TIME_LENGTH) > FILE_MAX_SIZE) //exceed file size, create new one
		{ //two files first, then think about 5 files
			char new_filename[128];
			sprintf(new_filename,"%s%c",filename,'1');
			//strcat(new_filename, "1");
			/*		fp = fopen(new_filename, "a+");
			 if (NULL == fp) {
			 perror("cannot open logfile1\n");
			 exit(1);
			 }*/
			filename=new_filename;
		}

		fp = fopen(filename, "a+");
		if (NULL == fp) {
			perror("cannot open logfile1\n");
			exit(1);
		}

		char now_time[32];
		memset(now_time, 0, sizeof(now_time));
		get_local_time(now_time);
		fprintf(fp,"%s: ",now_time);
		fputs(buffer,fp);
//		fwrite(now_time, strlen(now_time) + 1, 1, fp);
//		fwrite(buffer, sizeof(buffer), 1, fp);

		fclose(fp);
		fp=NULL;
	}
}
