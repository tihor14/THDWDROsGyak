/* 	msgctl.c 	 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// kulcs, lehet barmi egyedi
#define MSGKEY 654321L

int main()
{
	int msgid, msgflg,ret;
	key_t key;

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT; // jogosultsagok + letrehozas flag

	msgid = msgget(key, msgflg); // ha nincs akkor a get letre is hozza, mert volt IPC_CREAT flag is beallitva

	ret = msgctl(msgid, IPC_RMID, NULL);	// uzenetsor torles msgctl()-el, IPC_RMID !
	printf ("\n Visszatert: %d\n", ret);

	exit(0);
}