#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

#define MAX_MSG_SIZE 100
#define MSG_KEY 12345

typedef struct message {
    long type;
    char body[MAX_MSG_SIZE];
} Message;

int main() {
    Message m;
    int msg_id;

    // Obtener el ID de la cola de mensajes
    msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        perror("Error al obtener la cola de mensajes");
        return 1;
    }

    while (1) {
        // Recibir el mensaje
        if (msgrcv(msg_id, &m, sizeof(m.body), 0, 0) == -1) {
            perror("Error al recibir el mensaje");
            return 1;
        }

        if(strcmp(m.body, "Terminado") == 0) {
            break;
        }
        printf("%d recibido: %s\n",getpid(), m.body);
    }

    printf("%d recibido: %s, se termina el programa\n", getpid(), m.body);
    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}
