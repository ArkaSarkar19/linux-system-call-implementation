#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
int main(int argc, char** argv){
long ret =  syscall(354,atoi(argv[1]),argv[2]);
if(ret == 0){

	printf("success\n");
}
else{
	perror("Error");
	printf("errorno : %d\n",errno);
	return 0;

}}

