/*****************************************************************************
 * Copyright (C) 2016   Zure Aakash Vasantrao zureav16.comp@coep.ac.in 
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>		/*Header file to access directory structure*/
#include <errno.h>
#include <stdio.h>

/*Defining color codes to display different file types*/
#define KRED  "\x1B[31m"
#define RESET "\033[0m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
int check(char *typechar);

int a = -1;			/*integer to traverse through levels of directories*/
int fcount = 0, dcount = 0;	/*Counts no. of files and folders*/
int chk = 0;			/*To check file types*/

/*This function is used for -i function and displays files without indentation.*/
void ifiles(const char *name)
{
	DIR *dir;
	char * occ,  space[128], line[128], buf[128];
	int i;
	struct dirent *filename;

	/*error if directory does not found*/
	if (!(dir = opendir(name))){
	printf("tree : '%s' : %s\n", name, strerror(errno));
        return;
        }
	if (!(filename = readdir(dir))){
		printf("%s\n", strerror(errno));
		return;
	}

	/*Isolates the filename from path.*/
	if(a >= 0){
		occ = strrchr(name,'/');
		i = occ - name;
		strncpy(buf, name+i+1, strlen(name));	
	}
	printf(KBLU"%s\n"RESET, buf);
	do {
		if (filename->d_type == DT_DIR) {     	/*Prints the directory files.*/
			char path[1024];
			snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
			if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
				continue;
			a++;
			dcount++;			/*Directory count*/
			ifiles(path);
		}
		else{					/*Prints the files.*/
			chk = check(filename->d_name);
			if (chk == 1) {
				printf(KMAG"%s\n"RESET, filename->d_name);	/*prints graphic files in MAGNETA.*/
			}
			else if (chk == 2) {
				printf(KRED"%s\n"RESET, filename->d_name);	/*Prints archives and compressed files in RED*/
			}
			else if(chk == 3) {
				printf(KGRN"%s\n"RESET, filename->d_name);	/*Prints executalble and text files in GREEN*/
			}
			else {
				printf("%s\n", filename->d_name);		/*Prints other files in default color*/
			}
			a = -1;
			fcount++;			/*File count*/
		}
	} while ((filename = readdir(dir)));
	closedir(dir);
}

/*Displays the tree command as it is.*/
void files(const char *name)
{
	DIR *dir;
	char * occ,  space[128], line[128], buf[128];
	int i;
	struct dirent *filename;
	strcpy(space,"");
	strcpy(buf, "");
	strcpy(line, "|-----");
	if (!(dir = opendir(name))){
	printf("tree : '%s' : %s\n", name, strerror(errno));
        return; 
        }
	if (!(filename = readdir(dir))){
		printf("%s\n", strerror(errno));
		return;
	}
	for(i=0;i<=a;i++)
	strcat(space, "|\t");
	if(a >= 0){
		occ = strrchr(name,'/');
		i = occ - name;
		strncpy(buf, name+i+1, strlen(name));	
	}
	printf("%s%s", space, line);
	printf(KBLU"%s\n"RESET, buf);
	do {
		if (filename->d_type == DT_DIR) {
			char path[1024];
			snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
			if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
				continue;
			a++;
			dcount++;
			files(path);
		}
		else{
			chk = check(filename->d_name);
			if (chk == 1) {
				printf("%s%s", space, line);
				printf(KMAG"%s\n"RESET, filename->d_name);
			}
			else if (chk == 2) {
				printf("%s%s", space, line);
				printf(KRED"%s\n"RESET, filename->d_name);
			}
			else if(chk == 3) {
				printf("%s%s", space, line);
				printf(KGRN"%s\n"RESET, filename->d_name);
			}
			else {
				printf("%s%s%s\n", space, line, filename->d_name);
			}
			
			a = -1;
			fcount++;
		}
	} while ((filename = readdir(dir)));
	closedir(dir);
}

/*Prints -d  option. Dierctories only*/
void folders(const char *name)
{
	DIR *dir;
	char * occ,  space[128], line[128], buf[128];
	int i;
	struct dirent *filename;
	strcpy(space, "");
	strcpy(buf, "");
	strcpy(line, "|-----");
	if (!(dir = opendir(name))){
		printf("tree : '%s' : %s\n", name, strerror(errno));
		return;
	}
	if (!(filename = readdir(dir))){
		printf("%s\n", strerror(errno));
		return;
	}
	for(i=0;i<=a;i++)
		strcat(space, "|\t");
	if(a >= 0){
		occ = strrchr(name, '/');
		i = occ - name;
		strncpy(buf, name+i+1, strlen(name));	
	}
	do {
		if (filename->d_type == DT_DIR) {
			char path[1024];
			snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
			if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
				continue;
			a++;
			printf("%s%s", space, line);
			printf(KBLU"%s\n"RESET, filename->d_name);
			dcount++;
			folders(path);
		}
		else{             
			a = -1;
			fcount++;
		}
	}while ((filename = readdir(dir)));
	closedir(dir);
}

/*-h option. Prints help*/
void printhelp(void){
	FILE *fp;
	char c, *s="help.txt";
	fp = fopen(s, "r");
	if(fp == NULL){
		printf("cann't open file");
		exit(0);
	}
	c=fgetc(fp);
	while(c != EOF){
		printf("%c", c);
		c=fgetc(fp);
	}
	fclose(fp);
}

