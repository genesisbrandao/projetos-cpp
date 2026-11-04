#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

using namespace std;

int main() {
  cout << "==== BAU DINAMICO ====" << endl;

  map<string, int> bau;
   bau["moedas"] = 150;
   bau["pocao"] = 5;
   bau["chaves"] = 3;

  string item_buscado;
  bool itemValido = false;

  while (!itemValido) {
      try {
        cout << "\nNo baú há exatamente " << "quantidade: " << item_buscado << endl;
        getline(cin >> ws, item_buscado);
        int quantidade = bau.at(item_buscado);

        cout << "\nVoce retirou: " << item_buscado << endl;
        cout << "-> Quantidade disponivel no bau: " << quantidade << " unidades." << endl;
        itemValido = true;

      }
        catch (const out_of_range& erro) {
        cout << "\n[BLOQUEIO] Erro de Inventario!" << endl;
        cout << "Motivo: O item '" << item_buscado << "' nao existe dentro do bau!" << endl;
        cout << "[SISTEMA] Tente digitar o nome correto " << endl;
      }
    }
    return 0;
}
