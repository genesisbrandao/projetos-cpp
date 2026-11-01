#include <iostream>
#include <string>
#include <stdexcept> // 1. OBRIGATÓRIO PARA USAR EXCEÇÕES PADRÕES

using namespace std;

// Função de simulação que calcula a divisão entre dois números decimais
double dividir(double numerador, double denominador) {
  // Se o denominador for zero, o c++ normal daria um erro matemático grave.
  // Usamos o 'throw' para DISPARAR um erro customizado antes que o hardware quebre!
  if (denominador == 0) {
    throw runtime_error("Erro Critico: Tentativa de divisao por zero detectada!");
  }
  return numerador / denominador;

}

int main() {
  cout << "=== TESTANDO TRATAMENTO DE EXCECOES (C++ MODERNO) ===" << endl;

  double n1, n2, resultado;
  cout << "Digite o numerador: ";
  cin >> n1;
  cout << "Digite o denominador: ";
  cin >> n2;

  // 2. O BLOCO TRY (Tente): Envolve o código perigoso que pode dar erro
  try {
    cout << "\n[SISTEMA] Tentando realizar o calculo..." << endl;

    resultado = dividir(n1, n2);

    // Se a função 'dividir' lançar um erro, o c++ pula IMEDIATAMENTE
    // as linhas abaixo e vai direto para o bloco catch!
    cout << "-> Resultado da divisao: " << resultado << endl;
    cout << "[SISTEMA] Calculo concluido com sucesso!" << endl;
  }
  // 3. O BLOCO CATCH (Capture): Se der erro lá no try, ele captura o aviso aqui
  catch (const runtime_error& erro) {
    cout << "\n[TRAVA DE SEGURANÇA ACIONADA]" << endl;
    // O método .what() extrai o texto de erro que escrevemos lá no throw
    cout << "-> Motivo do bloqueio: " << erro.what() << endl;
    cout << "[SISTEMA] o erro foi trarado e o proograma continua rodando normalmente." << endl;
  }

  cout << "\n=== FIM DO PROGRAMA: Repare que o software nao travou! ===" << endl;

  return 0;
}
