#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

#define COLUMNS 10
#define ROWS 10

void populateMatrix(int matrix[][COLUMNS])
{
  int row;
  int col;

  for(row = 0; row < ROWS; row++)
  {
    for(col = 0; col < COLUMNS; col++)
    {
          matrix[row][col] = 1;
    }
  }
}

int sequentialSum(int matrix[][COLUMNS])
{
  int row;
  int col;
  int total = 0;

  for(row = 0; row < ROWS; row++)
  {
    for(col = 0; col < COLUMNS; col++)
    {
         total = total +  matrix[row][col];
    }
  }
 return total;
}

//
int main(int argc, char **argv)
{
  int nprocs;
  int rank;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  
  int matrix[ROWS][COLUMNS];
  populateMatrix(matrix);
  
  int seq_total;
  
  if(rank == 0)
  {
     seq_total = sequentialSum(matrix);
     printf("sequential sum is %d \n", seq_total);
  }
 
  // MPI_Reduce(&localSum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);  
  
  MPI_Finalize();
  return 0;
}
