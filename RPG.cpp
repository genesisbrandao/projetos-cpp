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
      vida = vidaInicial;

    }

    void setVida(int novaVida) { vida = (novaVida < 0) ? 0 : (novaVida > 100 ? 100 : novaVida); }
    int getVida() { return vida; }
    int getForce() { return forca; }
    string getNome() { return nome; }
    // MÉTODO PARA ATACAR: gera um dano baseado na forca + um fator aleatório
    int atacar() { return forca + (rand() % 6); }
};

// ==================CLASSE INIMIGO ==================
class Inimigo {
 protected:
    string tipo;
    int vida;
    int forca;
public:
    Inimigo(string tipoInicial, int vidaInicial, int forcaInicial) {
         tipo = tipoInicial;
         vida = vidaInicial; 
         forca = forcaInicial;
    }
    void setVida(int novaVida) { vida = (novaVida < 0) ? 0 : novaVida; }
    int getVida() { return vida; }
    int getForce() { return forca; }
    string getTipo() { return tipo; }

    virtual int atacar() { return forca + (rand() % 4); }
};

class Chefao : public Inimigo {
  public:
    Chefao(string nomeChefao, int vidaInicial, int forcaInicial)
        : Inimigo(nomeChefao, vidaInicial, forcaInicial) {}

  int atacar() override {
      int chanceCritico = (rand() % 100);
      if (chanceCritico > 70) {
        cout << "\n[CUIDADO] O " << tipo << " desferiu um GOLPE CRITICO DEVASTADOR!" << endl;
        return (forca + (rand() % 6 )) * 2;
      }
      return forca + (rand() % 6);
  }
};

// =================== PROGRAMA PRINCIPAL =============
int main() {
  srand(time(0)); // Somente para os danos aleatórios 

  cout << " =========================================== " << endl;
  cout << " === BEM-VINDO AO MINI-RPG: MODO CHEFAO === " << endl;
  cout << " =========================================== " << endl;

  string nomeDoUsuario;
  cout << "Digite seu nome aqui: ";
  getline(cin, nomeDoUsuario);

  if (nomeDoUsuario.empty()) {
    nomeDoUsuario = "Heroi Anonimo";
  }

  Jogador heroi(nomeDoUsuario, 120, 30);

  cout << "\nBoa Sorte, " << heroi.getNome() << "! Sua jornada comeca agora... " << endl;
  cout << " =========================================== " << endl;

  // Inicializando nossos combatentes usando construtores
    cout << "Escolha a dificuldade do combate:\n1. Normal (Orc Guerreiro)\n2. Dificil (Dragao Negro - CHEFAO)\nEscolha: ";
  int dificuldade;
  cin >> dificuldade;

  Inimigo* monstro = nullptr;

  if (dificuldade == 2) {
    monstro = new Chefao("Dragao Negro", 150, 14);
    cout << "\nALERTA DE BOSS: O lendario Dragao Negro emegiu!" << endl;
  } else {
      monstro = new Inimigo("Orc Guerreiro", 100, 30);
      cout << "\nUm Orc Guerreiro selvagem apareceu!" << endl;
  }
    cout << " =========================================== " << endl;
 
  int rodada = 1;

  // O LOOP DA BATALHA: Continua enquanto AMBOS estiverem vivos
  while (heroi.getVida() > 0 && monstro->getVida() > 0) {
    cout << "\n--- RODADA " << rodada << " ---" << endl;
    cout << heroi.getNome() << " (Vida: " << heroi.getVida() << ") vs "
         << monstro->getTipo() << " (Vida: " << monstro->getVida() << ")" << endl;

    // Menu de ação do Jogador
    cout << "Escolha sua acao:\n1. Atacar\n2. Defender\nEscolha: ";
    int acao;
    cin >> acao;

    int danoDoHeroi = 0;
    int danoDoInimigo = monstro->atacar();

    if (acao == 1) {
        // Turno de Jogador Atacando
        danoDoHeroi = heroi.atacar();
        monstro->setVida(monstro->getVida() - danoDoHeroi);
        cout << "-> " << heroi.getNome() << " causou " << danoDoHeroi << " de dano!" << endl;
    } else {
        // Turno do Jogador Defendendo
        cout << "-> " << heroi.getNome() << " defendeu!" << endl;
        danoDoInimigo = danoDoInimigo / 2; // Corta o dano do mosntro pela metade
    }

    // --- ATENCAO AQUI: Esta checagem de morte do mostro DEVE ficar FORA do if/else de cima! -----
    if (monstro->getVida() <= 0) {
       cout << "\n0 " << monstro->getTipo() << " foi derrotado!" << endl;
       break;
    }

    // Turno de Inimigo Atacando
    heroi.setVida(heroi.getVida() - danoDoInimigo);
    cout << "-> 0 " << monstro->getTipo() << " causou " << danoDoInimigo << " de dano!" << endl;

    // Se o herói morreu
    if (heroi.getVida() <= 0) {
        cout << "\n" << heroi.getNome() << " foi derrotado em combate..." << endl;
        break;

    }

    rodada++;

    }

    // FIM DA BATALHA
    cout << "\n================================" << endl;
    if (heroi.getVida() > 0) {
        cout << "Incrivel! voce derrotou o CHEFAO do jogo e salvou o reino! " << endl;
    } else {
      cout << "GAME OVER! O Chefao destruiu suas esperancas." << endl;

    }
    cout << "=====================================" << endl;

    delete monstro;

    return 0;
}
