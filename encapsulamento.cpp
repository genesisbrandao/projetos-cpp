#include <iostream>
#include <string>
using namespace std;

class Jogador {
private: // 1.TUDO ESTÁ BLINDADO! Ninguém de fora pode alterar ou ler direto.
    string nome;
    int vida;
    int forca;

public:
    // Construtor (ele pode mexer no private porque esté DENTRO da classe)
    Jogador (string nomeInicial, int vidaInicial, int forcaInicial) {
      nome = nomeInicial;
      forca = forcaInicial;

      // Usamoso nosso Setter aqui para garantir que o jogo comece com vida válida
      setVida(vidaInicial);

    }

    // 2.O seller (Função para alternar vida com segurança)
    void setVida(int novaVida) {
        if (novaVida < 0) {
            vida = 0; // Proteção: impede vida negativa
            cout << "[AVISO] Tentativa de vida negativa detectada. Ajustado para 0." << endl;
        } else if (novaVida > 100) {
            vida = 100; // Proteção: impede passar pelo limite máximo de vida
            cout << "[AVISO] Tentativa de vida acima do limite. Ajustado para 100." << endl;
        } else {
            vida = novaVida; // Valor vãlido, aceita a alteração

        }

      }

    // 3. O GETTER (Função apenas para ler a vida de fora da classe)
    int getVida() {
        return vida;
    }

    string getNome() {
        return nome;

    }

    void mostrarStatus() {
      cout << "Jogador: " << nome << " | Vida: " << vida << " | Forca: " << forca << endl;
    }

};

int main() {
  cout << "=== TESTANDO EMCAPSULAMENTO ===" << endl;

  //Criando jogador tentando trapacear com 500 de vida
  Jogador j1("Jquest", 500, 25);
  j1. mostrarStatus(); // vai mostrar vida 100 devido ao filtro do Setter!

  // Tentativa de bug (Se voce tentar romper o comentário da linha abaixo, o lazyvim/g++ vai dar erro de compilação!)
  // j1.vida = 50;

  // O jeito certo e profissional de alternar a vida agora é pelo Setter:
  cout << "\nTomando dano em batalha..." << endl;
  j1.setVida(j1.getVida() - 40); // pega a vida atual (100), e define nova vida (60)
  j1.mostrarStatus();

  return 0;

}
