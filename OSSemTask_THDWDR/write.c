#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h> 
#include<fcntl.h> 
#include<signal.h> 


int main(int argc, char* argv[]){
        int num[]={5,3,6}; // haromszog oldalai
        if(mkfifo("myfifo",0777) == -1)//fifo letrehozasa
        {
            printf("Hiba a fajl keszitese kozben!\n");
        }
        int fd=open("myfifo",O_WRONLY); //fifo megnyitasa olvasasi joggal
        printf("megnyitva\n");
        int i;
        for(i=0;i<3;i++)//fifoba iras
        {

            if(write(fd,&num[i],sizeof(int))==-1)
            {
                printf("Hiba");
            }
            else{
                printf("%d. szam(%d) irasa\n",i,num[i]);
            }
        }
        close(fd);//cso bezarasa
        printf("Varok 3 mp-t az eredmenyre...\n");
        sleep(3);
        int result[4];//megoldas tarolasa
        int fd2= open("result",O_RDONLY);//megoldas fifo olvasasa
        if(fd == -1)
        {
            printf("Hiba a megnyitasban!");
        }
        int j;
        for(j=0;j<4;j++)//kiolvasas
        {
            if(read(fd2,&result[i],sizeof(int))==-1)
            printf("Hiba");
        }
        printf("a= %d, b= %d, c= %d,result= %d\n",num[0],num[1],num[2],result[3]);
        return 0;

    }