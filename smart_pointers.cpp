#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Inimigo {
    private:
    string tipo;
    public:
    Inimigo(string tipoInicial) : tipo(tipoInicial) {
        cout << "[CONSTRUTOR] " << tipo << " nasceu na memoria RAM!" << endl;

      }
      ~Inimigo() {
          cout << "[DESTRUTOR] " << tipo << " FOI DELETEDO AUTOMATICAMENTE!" << endl;

      }
      void rugir() {
          cout << tipo << " diz: VOU TE DESTRUIR!" << endl;

      }
  };

  int main() {
    cout << "=== TESTANDO SMART POINTERS (C++ MODERNO) ===" << endl;

    { cout << "\n--- Entrando no escopo interno ---" << endl;
     unique_ptr<Inimigo> monstro = make_unique<Inimigo>("Orc Mutante");
     monstro->rugir();
     cout << "--- Chegando ao fim do escopo interno ---" << endl;
     }
     cout << "\n--- Fora do escopo: Repare que o objeto já morreu lá em cima! ---" << endl;

     return 0;

    }
