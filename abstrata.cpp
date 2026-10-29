#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Inimigo {
  protected:
    string tipo;
    int vida;

    public:
    Inimigo(string tipoInicial, int vidaInicial) : tipo(tipoInicial), vida(vidaInicial) {}
    virtual ~Inimigo() {}

    int getVida() { return vida; }
    string getTipo() { return tipo; }

    virtual int atacar() = 0;

};

class Orc : public Inimigo {
  private:
    int forcaFisica;
  public:
    Orc(string nome) : Inimigo(nome, 60), forcaFisica(15) {}

    int atacar() override {
      cout << "\n-> o " << tipo << " balanca seu machado pesado!" << endl;
      return forcaFisica + (rand() % 5);

    }
};

class MagoNegro : public Inimigo {
  private:
    int poderMagico;
  public:
    MagoNegro(string nome) : Inimigo(nome, 40), poderMagico(22) {}

    int atacar() override {
      cout << "\n-> o " << tipo << " canaliza runas de energia das trevas!" << endl;
      return poderMagico + (rand() % 8);
    }
};

int main() {
  srand(time(0));
  cout << "=== TESTANDO CLASSES ABSTRATAS ===" << endl;

  Inimigo* monstro1 = new Orc("Orc Enfurecido");
  Inimigo* monstro2 = new MagoNegro("Mago de Sangue");

  int dano1 = monstro1->atacar();
  cout << "Dano causado: " << dano1 << endl;

  int dano2 = monstro2->atacar();
  cout << "Dano causado: " << dano2 << endl;

  delete monstro1;
  delete monstro2;

  return 0;

}





