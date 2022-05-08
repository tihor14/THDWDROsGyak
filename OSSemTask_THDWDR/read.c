#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h> 
#include<fcntl.h> 
#include<signal.h> 


int main(int argc, char* argv[]){
        int num[3];
        int fd= open("myfifo",O_RDONLY);//fifo olvasasa
        if(fd == -1)
        {
            printf("Hiba a megnyitasban!");
        }
        int i;
        for(i=0;i<3;i++)
        {
            if(read(fd,&num[i],sizeof(int))==-1)//fifo elemei tarolasa
            printf("Hiba");
        }

        printf("a= %d, b= %d, c= %d",num[0],num[1],num[2]);
        close(fd);

        int result[4];
        if(mkfifo("result",0777) == -1)
        {
            printf("\nHiba a fajl keszitese kozben!\n");
        }
        int fd2= open("result",O_WRONLY); //result fifo i­rasi joggal valo megnyitasa
        result[0]=num[0];
        result[1]=num[1];
        result[2]=num[2];
        if((result[0]+result[1])<result[2])//szerkeztheto-e?
        {
            result[3]=1;
        }
        else
        {
            result[3]=0;
        }
        int j;
        for(j=0;j<4;j++)
        {
            if(write(fd,&result[i],sizeof(int))==-1)//result fiofoba iras
            {
                printf("Hiba");
            }
        }
        close(fd);
        return 0;
    }