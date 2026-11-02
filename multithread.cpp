#include <iostream>
#include <thread> // 1. OBRIGATÓRIO PARA MULTIPROCESSAMENTO
#include <chrono> // Para usar timers (segundos, milissegundos)
#include <string>

using namespace std;

// 2. FUNÇÃO QUE VAI RODAR NO SEGUNDO NÚCLEO DA CPU
// Ela simula uma trilha sonora em texto ou um relógio correndo em tempo real
// O 'volatile bool& rodando' serve para controlarmos quando ela deve parar de fora
void efeitoTrilhaSonora(const bool& rodando) {
  while (rodando) { // Erro proposital de digitação aqui para testarmos sua águia! Mude para 'rodando'
 
      //Envia em "bip" visual ou sonoro a cada 3 segundos
      this_thread::sleep_for(chrono::seconds(5));
      if (rodando) {
        cout << "\n[MUSICA DE FUNDO] *Tensao aumenta na batalha...*" << endl;
      }
    }
    cout << "[SISTEMA] Thread da musica encerrada com sucesso!" << endl;
  }
  int main() {
    cout << "=== TESTANDO MULTITHREADING (C++ SENIOR) ===" << endl;

    bool jogoRodando = true;

    // 3. CRIANDO E DISPARANDO A THREAD SECUNDÁRIA
    // Passamos a função que ela vai executar e o parâmetro por referência (ref)
    thread tMusica(efeitoTrilhaSonora, ref(jogoRodando));

    // 4. O FLUXO PRINCIPAL CONTINUA AQUI
    // Repare que o loop de cima está rodando em paralelo enquanto você digita!
    string acao;
    cout << "\n[MENU] Digite ' atacar ' para golpear ou ' sair ' para fechar o jogo: " << endl;

    while (true) {
      cout << "Comando: ";
      cin >> acao;

      if (acao == " sair ") {
          cout << "\nEncerrando o combate..." << endl;
          break;
      } else {
          cout << "-> Voce executou a acao: " << acao << "!" << endl;
      }
     }

     // 5. ENCERRAMENTO SEGURO (Sincronização de Hardware)
     jogoRodando = false; // Avisa a thread secundária para parar o loop dela

     // O comando .join() obriga a Thread Principal a esperar a Thread secundária
     // terminar de limpar seus bytes antes do programa fechar na RAM do Arch
     tMusica.join();

     cout << "=== PROGRAMA FINALIZADO: Memoria de processadores limpa! ===" << endl;

     return 0;
}
