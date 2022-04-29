#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
        int     THDWDR[2];
        pid_t   childpid;
        char    string[20];
        char    readbuffer[80];

        pipe(THDWDR);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                //Gyerek 
		close(THDWDR[0]);
		printf("Gyermek processz,irja be a szoveget:\n");
		scanf("%s",string);
                write(THDWDR[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
		//Szulo 
                close(THDWDR[1]);
                read(THDWDR[0], readbuffer, sizeof(readbuffer));
                printf("Szulo processz, a kapott string: %s\n", readbuffer);
        }
        
        return(0);
}