#include <iostream>
#include <string>

using namespace std;

// 1. ESTRETURAS DIFERENTES DO JOGO
struct Item {
  string nome;
  string raridade;
  double peso;

};

struct Habilidade {
  string nome;
  int custoMana;
  int danoBase;

};

// 2. CLASSE TEMPLATE: O POP-UP GENÉRICO!
// Ele aceita QUALQUER tipo de dado (T) para ser o conteúdo da descrição
template <typename T>
class PopUpDescricao {
private:
  T conteudo;
  int larguraJanela;

public:
  PopUpDescricao(T dadosIniciais) : conteudo(dadosIniciais), larguraJanela(40) {}

  // Função que desenha as bordas genéricas da janela do pop-up na tela
  void renderizarJanela() {
    cout << "\n=================================" << endl;
    cout << "===    CAIXA DE INFORMACOES    ===" << endl;
    cout << "==================================" << endl;

    // Aqui chamamos uma função auxiliar que nós vamos escrever ali embaixo
    // para desenhar o miolo especifico de cada tipo de dado!
 desenharMiolo(conteudo);

    cout << "====================================" << endl;
}

private:
     // 3. SOBRECARGA INTELIGENTE: Como o miolo de um Item é diferente de uma Habilidade,
     // nós criamos versões específicas do desenho interno aqui dentro!
     void desenharMiolo(Item item) {
       cout << " ITEM: " << item.nome << endl;
       cout << " RARIDADE: [" << item.raridade << "]" << endl;
       cout << " PESO: " << item.peso << " kg" << endl;

     }

     void desenharMiolo(Habilidade hab) {
       cout << " HABILIDADE: " << hab.nome << endl;
       cout << " CUSTO DE MANA: " << hab.custoMana << " MP" << endl;
       cout << " DANO MAGICO: " << hab.danoBase << " de dano" << endl;
     }
};

int main() {
  cout << "=== SIMULADOR DE POP-UPS COM TEMPLATE ===" << endl;

  // Criando dados de teste
  Item espada = {"Espada de Diamante", "Lendaria", 4.5};
  Habilidade fogo = {"Bola de Fogo", 20, 75};

  // 4. USANDO O MESMO POP-UP PARA COISAS DIFERENTES!
  // Pop-up de Item
  PopUpDescricao<Item> popupEspada(espada);
  popupEspada.renderizarJanela();

  // Pop-up de Habilidade
  PopUpDescricao<Habilidade> popupMagia(fogo);
  popupMagia.renderizarJanela();

  return 0;
}
