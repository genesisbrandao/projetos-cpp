#include "includes.h"

using namespace std;

// ==================CLASSE DE JOGADOR ======
class Jogador {
 protected:
    string nome; int vida; int forca;
    // 1. A MOCHILA DO JOGADOR: Um mapa protegido chave-valor
    map<string, int> mochila;

 public:
    Jogador(string nomeInicial, int vidaInicial, int forcaInicial) {
      nome = nomeInicial; forca = forcaInicial; setVida(vidaInicial);
      //Itens iniciais de fábrica na mochila
      mochila["Pocao de Vida"] = 2;
    }
    virtual ~Jogador() {}

    void setVida(int novaVida) { vida = (novaVida < 0) ? 0 : (novaVida > 120 ? 120 : novaVida); }
    // MÉTODO PARA ATACAR: gera um dano baseado na forca + um fator aleatório
    int getVida() { return vida; }
    int getForca() { return forca; }
    string getNome() { return nome; }
    virtual int atacar() { return forca + (rand() % 6); }

    int qtdeItem(string nomeItem) { return mochila[nomeItem]; }
    void usarPocao() {
      if (mochila["Pocao de Vida"] > 0) {
          mochila["Pocao de vida"]--;
          setVida(vida + 30);
          cout << "\n[ITEM] " << nome << " bebeu uma Pocao de Vida e recuperou 30 de HP!" << endl;
      } else {
          throw runtime_error("Você nao tem nenhuma Pocao de Vida na mochila!");
      }
  }
};

// ==================CLASSE INIMIGO ==================
class Mago : public Jogador {
private:
    int mana;

public:
    Mago(string nomeMago, int vidaInicial, int forcaInicial) : Jogador(nomeMago, vidaInicial, forcaInicial) {
         mana = 50;
         mochila["Elixir de Mana"] = 2; // Magos ganham elixires extras
    }

    int getMana() { return mana; }

    int lancarBolaDeFogo() {
      if (mana >= 20) { mana -= 20; cout << "\n[FEITICO] Bola de Fogo conjurada!" << endl; return forca * 2 + (rand() % 10); }
      else { cout << "\n[AVISO] Mana insuficiente! Executando ataque cajado normal... " << endl; return atacar(); }
    }

    void curar() {
        if (mana >= 15) { mana -= 15; int cura = 30 + (rand() % 11); setVida(vida + cura); cout << "\n[FEITICO] usou Magia de Cura e recuperou " << cura << " HP!" << endl; }
        else { cout << "\n[AVISO] Mana insuficiente para curar!" << endl; }
    }

    void usarElixir() {
      if (mochila["Elixir de Mana"] > 0) {
          mochila["Elixir de Mana"]--; mana += 25;
          cout << "\n[ITEM] " << nome << " bebeu um Elixir de Mana e recuperou 25 de MP!" << endl;
      } else { throw runtime_error("Você nao tem nenhum Elixir de Mana na mochila!"); }
    }
};

class Inimigo {
  protected: string tipo; int vida; int forca;
  public:
      Inimigo(string tipoInicial, int vidaInicial, int forcaInicial) { tipo = tipoInicial; vida = vidaInicial; forca = forcaInicial; }
      virtual ~Inimigo() {}
      void setVida(int novaVida) { vida = (novaVida < 0) ? 0 : novaVida; }
      int getVida() { return vida; }
      string getTipo() { return tipo; }
      virtual int atacar() { return forca + (rand() % 4); }

};
class Chefao : public Inimigo {
  public:
    Chefao(string nomeChefao, int vidaInicial, int forcaInicial) : Inimigo(nomeChefao, vidaInicial, forcaInicial) {}
    int atacar() override {
     if ((rand() % 100) > 70) { cout << "\n[CUIDADO] O " << tipo << " desferiu um GOLPE CRITICO DEVASTADOR!" << endl; return (forca + (rand() % 6 )) * 2; }
      return forca + (rand() % 6);

   }
};

