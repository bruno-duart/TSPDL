#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

int** New_matrix(int row, int columns){
    int val;
    int **m = malloc(sizeof(int*) * row);
    for(int i = 0; i < row; i++)
        m[i] = malloc(sizeof(int) * columns);
    return m;
}

int *ini_array(int size)
{
    int *arr = malloc(sizeof(int) * size);
    return arr;
}


int main(){
    char* string = ReadFile("/mnt/c/Users/fabio/Desktop/meta/TSPDL/instances/bayg29_10_1.txt");
    //puts(string);

    int DIM;
    char *token = strtok(string, "\n");
    sscanf(token, "%d", &DIM);
    int **matrix = New_matrix(DIM, DIM);
    int *DEMAND = ini_array(DIM);
    int *DRAFT = ini_array(DIM);
    token = strtok(NULL, " ");

    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            sscanf(token, "%d", &matrix[i][j]);
            token = strtok(NULL, " ");
        }
    }

    for (int j = 0; j < DIM; ++j) {
        sscanf(token, "%d", &DEMAND[j]);
        token = strtok(NULL, " ");
    }

    for (int j = 0; j < DIM; ++j) {
        sscanf(token, "%d", &DRAFT[j]);
        token = strtok(NULL, " ");
    }

    // printf("%d", DIM);
    // printf("\n");

    // for (int i = 0; i < DIM; ++i) {
    //     for (int j = 0; j < DIM; ++j) 
    //         printf("%i ", matrix[i][j]);
    //     printf("\n");
    // }

    for (int j = 0; j < DIM; ++j) 
        printf("%i ", DEMAND[j]); 
    printf("\n");
    for (int j = 0; j < DIM; ++j) 
        printf("%i ", DRAFT[j]);
    // int line = 0;

    // for (int j = 0 ; j < strlen(string); j++){
    //     if( isdigit(string[j]) )
    //         printf("%c", string[j]);
    //     if(string == "\n"){
    //         line++;
    //     }
    // }
} 