/*
 * matrixmultiplication.c
 * 
 * C[x,y] = A[x,y]*B[x,y]
 * 
 * Program do zadania 2. (3.5) Mnożenie macierzy przez macierz.
 * http://pl.wikipedia.org/wiki/Mno%C5%BCenie_macierzy
 * http://en.wikipedia.org/wiki/Matrix_multiplication 
 * 
 * compile with -lrt option for use High-resolution per-process timer from the CPU.
 * Running: ./matrixmultiplication  matrix_A_file_name matrix_B_file_name
 * 
 * Files with the matrix in the form:
 * x,y
 * a(1,1) a(1,2) ... a(1,y)
 * a(2,1) ...    ... a(2,y)
 * ...    ...    ... ...
 * a(x,1) ...    ... a(x,y)
 * 
 * where x is a row number, y is a column number and a(1,1),a(1,2),...,a(x,y) are next matrix elements.
 * 
 * Computational complexity =  Theta(n^3)
 * 
 * Copyright 2014 Jędrzej Dolata <jdolata@inf.ug.edu.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define BIL 1000000000.0 // Billion 10^9
 
int main(int argc, char **argv){
  printf("-------- START --------\n");
  if(argc!=3){
    printf("-------- ERROR -------- \n");
    printf("Invalid number of arguments(%d)\n",argc-1);
    printf("To run type: ./matrixmultiplication matrix_A_file_name matrix_B_file_name\n");
    printf("-------- STOP -------- \n");
    exit(0);
  }
  
  FILE *file;
  struct timespec tp0, tp1;
  double sp;
  int i,j,k;
  int rows_A,columns_A,rows_B,columns_B;
 
  printf("-------- DATA LOADING --------\n");
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
  file=fopen(argv[1],"r");
  if(file==NULL){
    printf("An error occurred while loading a %s file.\n", argv[1]);
    printf("-------- STOP --------\n");
    exit(0);
  }
  fscanf(file,"%d,%d\n",&rows_A,&columns_A);
  int matrixA[rows_A][columns_A];
  for(i=0; i<rows_A; i++){
    for(j=0; j<columns_A; j++){
      fscanf(file,"%d ",&matrixA[i][j]);
    }
  }
  fclose(file);
  printf("Matrix A loaded.\n");
 
  file=fopen(argv[2],"r");
  if(file==NULL) {
    printf("An error occurred while loading a %s file.\n", argv[2]);
    printf("-------- STOP --------\n");
    exit(0);
  }
  fscanf(file,"%d,%d\n",&rows_B,&columns_B);
  int matrixB[rows_B][columns_B];
  for(i=0; i<rows_B; i++){
    for(j=0; j<columns_B; j++){
      fscanf(file,"%d ",&matrixB[i][j]);
    }
  }  
  fclose(file);
  printf("Matrix B loaded.\n");  
 
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  sp=(tp1.tv_sec+tp1.tv_nsec/BIL)-(tp0.tv_sec+tp0.tv_nsec/BIL);
  
  
  printf("Data loading time: %3.10lfs\n",sp); 
  if(columns_A != rows_B){
    printf("Multiplication impossible, the number of columns in A does not equal the number of rows in B.\n");
     printf("-------- STOP --------\n");
    exit(0);
  }
  printf("Loaded data:\n"); 
  printf("-------- MATRIX A --------\n");
  for(i=0; i<rows_A; i++){
    for(j=0; j<columns_A; j++){
      printf("%d ",matrixA[i][j]);
    }
  printf("\n");
  }
 
  printf("-------- MATRIX B --------\n");
  for(i=0; i<rows_B; i++){
    for(j=0; j<columns_B; j++){
      printf("%d ",matrixB[i][j]);
    }
    printf("\n");
  }
 
  int matrixC[rows_A][columns_B];
  for(i=0; i<rows_A; i++){
	for(j=0; j<columns_B; j++){
      matrixC[i][j] = 0;
    }
  }
 
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
  for(i=0; i<rows_A; i++){
    for(j=0; j<columns_B; j++){
      for(k=0; k<rows_B; k++){
        matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
      }
    }
  }
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  sp=(tp1.tv_sec+tp1.tv_nsec/BIL)-(tp0.tv_sec+tp0.tv_nsec/BIL);
  printf("-------- MULTIPLICATION --------\n");
  printf("Multiplication of AxB time: %3.10lfs\n",sp);
 
  printf("Product matrix:\n");
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
  printf("-------- MATRIX C --------\n");
  for(i=0; i<rows_A; i++){
    for(j=0; j<columns_B; j++){
      printf("%d ",matrixC[i][j]);
    }
    printf("\n");
  }
  
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  sp=(tp1.tv_sec+tp1.tv_nsec/BIL)-(tp0.tv_sec+tp0.tv_nsec/BIL);
  printf("\nData writing time: %3.10lfs\n",sp);
  printf("-------- STOP --------\n");
  return 0;
}
