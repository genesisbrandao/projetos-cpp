#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// ==================CLASSE DE JOGADOR ======
class Jogador {
  private:
    string nome;
    int vida;
    int forca;

  public:
    Jogador(string nomeInicial, int vidaInicial, int forcaInicial) {
      nome = nomeInicial;
      forca = forcaInicial;
      setVida(vidaInicial);

    }

    void setVida(int novaVida) {
      if (novaVida < 0) vida = 0;
      else if (novaVida > 100) vida = 100;
      else vida = novaVida;

    }

    int getVida() { return vida; }
    int getForce() { return forca; }
    string getNome() {return nome; }

    // MÉTODO PARA ATACAR: gera um dano baseado na forca + um fator aleatório
    int atacar() {
      int variacao = (rand() % 6); // Gera um bonus de 0 a 5 no ataque
      return forca + variacao;

    }
};

// ==================CLASSE INIMIGO ==================
class Inimigo {
  private:
    string tipo;
    int vida;
    int forca;

public:
    Inimigo(string tipoInicial, int vidaInicial, int forcaInicial) {
      tipo = tipoInicial;
      forca = forcaInicial;
      if (vidaInicial < 0) vida = 0;
      else vida = vidaInicial; // Inimigos podem ter mais de 100 de vida (chefões)
    }

    void setVida(int novaVida) {
      if (novaVida < 0) vida = 0;
      else vida = novaVida;
    }

    int getVida() { return vida; }
    int getForce() { return forca; }
    string getTipo() { return tipo; }

    int atacar() {
      int variacao = (rand() % 4); // Inimigo varia de 0 a 3 de bonus
      return forca + variacao;
   }

};

// =================== PROGRAMA PRINCIPAL =============
int main() {
  srand(time(0)); // Somente para os danos aleatórios 

  cout << " === BEM-VINDO AO MINI-RPG DE TURNOS === " << endl;

  // Inicializando nossos combatentes usando construtores
  Jogador herói("Heroi", 100, 15);
  Inimigo monstro("Orc Guerreiro", 100, 12);

  cout << "\nUm " << monstro.getTipo() << " Monstro Apareceu!" << endl;
  cout << herói.getNome() << "prepare-se para a batalha!" << endl;
  cout << "========================================" << endl;

  int rodada = 1;

  // O LOOP DA BATALHA: Continua enquanto AMBOS estiverem vivos
  while (herói.getVida() > 0 && monstro.getVida() > 0) {
    cout << "\n--- RODADA " << rodada << " ---" << endl;
    cout << herói.getNome() << " (Vida: " << herói.getVida() << ") vs "
         << monstro.getTipo() << " (Vida: " << monstro.getVida() << ")" << endl;

    // Menu de ação do Jogador
    cout << "Escolha sua acao:\n1. Atacar\n2. Defender (Reduz o proximo dano)\nEscolha: ";
    int acao;
    cin >> acao;

    int danoDoHeroi = 0;
    int danoDoInimigo = monstro.atacar();

    if (acao == 1) {
        // Turno de Jogador Atacando
        danoDoHeroi = herói.atacar();
        monstro.setVida(monstro.getVida() - danoDoHeroi);
        cout << "-> " << herói.getNome() << " atacou o " << monstro.getTipo()
             << " e causou " << danoDoHeroi << " de dano!" << endl;
    } else {
        // Turno do Jogador Defendendo
        cout << "-> " << herói.getNome() << " entrou em postura de defesa!" << endl;
        danoDoInimigo = danoDoInimigo / 2; // Corta o dano do mosntro pela metade

    }

    // --- ATENCAO AQUI: Esta checagem de morte do mostro DEVE ficar FORA do if/else de cima! -----
    if (monstro.getVida() <= 0) {
       cout << "\n0 " << monstro.getTipo() << " desabou no chao!" << endl;
       break;
    }

    // Turno de Inimigo Atacando
    herói.setVida(herói.getVida() - danoDoInimigo);
    cout << "-> 0 " << monstro.getTipo() << " contra-atacou e causou "
         << danoDoInimigo << " de dano!" << endl;

    // Se o herói morreu
    if (herói.getVida() <= 0) {
        cout << "\n" << herói.getNome() << " foi derrotado em combate..." << endl;
        break;

    }

    rodada++;

    }

    // FIM DA BATALHA
    cout << "\n================================" << endl;
    if (herói.getVida() > 0) {
        cout << "VITORIA! voce derrotou o monstro e sobreviveu com " << herói.getVida() << " de vida!" << endl;
    } else {
      cout << "GAME OVER! O mundo caiu em trevas." << endl;

    }
    cout << "=====================================" << endl;

    return 0;
}
