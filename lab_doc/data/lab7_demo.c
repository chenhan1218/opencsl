#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i,status,oripid,ppid,npid,fn;
	int loop_num;
	float a = 1.05;

	if(argc==1){
	  loop_num = 1000;
	  fn = 50;
	}
	else{
	  loop_num = atoi(argv[2]);
	  fn = atoi(argv[1]); 
	  if(loop_num < 0 ) loop_num = 100000;
	}
	oripid = getpid();
	

	for(i=0;i<fn;i++){
	  if(getpid()==oripid) 
	    fork();
	}

	if(getpid() == oripid){ // parent
		for(i=0;i<fn;i++){
			waitpid(-1,&status,0);
		}
	}
	else{
		for(i=0;i<loop_num;i++)
		  a=a*a*a*a;
	}

	return 0;
}

