#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==================CLASSE DE JOGADOR ======
class Jogador {
 protected:
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
         else if (novaVida > 120) vida = 120;
         else vida = novaVida;
    }
    // MÉTODO PARA ATACAR: gera um dano baseado na forca + um fator aleatório
    int getVida() { return vida; }
    int getForce() { return forca; }
    string getNome() { return nome; }

    virtual int atacar() { return forca + (rand() % 6); }
};

// ==================CLASSE INIMIGO ==================
class Mago : public Jogador {
 private:
    int mana;

public:
    Mago(string nomeMago, int vidaInicial, int forcaInicial)
         : Jogador(nomeMago, vidaInicial, forcaInicial) {
         mana = 50;
    }

    int getMana() { return mana; }

    int lancarBolaDeFogo() {
      if (mana >= 20) {
          mana -= 20;
          cout << "\n[FEITICO] " << nome << " conjurou uma BOLA DE FOGO DEVASTADORA! " << endl;
          return forca * 2 + (rand() % 10);
      } else {
          cout << "\n[AVISO] Mana insuficiente! Executando ataque cajado normal... " << endl;
       return atacar();

      }
  };

    void curar() {
        if (mana >= 15) {
            mana -= 15;
            int cura = 30 + (rand() % 11);
            setVida(vida + cura);
            cout << "\n[FEITICO]" << nome << "usou Magia de Cura e recuperou " << cura << " de vida!" << endl;
        } else {
            cout << "\n[AVISO] Mana insuficiente para curar!" << endl;
        }
    }
};

class Inimigo {
  protected:
    string tipo; int vida; int forca;
  public:
      Inimigo(string tipoInicial, int vidaInicial, int forcaInicial) {
           tipo = tipoInicial; vida = vidaInicial; forca = forcaInicial;
      }
      void setVida(int novaVida) { vida = (novaVida < 0) ? 0 : novaVida; }
      int getVida() { return vida; }
      string getTipo() { return tipo; }
      virtual int atacar() { return forca + (rand() % 4); }

};
class Chefao : public Inimigo {
  public:
    Chefao(string nomeChefao, int vidaInicial, int forcaInicial) : Inimigo(nomeChefao, vidaInicial, forcaInicial) {}
    int atacar() override {
     if ((rand() % 100) > 70) {
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
  if (nomeDoUsuario.empty()) nomeDoUsuario = "Heroi Anonimo";

  cout << "\nEscolha a sua classe:\n1. Guerreiro (Foco em Forca Bruta)\n2. Mago (Usa magia e Mana)\nEscolhas: ";
  int classeEscolhida;
  cin >> classeEscolhida;

  Jogador* heroi = nullptr;
  bool ehMago = false;

  if(classeEscolhida == 2) {
     heroi = new Mago(nomeDoUsuario, 90, 10);
     ehMago = true;
     cout << "\n" << heroi->getNome() << " o Mago pegou seu cajado!" << endl;
  } else {
     heroi = new Jogador(nomeDoUsuario, 120, 22);
     cout << "\n" << heroi->getNome() << " o Guerreiro empunhou sua espada!" << endl;
  }

  cout << "\nEscolha a dificuldade do combate:\n1. Normal\n2. Dificil (CHEFAO)\nEscolha: ";
  int dificuldade;  cin >> dificuldade;
  Inimigo* monstro = (dificuldade == 2) ? (Inimigo*)new Chefao("Dragao Negro", 110, 10) : new Inimigo("Orc Guerreiro", 80, 11);
 
  int rodada = 1;

  // O LOOP DA BATALHA: Continua enquanto AMBOS estiverem vivos
  while (heroi->getVida() > 0 && monstro->getVida() > 0) {
    cout << "\n--- RODADA " << rodada << " ---" << endl;
    cout << heroi->getNome() << " (Vida: " << heroi->getVida();
    if (ehMago) {

       cout << " | Mana: " << static_cast<Mago*>(heroi)->getMana();
    }
    cout << ") vs " << monstro->getTipo() << "(Vida: " << monstro->getVida() << ")" << endl;

    int acao;
    if (ehMago) {

    // Menu de ação do Jogador
       cout << "Escolha sua acao:\n1. Ataque cajado\n2. Bola de Fogo (custa 20 Mana)\n3.Curar (custa 15 de Mana)\n4. Defender\nEscolha: ";
       cin >> acao;
    } else {
       cout << "Escolha sua acao:\n1. Atacar Espada\n2. Defender\nEscolha: ";
       cin >> acao;
       if (acao == 2) acao = 4;
    }

    int danoDoHeroi = 0;
    int danoDoInimigo = monstro->atacar();

    if (acao == 1) {
        danoDoHeroi = heroi->atacar();
        monstro->setVida(monstro->getVida() - danoDoHeroi);
        cout << "-> " << heroi->getNome() << " atacou e causou " << danoDoHeroi << " de dano!" << endl;
    }
    else if (acao == 2 && ehMago) {
         danoDoHeroi = static_cast<Mago*>(heroi)->lancarBolaDeFogo();
         monstro->setVida(monstro->getVida() - danoDoHeroi);
        // Turno do Jogador Defendendo
        cout << "-> " << monstro->getTipo() << " sofreu " << danoDoHeroi << " de dano magico!" << endl;
    }
    else if (acao == 3 && ehMago) {
         static_cast<Mago*>(heroi)->curar();
         danoDoHeroi = 0;
    }
    else {
      cout << "->" << heroi->getNome() << " defendeu com maestria! " << endl;
      danoDoInimigo = danoDoInimigo / 2;

    }

    // --- ATENCAO AQUI: Esta checagem de morte do mostro DEVE ficar FORA do if/else de cima! -----
    if (monstro->getVida() <= 0) {
       cout << "\n0 " << monstro->getTipo() << " foi completamente derrotado! " << endl;
       break;
    }

     if (acao !=3 || (rand() % 100 > 30)) {
       heroi->setVida(heroi->getVida() - danoDoInimigo);
       cout << "-> 0 " << monstro->getTipo() << " contra-atacou e causou " << danoDoInimigo << " de dano!" << endl;
  }
     if (heroi->getVida() <= 0) {
         cout << "\n" << heroi->getNome() << " tombou em batalha..." << endl;
         break;
    }
    rodada++;
 }

    // FIM DA BATALHA
    cout << "\n================================" << endl;
    if (heroi->getVida() > 0) cout << "Incrivel! voce derrotou o CHEFAO do jogo e salvou o reino! " << endl;
    else cout << "GAME OVER! O Chefao destruiu suas esperancas." << endl;
    cout << "=====================================" << endl;

    delete monstro;
    delete heroi;
    return 0;
}
