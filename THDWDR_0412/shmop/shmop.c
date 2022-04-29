/* 	shmop.c		*/
/*	shmid-vel azonosit osztott memoria szegmenst. Ezutan
	a segm nevu pointervaltozot hasznalva a process virtualis
	cimtartomanyaba kapcsolja (attach) a szegmest (shmat() 
	rendszerhivas). Olvassa, irja ezt a cimtartomanyt, 
	vegul lekapcsolja (detach) a shmdt() rendszerhivassal).
*/
	
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define SHMKEY 69905L

int main()
{
	int shmid;		/* osztott mem azonosito */
	key_t key;		/* kulcs a shmem-hez */
	int size=512;		/* osztott szegmens meret byte-ban */
	int shmflg;		/* flag a jellemzokhoz */
	struct vmi {
		int  hossz;
		char szoveg[512-sizeof(int)]; /* az egesz merete 512, ezert a hossz valtozot levonjuk a tombbol */
	} *segm;		/* Ezt a strukturat kepezzuk a szegmensre */
	
	key = SHMKEY;

	shmflg = 0;	/* Nincs IPC_CREAT, feltetelezzuk, az shmcreate.c
				keszitett osztott memoria szegmenst */

	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("Az shmget system-call sikertelen!\n");
	    exit(-1);
	}

/* Attach - rakapcsolodunk*/

	shmflg = 00666 | SHM_RND;	/* RND az igazitashoz */
	segm = (struct vmi *)shmat(shmid, NULL, shmflg);
				/* Itt a NULL azt jelenti, hogy az OS-re bizom, milyen cimtartomanyt hasznaljon. */
	if (segm == (void *)-1) {
		perror("Sikertelen attach!\n");
		exit(-1);
	}

/* Sikeres attach utan a "segm" cimen ott az osztott memoria.
   Ha van benne valami, kiiratom, utana billentyuzetrol kerek uj beteendo szoveget */

/* Kerdes: ez alabbi jol fog mindig mukodni? */
	if (strlen(segm->szoveg) > 0) 
		printf("\n Regi szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);
 
	printf("\nUj szoveget kerek!\n");
	gets(segm->szoveg);
	printf("Az uj szoveg: %s\n",segm->szoveg);
	segm->hossz=strlen(segm->szoveg);
		
/* Detach */
	shmdt(segm);

	exit(0);
}