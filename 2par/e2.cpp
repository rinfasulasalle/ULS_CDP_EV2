#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    int max = 1000, primos = 0;
    bool arr_primos[max+1];
    int start, end;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // dividimos el array entre los procesos
    start = rank * max / size;
    end = (rank + 1) * max / size;
    // cada proceso trabaja en su sección del array
    for (int i = start; i < end; i++) {
        if (i == 0 or i == 1) {
            arr_primos[0] = false;
            arr_primos[1] = false;
        }
        arr_primos[i] = true;
    }
    // sincronizamos los resultados de cada proceso en el proceso raíz
    int local_primos = 0;
    for (int i = start; i < end; i++) {
        if (arr_primos[i]) {
            local_primos++;
            for (int j = 2 * i; j <= max; j += i) {
                arr_primos[j] = false;
            }
        }
    }
    MPI_Reduce(&local_primos, &primos, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    // proceso raíz 
    if (rank == 0) {
        cout << "Primos: " << primos << endl;
        /*
        // imprimir primos OPCIONAL
        for (int x = 0; x < max; x++) {
            // 1 = primo, 0 = no primo
            cout << x << ":" << arr_primos[x] << endl;
        }*/
    }
    MPI_Finalize();
    return 0;
}





