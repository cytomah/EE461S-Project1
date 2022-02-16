#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


int numofArg(const char input[]);
int parse(int argc, char* input);

struct job{
    char jstr[80];
    int pgid;
    int lpid, rpid;
    char status;
    struct job *next;
};

int main(int argc, char *argv[]){
    int argCount;
    char testString[80];
    char *str1, *token;
    char* saveptr1;

    while(1){
        printf("# ");
        char* input = readline("");
        strcpy(testString, input);
        //input[(int) strlen(input)] = '\0';
        argCount = numofArg(testString);
        parse(argCount, input);
    }
}

int parse(int argc, char* input){
    char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;
    int j;

    if (argc > 15) {
        fprintf(stderr, "Too many arguments passed through!");
        exit(EXIT_FAILURE);
    }

    for (j = 1, str1 = input; ; j++, str1 = NULL) {
        token = strtok_r(str1, "|", &saveptr1);
        printf("%s", token);
        if (token == NULL)
            break;

        for (str2 = token; ; str2 = NULL) {
            subtoken = strtok_r(str2, "<>", &saveptr2);
            if (subtoken == NULL)
                break;
            printf("%s", subtoken);
        }
    }

    return 0;
}

int numofArg(const char input[]){
    int count = 1;

    if(strncmp(input, "|", 1) || strncmp(input, ">", 1) || strncmp(input, "<", 1)){
        //Return some sort of error
        //exit(EXIT_FAILURE);
    }

    for(int i = 0; i < (int) strlen(input) - 1; i++){
        if(input[i] == ' ' && input[i+1] != '\n'){
            count++;
        }
    }
    return count;
}