#include <stdio.h>
#include <time.h>
long num_steps = 100000;
double step = 1.0 / 100000.0;
int main() {
    clock_t tStart = clock();
    int i;
    double x, pi, sum = 0.0;
    for (i = 0; i < num_steps; ++i) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x*x);
    }
    pi = step * sum;
    printf("PI value = %f\n", pi);
    printf("Time taken: %.4fs\n",(double)(clock()-tStart)/CLOCKS_PER_SEC);
    return 0;
}


