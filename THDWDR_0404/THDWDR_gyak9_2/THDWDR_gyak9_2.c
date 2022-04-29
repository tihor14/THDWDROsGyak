#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void sig_handler(int signum){
 
  if(signum == SIGALRM){         //signal handler for SIGALRM
    //printf("Inside handler function for SIGALRM\n");
    alarm(1);
  }
  if(signum == SIGTERM){         // signal handler for SIGQUIT
    printf("Inside handler function for SIGTERM\n");
    alarm(3);
  }

 
}
 
int main(){
 
  signal(SIGALRM,sig_handler); //  Register signal handler for SIGALRM
  signal(SIGTERM,sig_handler); //  Register signal handler for SIGINT

  alarm(1);  // Schedule the first alarm after 1 seconds
 
  for(int i=1;i<15;i++){
    printf("%d : Inside main function\n",i);
    pause(); // waiting until signal is handled
    kill(getpid(),SIGTERM);
  }
 
return 0;
}