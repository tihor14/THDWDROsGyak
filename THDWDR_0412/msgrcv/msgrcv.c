/*	msgrcv.c	*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// kulcs
#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} recvbuf, *msgp;		/* message buffer es pointere */

struct msqid_ds ds, *buf;	/* uzenetsorhoz asszocialt struktura
					 es pointere*/

int main()
{
	int msgid;		/* uzenetsor azonosito */
	key_t key;		/* kulcs az uzenetsorhoz */
	int mtype, msgflg;	/* tipus, flag */
	int ret, msgsz;		/* return es meret */

	key = MSGKEY;		/* beallitom a kulcsot */
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(key, msgflg);
 	if (msgid == -1) {
                perror("msgget() nem sikerult");
                exit(-1);
        }
	printf("Az msgid: %d\n",msgid);

	msgp = &recvbuf;	/* uzenetfogado buffer cime */
	buf = &ds;		/* uzenetsor jellemzo adataihoz */
	msgsz = 20;		/* max hossz */
	mtype = 0;		/* minden tipust varok */

	ret = msgctl(msgid, IPC_STAT, buf); /* uzenetsor adatokat lekerdezem */
	printf("Az uzenetek szama az uzenetsorban: %d\n", buf->msg_qnum);

	while (buf->msg_qnum) {		/* van-e uzenet?*/
		/* veszem a kovetkezo uzenetet: */
		ret = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
		printf("msgrcv() visszaadta: %d, a kapott uzenet: %s\n",ret, msgp->mtext);
		ret = msgctl(msgid, IPC_STAT, buf); /* uzenetsor adatokat lekerdezem,
						     benne azt is, hany uzenet van meg */
	}

	exit(0);
}