#include "libs/data.h"
#include "libs/menuLib.h"
#include "bomb.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    int code;
    char *args[10];
    int nbArgs;
} send_t;

typedef struct
{
    int code;
    char *args[10];
    int nbArgs;
} received_t;

module_t modules[30];
int moduleCount = 0;

void serial(generic quoi, char *req);
void deserial(generic quoi, char *msg);
void printModules();

int main()
{
    socket_t sock = connectToServer("127.0.0.1", 0, "0.0.0.0", 5000, SOCK_STREAM);
    printf("Connected to server\n");
    send_t dataSent = {
        .code = 1,
        .args = {"Hello", "World"},
        .nbArgs = 2};
    envoyer(sock, &dataSent, serial);
    // envoyer(sock, &dataSent, serial);
    printf("Data sent\n");

    // clear file tmpfile
    FILE *fp = fopen("tmpfile", "w");
    fclose(fp);

    fermerConnexion(sock);

    while(1) {
        // read tmpfile
        FILE *tmpfile = fopen("tmpfile", "r");
        if (tmpfile == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int i = 0;
        while ((read = getline(&line, &len, tmpfile)) != -1)
        {
            // Separate the space
            char *token = strtok(line, " ");
            strcpy(modules[i].name, token);
            // printf("Name: %s\n", modules[i].name);
            token = strtok(NULL, " ");
            modules[i].armed = atoi(token);
            // printf("Armed: %d\n", modules[i].armed);
            i++;    
        }  
        moduleCount=i;

        if(i > 0)
            printModules(); 
        
        fclose(tmpfile);
    }
        

    while (1)
    {
        // recevoirSuivant(sock, &data, deserial);
        // printf("Received data: %d\n", data.code);

        // if(data.code == 1) {
        //     module_t tempModule = {
        //         .name = "TEST",
        //         .armed = ARMED,
        //         .state = INACTIVE,
        //         .init = NULL
        //     };

        //     modules[atoi(data.args[0])] = tempModule;

        //     if(atoi(data.args[0]) > moduleCount)
        //         moduleCount = atoi(data.args[0]);
        //     break;
        // }

        // printModules();
    }

    return 0;
}

void printModules()
{
    char** modulePrint = malloc(moduleCount * 30 * sizeof(char*));
    for (int i = 0; i < moduleCount; i++)
    {
        modulePrint[i] = malloc(30 * sizeof(char));
        sprintf(modulePrint[i], "%d - %s - %s", i, modules[i].name, modules[i].armed == ARMED ? "ARMED" : "DISARMED");
        printf("%s\n", modulePrint[i]);
    }
    printf("\n");

    createMenu(modulePrint, moduleCount, "# IG2I-OS (Enter to refresh)#");
}

/**
 * \fn void serial(generic quoi, char* req) ;
 *
 * @brief transforme les données en chaine de charactères
 * @param quoi
 * @param req
 */
void serial(generic quoi, char *req)
{
    send_t transQuoi = (*(send_t *)quoi);

    sprintf(req, "%d", transQuoi.code); // Convertit le code en char
    if (transQuoi.nbArgs == 0)
        return;
    for (int i = 0; i < transQuoi.nbArgs; i++)
    {
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
void deserial(generic quoi, char *msg)
{

    // Séparer les données selon le séparateur "-" et les ranger dans une array de strings
    char *token = strtok(msg, "-");
    ((received_t *)quoi)->code = atoi(token);
    ((received_t *)quoi)->nbArgs = 0;
    token = strtok(NULL, "-");
    int i = 0;
    if (token == NULL)
        return;
    int switchToken = atoi(token);
    switch (switchToken)
    {
    default:
        while (token != NULL)
        {
            ((received_t *)quoi)->args[i] = token;
            ((received_t *)quoi)->nbArgs++;
            token = strtok(NULL, "-");
            i++;
        }
        break;
    }
}