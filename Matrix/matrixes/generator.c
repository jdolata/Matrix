/*
* XnY matrixes filled with random values generator
* usage ./generator number_of_rows number_of_columns
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  //  printf("-------- START --------\n");
    if(argc!=4){
        printf("-------- ERROR -------- \n");
        printf("Invalid number of arguments(%d)\n",argc-1);
        printf("To run type: ./generator number_of_rows number_of_columns generated_file_name\n");
    printf("-------- STOP -------- \n");
    exit(0);
  }
    FILE *file;
    int rows= atoi(argv[1]);
    int columns = atoi(argv[2]);
    int **random=(int**)malloc(rows*sizeof(int *)); 
    int i=1, o, a;
    char name[100];
    srand(time(NULL));
    
    
    file=fopen(argv[3],"w");
    fprintf(file, "%d,%d\n",rows,columns);
    for(o = 0; o<columns; o++){
        random[o]=(int*)malloc(columns*sizeof(int));
        for(i = 0; i<rows; i++){
            random[o][i] = rand()%1000;
            fprintf(file,"%d ",random[o][i]);
        }
    fprintf(file,"\n");   
    }
    fclose(file);
//  printf("-------- STOP -------- \n");
    return 0;
}