#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd, ret;
	char buf[50];

	buf[0]=0;

    //O_RDONLY - O_RDWR - O_WRONLY -- ezekbol valamelyik kotelezo
    //O_APPEND - minden write utan a vegere pozicional
    //O_CREAT - letrehozas
    //O_TRUNC

	fd=open("neptunkod.txt",O_RDWR);
	if (fd == -1) {
	    perror("open() hiba tortent!");
	    exit(-1);
	}

	ret=write(fd,buf,1); // ret: mennyit irt ki valojaban
	printf("write() mondja: %d\n",ret);

	ret=read(fd,buf,50); // ret: mennyit sikerult olvasni
	printf("read() olvasott %d byteot, ami a kovetkezo: %s\n",ret,buf);
	buf[0]='a';

	ret=lseek(fd,0,SEEK_SET); // SEEK_CUR, SEEK_END - ret: hova allt be tenylegesen
	printf("lseek() mondja: %d\n",ret);



	close(fd);
}
