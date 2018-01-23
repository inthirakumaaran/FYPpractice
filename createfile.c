#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  FILE * fp;
  int i;
  char name[12];
  sprintf(name, "file%d.txt", world_rank);
  fp = fopen (name,"w");
  srand((unsigned)(world_rank+1));
  for(i = 0; i < 250000000;i++){
    fprintf (fp,"%d\n",rand() % 1000);
  }
  fclose (fp);
  MPI_Finalize();
}