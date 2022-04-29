#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
int db=0; 

void sig_handler(int signum){
 
  if(signum == SIGALRM){         //signal handler for SIGALRM
    printf("Inside handler function for SIGALRM,db= %d\n",db);
    alarm(2);
  }
  if(signum == SIGINT && db==0){         // elso SIGINT jel
    printf("\nVar 5 masodpercet....\n");
    db++;
    alarm(5);
  }else if(signum == SIGINT && db>0){     // masodik SIGINT jel,kilepes
    printf("\nEnd of the program,exiting\n");
    exit(0);
  }
  if(signum == SIGQUIT){        	 // signal handler for SIGQUIT
    printf("\nSIGQUIT: %d\n",signum);
  }

 
}
 
int main(){
 
  signal(SIGALRM,sig_handler); //  Register signal handler for SIGALRM
  signal(SIGINT,sig_handler); //  Register signal handler for SIGINT
  signal(SIGQUIT,sig_handler); //  Register signal handler for SIGQUIT

  alarm(2);  // Schedule the first alarm after 2 seconds
 
  for(int i=1;;i++){
    printf("%d : Inside main function\n",i);
    pause(); // waiting until signal is handled
  }
 
return 0;
}