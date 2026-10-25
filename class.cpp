#include <iostream>
#include <string>
using namespace std;

// 1. CRIANDO O MOLDE (A CLASSE)
class jogador {
public: // 'public' siginifica que qualquer parte do programa pode acssar essas informações
    string nome;
    int vida;
    int forca;
    
    // Isolar uma função dentro da classe se chama criar um método
    void mostrarStatus() {
        cout << "Jogador: " << nome << " | Vida: " << vida << " | Forca: " << forca << endl;
    }

    void receberDano(int dano) {
        vida = vida - dano;
        cout << nome << " tomou " << dano << " de dano!" << endl;
    }
};

int main() {
    cout << "=== PROGRAMACAO ORIENTADA A OBJETOS ===" << endl;

    // 2. CRIANDO O OBJETO REAL BASEADO NO MOLDE
    jogador j1;
    j1.nome = "Jquest";
    j1.vida = 100;
    j1.forca = 25;

    // Usando as funções (métodos) do objeto
    j1.mostrarStatus();
    j1.receberDano(30);
    j1.mostrarStatus();

    return 0;
}