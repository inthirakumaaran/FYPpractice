#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    long sum=0;
    long total=0;
    long totalCount=0;
    long count =0;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE * fp;
    int i;
    char name[12];
    sprintf(name, "file%d.txt", world_rank);
    fp = fopen (name,"r");
    
   if (fp == NULL)
        exit(EXIT_FAILURE);

   while ((read = getline(&line, &len, fp)) != -1) {
        sum+=(long)atoi(line);
        count++;
        
   }
   if (world_rank != 0) {
    MPI_Send(&sum, 1, MPI_LONG,0,
         0, MPI_COMM_WORLD);
    MPI_Send(&count, 1, MPI_LONG,0,
         0, MPI_COMM_WORLD);
            
} else {
    total=sum;
    totalCount=count;
    MPI_Recv(&sum, 1, MPI_LONG, 1, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             total+=sum;
    MPI_Recv(&count, 1, MPI_LONG, 1, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             totalCount+=count;
    MPI_Recv(&sum, 1, MPI_LONG, 2, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             total+=sum;
    MPI_Recv(&count, 1, MPI_LONG, 2, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             totalCount+=count;
    MPI_Recv(&sum, 1, MPI_LONG, 3, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             total+=sum;
    MPI_Recv(&count, 1, MPI_LONG, 3, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             totalCount+=count;          
    printf("Toatal value: %li\n",total);
    printf("Toatal count: %li\n",totalCount);
    printf("Average is %li\n",total/totalCount);
    
}  
   fclose (fp);
    MPI_Finalize();
    
}

