#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp> // 1. A BIBLIOTECA DE MERCADO QUE VOCE INSTALOU!

using namespace std;
// Facilitador de sintaxe: apelida o pacote longo apenas como 'json'
using json = nlohmann::json;

int main() {
  cout << "=== TESTANDO ESTRUTURAÇÃO JSON (PADRAO DE MERCADO) ===" << endl;

  // 2. CRIANDO DADOS NO FORMATO JSON
  // A sintaxe é incrivelmente parecida com a do std::map!
  json dadosSalvos;
  dadosSalvos["nome"] = "wesley";
  dadosSalvos["classe"] = "Mago";
  dadosSalvos["vida"] = 90;
  dadosSalvos["mana"] = 50;
  // Podemos criar listas/vetores facilmente lá dentro:
  dadosSalvos["inventario"] = {"Pocao de Vida", "Elixir de Mana", "Cajado Basico"};

  // 3. GRAVADO O JSON NO HD
  ofstream arquivo_saida("progresso.json");
  if (arquivo_saida.is_open()) {
    // O parâmetro '4' faz o json quebrar as linhas bonitinho com 4 espaços (indentação)
    arquivo_saida << dadosSalvos.dump(4);
    arquivo_saida.close();
    cout << "[SISTEMA] Arquivo 'progresso.json' criado e salvo com sucesso!" << endl;
  }

  // 4. LENDO O ARQUIVO JSON DE VOLTA PARA O PROGRAMA
  cout << "\n[SISTEMA] Lendo dados do HD para simular carregamento..." << endl;
  fstream arquivo_entrada("progresso.json");

  if (arquivo_entrada.is_open()) {
     json dadosCarregados;
     arquivo_entrada >> dadosCarregados; // Puxa todo o arquivo estruturado de uma vez
     arquivo_entrada.close();

     // Extraindo os valores de dentro do JSON direto para variáveis c++
     string nomeHeroi = dadosCarregados["nome"];
     int vidaHeroi = dadosCarregados["vida"];
     int manaHeroi = dadosCarregados["mana"];
     string classeHeroi = dadosCarregados["classe"];

     // RENDERIZADO UMA INTERFACE LIMPA NA TELA

     cout << "\n===================================" << endl;
     cout << "===      PERSONAGEM CARREGADO     ===" << endl;
     cout << "=====================================" << endl;
     cout << " NOME:  " << nomeHeroi << " o " << classeHeroi << endl;
     cout << " HP:    " << vidaHeroi << " pontos" << endl;
     cout << " MANA:  " << manaHeroi << " MP" << endl;
     cout << "--------------------------------------" << endl;
     cout << "-> ITENS NA MOCHILA: " << endl;

     // LOOP SEGURO: Varre a lista 'inventario' de dentro do JSON de forma organizada
     for (auto& item : dadosCarregados["inventario"]) {
       // O .get<string>() garante que o texto saia limpo, sem as aspas do JSON
       cout << " - " << item.get<string>() << endl;
     }
     cout << "========================================" << endl;
  }
  return 0;
}
