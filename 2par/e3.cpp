#include <iostream>
#include <fstream>
#include <mpi.h>
// Para ejecutar mpic++ -o e3 e3.cpp -lmpi -lstdc++
// sino saldra error de dependencias
using namespace std;

int main(int argc, char* argv[]) {
  int rank, size;
  int local_spaces = 0, total_spaces = 0;
  MPI_File file;
  MPI_Offset filesize, chunksize, offset;
  char* chunk;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_File_open(MPI_COMM_WORLD, "blancos.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &file);
  MPI_File_get_size(file, &filesize);
  chunksize = filesize / size;
  offset = rank * chunksize;

  chunk = new char[chunksize + 1];
  MPI_File_set_view(file, offset, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
  MPI_File_read(file, chunk, chunksize, MPI_CHAR, MPI_STATUS_IGNORE);
  chunk[chunksize] = '\0';

  for (int i = 0; i < chunksize; ++i) {
    if (chunk[i] == ' ') {
      local_spaces++;
    }
  }

  MPI_Reduce(&local_spaces, &total_spaces, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    cout << "Hay " << total_spaces << " espacios" << endl;
  }

  MPI_File_close(&file);
  MPI_Finalize();

  delete[] chunk;

  return 0;
}
