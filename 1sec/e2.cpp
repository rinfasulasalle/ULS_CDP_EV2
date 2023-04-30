#include <iostream>
using namespace std;
int main() {
  int max = 1001, primos = 0;
  bool arr_primos[max];
  // inicio todo el array true, todos son primos
  for (int i = 0; i <= max; i++) {
    if (i == 0 or i == 1) {
      arr_primos[0] = false; // 0 no primo
      arr_primos[1] = false; // 1 primo
    }
    arr_primos[i] = true;
  }
  for (int i = 2; i <= max; i++) {
    if (arr_primos[i]) { // si es primo, se incrementa el num de primos
      primos++;
      for (int j = 2 * i; j <= max; j += i) {
        arr_primos[j] = false;
      }
    }
  }
  cout << "Primos: " << primos << endl;
 
  return 0;
}
