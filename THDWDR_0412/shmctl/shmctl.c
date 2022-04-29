/* 	shmctl.c	*/
/*	shmcreate.c-vel keszitett osztott memoria szegmens
        statusanak lekerdezesere, a szegmens megszuntetesere
	alkalmazhato program. 
	IPC_STAT parancs a status lekerdezest,
	IPC_RMID parancs a megszuntetest keri.
 	A statusbol csak a szegmens meretet es annak a processznek
	azonositojat irja ki, amelyik utoljara operalt a szegmensen.
*/

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
	int rtn;		/* rensz.hivas visszter. ertek */
	int cmd;		/* parancskod */
	struct shmid_ds shmid_ds, *buf; /* adatstruktura a status
					   adatok fogadasahoz */
	buf = &shmid_ds;	/* es annak pointere */

	key = SHMKEY;

	shmflg = 0;	/* Nincs IPC_CREAT, feltetelezzuk, az shmcreate() keszitett osztott memoria szegmenst */
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("Az shmget() system-call sikertelen!\n");
	    exit(-1);
	}

	/* Kerjuk be mit is szeretnenk */
	do
	{
		printf("\nAdd meg a parancs szamat:\n");
		printf("0. IPC_STAT (status)\n");
		printf("1. IPC_RMID (torles)\n> ");
		scanf("%d",&cmd);
	} while (cmd < 0 || cmd > 1);

	switch (cmd)
	{
	    case 0:
		rtn = shmctl(shmid, IPC_STAT, buf);
		printf("Szegmens merete: %d\n",buf->shm_segsz);
		printf("Utolso shmop()-os processz pid-je: %d\n",buf->shm_lpid);
		break;
	    case 1:
		rtn = shmctl(shmid, IPC_RMID, NULL);
		printf("Szegmens torolve. Hibakod: %d\n", rtn);
	}

	exit(0);

}
