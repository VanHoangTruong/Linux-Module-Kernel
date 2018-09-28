#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#define DEVICE "/dev/my_module"

int main(){
	int  fd; 
	char read_buf[4];
	fd = open(DEVICE,O_RDWR);  
	if (fd==-1){
		printf("failed\n");
		exit(-1);
	}
	int ret ;
	ret =read(fd,read_buf,sizeof(read_buf));
	int randomNumber = *((int *)read_buf);
	printf("The random Number is: %d\n",randomNumber);
	close(fd);

	return 0;
}