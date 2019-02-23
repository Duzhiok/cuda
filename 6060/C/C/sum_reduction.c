#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int rank;
  char hostname[256];
  int nprocs;
  int arr[10] = {0,1,2,3,5,7,8,10,13,14};
 
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  gethostname(hostname,255);
  
  int startIndex;
  int endIndex;
  startIndex = rank*(10/nprocs);
  endIndex = (rank+1)*(10/nprocs);
  int localSum = 0;
  int i;
  for(i=startIndex; i<endIndex; i++)
  {
    localSum += arr[i];
  } 
  
  printf("localSum by id = %d %d\n", localSum, rank);
 
  //int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype,
              // MPI_Op op, int root, MPI_Comm comm)
  int global_sum = 0;
  MPI_Reduce(&localSum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  printf("Final sum = %d \n", global_sum);
  
 // printf("Hello world!  I am process number: %d on host %s\n", rank, hostname);

  MPI_Finalize();

  return 0;
}