/*Displayes full path names with tree structure*/
void ffiles(const char *name)
{
	DIR *dir;
	char * occ,  space[128], line[128], buf[128];
	int i;
	struct dirent *filename;
	strcpy(space, "");
	strcpy(buf, "");
	strcpy(line, "|-----");
	if (!(dir = opendir(name))){
		printf("tree : '%s' : %s\n", name, strerror(errno));
		return;
	}
	if (!(filename = readdir(dir))){
		printf("%s\n", strerror(errno));
		return;
	}
	for(i=0;i<=a;i++)
		strcat(space, "|\t");
	printf("%s%s", space, line);
	printf(KBLU"%s\n"RESET, name);
	do {
		if (filename->d_type == DT_DIR) {
			char path[1024];
			snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
			if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
				continue;
			a++;
			dcount++;
			ffiles(path);
		}
		else{
			chk = check(filename->d_name);
			if(chk == 1) {
				printf("%s%s", space, line);
				printf(KMAG"%s/%s\n"RESET, name, filename->d_name);
			}
			else if(chk == 2) {
				printf("%s%s", space, line);
				printf(KRED"%s/%s\n"RESET, name, filename->d_name);
			}
			else if(chk == 3) {
				printf("%s%s", space, line);
				printf(KGRN"%s/%s\n"RESET, name, filename->d_name);
			}
			else {
				printf("%s%s%s/%s\n", space, line, name, filename->d_name);
			}
			a = -1;
			fcount++;
		}
	} while ((filename = readdir(dir)));
	closedir(dir);
}

/* -f and -i options used */
void fifiles(const char *name)
{
	DIR *dir;
	char * occ,  space[128], line[128], buf[128];
	int i;
	struct dirent *filename;
	strcpy(space, "");
	strcpy(buf, "");
	strcpy(line, "|-----");
	if (!(dir = opendir(name))){
	printf("tree : '%s' : %s\n", name, strerror(errno));
        return;
        }
	if (!(filename = readdir(dir))){
		printf("%s\n", strerror(errno));
		return;
	}
	
	strncpy(buf, name+1, strlen(name));	
	printf(KBLU"%s\n"RESET, buf);
	do {
		if (filename->d_type == DT_DIR) {
			char path[1024];
			snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
			if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
				continue;
			a++;
			dcount++;
			fifiles(path);
		}
		else{
			chk = check(filename->d_name);
			if(chk == 1) {
				printf(KMAG"%s/%s\n"RESET, name, filename->d_name);
			}
			else if(chk == 2) {
				printf(KRED"%s/%s\n"RESET, name, filename->d_name);
			}
			else if (chk == 3) {
				printf(KGRN"%s/%s\n"RESET, name, filename->d_name);
			}
			else {
			printf("%s/%s\n", name, filename->d_name);
			}
			
			a = -1;
			fcount++;
		}
	} while ((filename = readdir(dir)));
	closedir(dir);
}

int main(int argc, char *argv[]){
	if(argc == 2) {
		if(argv[1] == NULL){ 
			files(".");
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}
		if(strcmp(argv[1],".") == 0){
			files(".");
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}
		if(strcmp(argv[1],"-h") == 0){
			printhelp();
			return 0;
		}
		else {
			files(argv[1]);
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}		
	}
	else if(argc == 3) {
		
		if(strcmp(argv[2],"-d") == 0){
			folders(argv[1]);
			printf("%d folders\n", dcount);
			return 0;
		}
		if(strcmp(argv[2],"-f") == 0){
			ffiles(argv[1]);
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}
		if(strcmp(argv[2],"-i") == 0){
			ifiles(argv[1]);
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}
		if(strcmp(argv[2],"-l") == 0){
			files(argv[1]);
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}
	}
	else {
		if((strcmp(argv[2],"-f") && strcmp(argv[3],"-i")) == 0){
			fifiles(argv[1]);
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}
		if((strcmp(argv[2],"-i") && strcmp(argv[3],"-f")) == 0){
			fifiles(argv[1]);
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}
		else {
			files(".");
			printf("%d files and %d folders\n", fcount, dcount);
			return 0;
		}
	}
	return 0;
}

int check(char *typechar) {
	if(strstr(typechar, ".avi")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".flv")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".mkv")!=NULL) {
		return 1;;
	}
	else if(strstr(typechar, ".3gp")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".mpg")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".mpeg")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".mp4")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".jpeg")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".npg")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".tif")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".gif")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".flv")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".bmp")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".png")!=NULL) {
		return 1;
	}
	else if(strstr(typechar, ".tar")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".tar.gz")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".zip")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".rar")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".7zip")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".iso")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".tar")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".gz2")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".bz")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".gz")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".rz")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".cab")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".car")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, ".jar")!=NULL) {
		return 2;
	}
	else if(strstr(typechar, "a.out")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".o")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".COFF")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".pdf")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".odp")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".docx")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".c")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".cpp")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".rtf")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".doc")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".pptx")!=NULL) {
		return 3;
	}
	else if(strstr(typechar, ".ppt")!=NULL) {
		return 3;
	}
	return 0;
}
	
