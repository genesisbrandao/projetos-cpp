#include <iostream>
#include <string>
#include <map> // 1. OBRIGATÓRIO PARA USAR MAPAS

using namespace std;

int main() {
  cout << "=== TESTANDO INVENTARIO COM STD::MAP (C++ MODERNO) ===" << endl;

  // 2. DECLERAÇÃO DO MAPA: <Tipo_da_Chave, Tipo_do_Valor>
  // Nossa chave será uma 'string' (nome do item) e o valor será um 'int' (quantidade)
  map<string, int> mochila;


  // 3. ADICIONANDO ITENS DIRETO POR TEXTO (Super simples!)
  mochila["Pocao de Vida"] = 5;
  mochila["Elixir de Mana"] = 3;
  mochila["Antidoto"] = 1;

  // 4. ALTERANDO VALORES (Modo Dinâmico)
  cout << "\n[Acao] Voce encontrou mais Pocoes e usou seu Antidoto!" << endl;
  mochila["Pocao de Vida"] += 2; //Agora soma +2, virando 7
  mochila["Antidoto"] = 0;       //zerou o estoque

  // 5. LENDO UM ITEM ESPECÍFICO DIRETO PELO NOME
  cout << "-> Quantidade de Pocoes de Vida: " << mochila["Pocao de Vida"] << endl;
  cout << "-> Quantidade de Antidotos: " << mochila["Antidoto"] << endl;

  // 6. VERIFICANDO SE UM ITEM EXISTE ANTES DE USAR (.count())
  // O método .count () retorna 1 se a palavra existir no mapa ou 0 se não existir
  cout << "\n[Checagem] Procurando itens raros na mochila..." << endl;
  string itemProcurado = "Espada Lendaria";

  if (mochila.count(itemProcurado)) {
    cout << "-> " << itemProcurado << " encontrada! Quantidade: " << mochila[itemProcurado] << endl;
  } else {
    cout << "-> A " << itemProcurado << " nao esta na sua mochila!" << endl;
  }

  // 7. PERCORRENDO O MAPA INTEIRO COM LOOP 'FOR EACH'
  // Cada elemento de um mapap é um 'pair' (par) contendo .first (chave) e .second (valor)
  cout << "\n=== EXIBINDO TODO O SEU INVENTARIO ===" << endl;
  for (auto const& [nomeItem, quantidade] : mochila) {
    if (quantidade > 0) { // Só mostra o que você realmente tem no estoque
        cout << " - " << nomeItem << ": " << quantidade << " unidades" << endl;
    }
  }
  return 0;
 }
