#include <iostream>
#include <string>

using namespace std;

// 1. DEFININDO O TEMPLATE (O nosso tipo coringa 'T')
template <typename T>
T encontrarMaior(T a, T b) {
  return (a > b) ? a : b;

}

int main() {
  cout << "=== TESTANDO TEMPLATES (PROGRAMACAO GENERICA) ===" << endl;

  // 2. TESTANDO COM INTEIROS (O c++ substitui 'T' por 'int' nos bastidores)
  int i1 = 15, i2 = 42;
  cout << "Maior inteiro entre " << i1 << " e " << i2 << " eh: "
    << encontrarMaior(i1, i2) << endl;

  // 3. TESTANDO COM DECIMAIS (O C++ substitui 'T' por 'double' nos bastidores)
  double d1 = 45.67, d2 = 23.89;
  cout << "Maior decimal entre " << d1 << " e " << d2 << " eh: "
    << encontrarMaior(d1, d2) << endl;

  // 4.   MÁGICA EXTRA: FUNCIONA ATÉ COM STRINGS!
  // Na ordem alfabética, o C++ sabe quem vem depois.
  string s1 = "ArchLinux", s2 = "LazyVim";
  cout << "Maior string entre '" << s1 << "' e '" << s2 << "' eh: '"
    << encontrarMaior(s1, s2) << endl;

  return 0;
}
