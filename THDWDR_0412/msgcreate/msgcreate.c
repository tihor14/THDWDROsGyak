/* 	msgcreate.c	*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// kulcs
#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} sendbuf, *msgp;		/* message buffer es pointere */

int main()
{
	int msgid;		/* uzenetsor azonosito */
	key_t key;		/* kulcs az uzenetsorhoz */
	int msgflg;		/* flag a kreaciohoz, uzenetkuldeshez */
	int ret, msgsz;		/* return es meret */

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT; // jogosultsag + letrehozas flag
	msgid = msgget(key, msgflg);
 	if (msgid == -1) {
                perror(": msgget() nem sikerult!");
                exit(-1);
        }
	printf("Az msgid letrejott: %d, %x\n", msgid,msgid);

	msgp        = &sendbuf;
	msgp->mtype = 1;   			/* tipus = text */
 	strcpy(msgp->mtext,"Egyik uzenet");
	msgsz       = strlen(msgp->mtext) + 1;	/* az uzenet hossza */
	/* bekuldes az uzenetsorba */
        ret = msgsnd(msgid,(struct msgbuf *)msgp, msgsz, msgflg);

	printf("Az 1. msgsnd() visszaadott: %d\n", ret);
	printf("A kikuldott uzenet: %s\n", msgp->mtext);

	strcpy(msgp->mtext,"Masik uzenet");
	msgsz       = strlen(msgp->mtext) + 1;
	ret = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("A 2.  msgsnd visszaadott: %d\n", ret);
	printf("A kikuldott uzenet: %s\n", msgp->mtext);

	exit(0);
}
