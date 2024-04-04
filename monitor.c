#include "libs/data.h"

typedef struct {
    int code;
    char* args[10];
    int nbArgs;
} send_t;

typedef struct {
    int code;
    char* args[10];
    int nbArgs;
} received_t;

void serial(generic quoi, char* req);
void deserial(generic quoi, char *msg);

int main(int argc, char *argv[]) {
    socket_t sock = connectToServer("0.0.0.0", 5000, argv[1], atoi(argv[2]), SOCK_STREAM);
    received_t data;

    while(1){
        socket_t sockClient = recevoir(sock, &data, deserial);
        printf("Received data: %d\n", data.code);
        sockClient.fd+=1;
    }
}

/**
 * \fn void serial(generic quoi, char* req) ;
 * 
 * @brief transforme les données en chaine de charactères  
 * @param quoi 
 * @param req 
 */
void serial(generic quoi, char* req) {
    send_t transQuoi = (*(send_t*)quoi);

    sprintf(req, "%d", transQuoi.code); // Convertit le code en char
    if(transQuoi.nbArgs == 0)
        return;
    for(int i = 0; i < transQuoi.nbArgs; i++) {
        strcat(req, "-");
        strcat(req, transQuoi.args[i]);
    }
}

/**
 * \fn void deserial(generic quoi, char* msg) ;
 * 
 * @brief transforme les chaine de charactères en données
 * @param quoi 
 * @param msg 
 */
void deserial(generic quoi, char *msg) {

    // Séparer les données selon le séparateur "-" et les ranger dans une array de strings
    char *token = strtok(msg, "-");
    ((received_t*)quoi)->code = atoi(token);
    ((received_t*)quoi)->nbArgs = 0;
    token = strtok(NULL, "-");
    int i = 0;
    if(token == NULL)
        return;
    int switchToken = atoi(token);
    switch (switchToken)
    {
    default:
        while(token != NULL){
            ((received_t*)quoi)->args[i] = token;
            ((received_t*)quoi)->nbArgs++;
            token = strtok(NULL, "-");
            i++;
        }
        break;
    }
}