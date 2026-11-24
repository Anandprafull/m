#include <mpi.h>
#include <stdio.h>
int main(int argc,char** argv) {
    MPI_Init(&argc,&argv);
    int r,n;
    MPI_Comm_rank(MPI_COMM_WORLD,&r);
    MPI_Comm_size(MPI_COMM_WORLD,&n);
    printf("Hello %d of %d\n",r,n);
    MPI_Finalize();
}

