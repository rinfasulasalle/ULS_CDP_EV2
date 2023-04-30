#include <iostream>
#include <fstream>
using namespace std;

int main() {
  ifstream txt("blancos.txt");
  int espacios = 0;
  char temp;
  while (txt.get(temp)) {
    if (temp == ' '){
      espacios++;
    }
  }
  cout << "Hay " << espacios << " espacios" << endl;
  txt.close();
  return 0;
}


