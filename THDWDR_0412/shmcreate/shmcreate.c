/*	shmcreate.c	*/
/*	SHMKEY  kulccsal kreal/azonosit osztott memoria szegmenst. */
/*	Azonositoja: shmid, amit kiiratunk */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHMKEY 69905L

int main()
{
	int shmid;		/* osztott mem azonosito */
	key_t key;		/* kulcs a shmem-hez */
	int size=512;		/* osztott szegmens meret byte-ban */
	int shmflg;		/* flag a jellemzokhoz */

	key = SHMKEY;

	/* Megnezzuk, van-e mar SHMKEY kulcsu es "size" meretu szegmens. */
	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   printf("Nincs meg szegmens! Keszitsuk el!\n");
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Az shmget() system-call sikertelen!\n");
	      exit(-1);
	   }
	} else printf("Van mar ilyen shm szegmens!\n");

	printf("\nAz shm szegmens azonositoja %d: \n", shmid);

	exit(0);
}