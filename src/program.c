#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define SIZE 128

typedef enum { CEL, RES, SPE } Type;

char* resRegex = "\\(?\\+?(506)?\\)?[ -]?(2[0-9]{1})[ -]?([0-9]{2})[ -]?([0-9]{2})[ -]?([0-9]{2})";
char* celRegex = "\\(?\\+?(506)?\\)?[- ]?([1|3-9]{1}[0-9]{1})[- ]?([0-9]{2})[- ]?([0-9]{2})[- ]?([0-9]{2})$";
char* speRegex = "(^[0-9]{3}$)|(^[0-9]{4}$)";

struct nodeList {
    char* phone;
    Type type;
    struct nodeList* next;
} *head;

void newPhone(char* p, Type type) {
    struct nodeList* nl = NULL;
    nl = (struct nodeList*) malloc(sizeof(struct nodeList));
    nl->phone = (char *) malloc(1);
    strcpy(nl->phone, p);
    nl->type = type;
    nl->next = NULL;

    if (head == NULL)
        head = nl;
    else {
        nl->next = head;
        head = nl;
    }
}


int match(const char* string, char* pattern) {
    int status;
    regex_t re;

    if (string != NULL) {
        if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
            return(0);
        }
        status = regexec(&re, string, (size_t) 0, NULL, 0);
        regfree(&re);
        if (status != 0) {
            return (0);
        }
        return(1);
    } else {
        return (0);
    }
}

int readText() {
    FILE *fp;
    char str[SIZE];
    char* filename = "C:\\Users\\Javier\\lenguajesTxt\\test.txt";
    size_t len = sizeof(str);
    char* line = (char*) malloc(len);
    char* token;

    if (filename == NULL) {
        perror("Debe especificar un archivo de texto...");
        exit(1);
    }

    fp = fopen(filename, "r");

    if(line == NULL) {
        perror("Unable to allocate memory for the line buffer.");
        return 0;
    }

    while (fgets(str, sizeof(str), fp) != NULL) {
        strncpy(line, str, len);

        token = strtok(line, "\t");
        if (match(token, resRegex) == 1)
            newPhone(token, RES);
        else if (match(token, speRegex) == 1)
            newPhone(token, SPE);
        else if (match(token, celRegex) == 1)
            newPhone(token, CEL);

        while( token != NULL ) {
            token = strtok(NULL, "\t");
            if (match(token, resRegex) == 1)
                newPhone(token, RES);
            else if (match(token, speRegex) == 1)
                newPhone(token, SPE);
            else if (match(token, celRegex) == 1)
                newPhone(token, CEL);
        }
    }

    fclose(fp);
    free(line);
}

void printPhones() {
    struct nodeList* current = head;

    printf("\n****** Numeros identificados ******\n\n");
    if (current == NULL)
        printf("Lista vacia");
    else {
        while (current != NULL) {
            if (current->type == 0) {
                printf("Telefono: %s\n", current->phone);
                printf("Tipo: Celular\n\n ");
            } else if (current->type == 1) {
                printf("Telefono: %s\n", current->phone);
                printf("Tipo: Residencial\n\n ");
            } else if (current->type == 2) {
                printf("Telefono: %s\n", current->phone);
                printf("Tipo: Especial\n\n ");
            }
            current = current->next;
        }
    }
}

int main() {
    printf("\nBienvenidos a esta app\n");
    readText();
    printPhones();
    printf("\nGracias por usar esta App! ;)\n");

    return 0;
}