// =================== PROGRAMA PRINCIPAL =============
int main() {
  srand(time(0)); // Somente para os danos aleatórios 

  cout << " =========================================== " << endl;
  cout << " === BEM-VINDO AO MINI-RPG: DE TURNO V5.0 === " << endl;
  cout << " =========================================== " << endl;

  string nomeDoUsuario;
  cout << "Digite seu nome aqui: ";
  getline(cin, nomeDoUsuario);
  if (nomeDoUsuario.empty()) nomeDoUsuario = "Heroi Anonimo";

  cout << "\nEscolha a sua classe:\n1. Guerreiro\n2. Mago\nEscolhas: ";
  int classeEscolhida; cin >> classeEscolhida;

  unique_ptr<Jogador> heroi = nullptr; bool ehMago = false;
  if (classeEscolhida == 2) { heroi = make_unique<Mago>(nomeDoUsuario, 90, 10); ehMago = true; }
  else { heroi = make_unique<Jogador>(nomeDoUsuario, 120, 22); }

  cout << "\nEscolha a dificuldade do combate:\n1. Normal\n2. Dificil (CHEFAO)\nEscolha: ";
  int dificuldade; cin >> dificuldade;
  unique_ptr<Inimigo> monstro = (dificuldade == 2) ? (unique_ptr<Inimigo>)make_unique<Chefao>("Dragao Negro", 110, 10) : make_unique<Inimigo>("Orc Guerreiro", 80, 11);

  int rodada = 1;

  // O LOOP DA BATALHA: Continua enquanto AMBOS estiverem vivos
  while (heroi->getVida() > 0 && monstro->getVida() > 0) {
    cout << "\n--- RODADA " << rodada << " ---" << endl;
    cout << heroi->getNome() << " (Vida: " << heroi->getVida();
    if (ehMago) cout << " | Mana: " << static_cast<Mago*>(heroi.get())->getMana();
    cout << ") vs " << monstro->getTipo() << "(Vida: " << monstro->getVida() << ")" << endl;

    int acao;
    bool turnoValido = false;

    while (!turnoValido) {
        try {
        if (ehMago) {

    // Menu de ação do Jogador
       cout << "Acoes:\n1. Espada/Cajado\n2. Bola de Fogo (20 MP)\n3. Curar (15 MP)\n4. Usar Pocao de Vida (" << heroi->qtdeItem("Pocao de Vida") << " rest.)\n5. Usar Elixir de Mana (" << static_cast<Mago*>(heroi.get())->qtdeItem("Elixir de Mana") << " rest.)\n6. Defender\nEscolha: ";
       cin >> acao;
    } else {
       cout << "Acoes:\n1. Atacar Espada\n2. Usar Pocao de Vida (" << heroi->qtdeItem("Pocao de Vida") << " rest.)\n3. Defender\nEscolha: ";
       cin >> acao;
       if (acao == 2) acao = 4;
       else if (acao == 3) acao = 6;
    }

    if (cin.fail() || acao < 1 || acao > 6) {
        cin.clear(); cin.ignore(1000, '\n');
        throw invalid_argument("Opcao invalida! Digite em numero valido do menu.");
    }

    int danoDoHeroi = 0;
    int danoDoInimigo = monstro->atacar();

    if (acao == 1) {
       danoDoHeroi = heroi->atacar(); monstro->setVida(monstro->getVida() - danoDoHeroi);
       cout << "-> Causou " << danoDoHeroi << " de dano!" << endl;
    }
    else if (acao == 2 && ehMago) {
         danoDoHeroi = static_cast<Mago*>(heroi.get())->lancarBolaDeFogo(); monstro->setVida(monstro->getVida() - danoDoHeroi);
        // Turno do Jogador Defendendo
    }
    else if (acao == 3 && ehMago) {
         static_cast<Mago*>(heroi.get())->curar();
    }
    else if (acao == 4) {
      heroi->usarPocao();
    }
    else if (acao == 5 && ehMago) {
        static_cast<Mago*>(heroi.get())->usarElixir();
    }
    else {
      cout << "-> Postura de Defesa!" << endl; danoDoInimigo /= 2;
    }
    // --- ATENCAO AQUI: Esta checagem de morte do mostro DEVE ficar FORA do if/else de cima! -----
    if (monstro->getVida() <= 0) { cout << "\n0 " << monstro->getTipo() << " foi completamente derrotado! " << endl; break; }

    heroi->setVida(heroi->getVida() - danoDoInimigo);
    cout << "-> 0 " << monstro->getTipo() << " contra-atacou: " << danoDoInimigo << " de dano!" << endl;

    turnoValido = true;
  }
    catch (const exception& e) {
      cout << "\n[ERRO DE COMANDO] " << e.what() << " Tente outra acao!" << endl << endl;
    }

  }
     if (heroi->getVida() <= 0) { cout << "\n" << heroi->getNome() << " tombou em batalha..." << endl; break; }
    rodada++;
  }
    ofstream arquivo_ranking("ranking.txt", ios::app);
    if (arquivo_ranking.is_open()) {
        arquivo_ranking << "Jogador: " << heroi->getNome() << " | Classe: " << (ehMago ? "Mago" : "Guerreiro") << " | Resultado: " << (heroi->getVida() > 0 ? "VITORIA" : "GAME OVER") << endl;
        arquivo_ranking.close();

  }
    return 0;
}
