#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "delay.h"

#define MAX_MSG_SIZE 100
#define MSG_KEY 12345

typedef struct message {
    long type;
    char body[MAX_MSG_SIZE];
} Message;

int main() {
    srand(getpid());
    Message m;
    int msg_id, msg_count = 1;

    // Crear la cola de mensajes
    msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        perror("Error al crear la cola de mensajes");
        return 1;
    }

    while (1) {
        delay(1,3);
        m.type = 1;  // Tipo de mensaje
        sprintf(m.body, "Mensaje %d-%d" , getpid(), msg_count);

        if(msg_count == 15) {
            sprintf(m.body, "Terminado");
        }

        // Enviar el mensaje
        if (msgsnd(msg_id, &m, sizeof(m.body), 0) == -1) {
            perror("Error al enviar el mensaje");
            return 1;
        }

        printf("%d enviado: %s\n",getpid(), m.body);

        if(strcmp(m.body, "Terminado") == 0) {
            break;
        }

        msg_count++;
    }

    return 0;
}
