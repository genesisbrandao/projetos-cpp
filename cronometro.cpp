#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Função que a Thread Secundária vai executar em paralelo
void contagemRegressiva() {
  cout << "\n[CRONOMETRO] Iniciando contagem regressiva de seguranca..." << endl;

  for (int i = 5; i > 0; i--) {
    cout << "[RELOGIO CHRONO] " << i << " segundos restantes..." << endl;
    // Faz essa thread específica dormir por exatamente 1 segundo
    this_thread::sleep_for(chrono::seconds(1));
  }

  cout << "[CRONOMETRO] Tempo esgotado! Contagem finalizada." << endl;

}

int main() {
  cout << "=== CRONOMETRO DE BATALHA SEGURO ===" << endl;

  cout << "\n[SISTEMA] Disparando a contagem paralela em outro nucleo da CPU..." << endl;
  // 1. DISPARANDO A THREAD: Ela nasce e começa a rodar a função Imediatamente
  thread tRelogio(contagemRegressiva);
  // 2. A THREAD PRINCIPAL CONTINUA DAQUI:
  cout << "[MAIN] Enquanto o relogio corre ali em cima, o fluxo principal continua livre." << endl;
  cout << "[MAIN] Realizando calculos internos do jogo..." << endl;

  // 3. TRAVA DE SEGURANÇA CRÍTICA:
  // O .join() bloqueia o fim do main() e obriga o programa a esperar a thread 'tRelogio'
  // terminar todos os seus 5 segundos antes de avançar para o return 0.
  cout << "[MAIN] Aguardando o encerramento seguro da thread paralela..." << endl;
  tRelogio.join();

  cout << "\n=== FIM DO PROGRAMA: Ambas as threads se uniram e a RAM forma impecavel! ===" << endl;
  return 0;

}
