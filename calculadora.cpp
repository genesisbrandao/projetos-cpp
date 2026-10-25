#include <iostream>
#include <cmath> // 1. NOVA BIBLIOTECA PARA FUNCOES MATEMATICAS

using namespace std;

int main() {
    int opcao = 0;
    double num1, num2, resultado;

    // O loop continua até o usuário digitar a opção 7 (Sair) 
    while (opcao != 7) {
        cout << "\n==========CALCULADORA C++ ========" << endl;
        cout << "1. Somar (+)" << endl;
        cout << "2. Subtrair (-)" << endl;
        cout << "3. Multiplicar (*)" << endl;
        cout << "4. Dividir (/)" << endl;
        cout << "5. Potenciacao (x^y)" << endl;
        cout << "6. Raiz quadrada (v^x)" << endl;
        cout << "7. Sair do programa" << endl;
        cout << "===================================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        // Se o usuário escolher sair, interrompemos o loop imediatamente
        if (opcao == 7) {
            cout << "Saindo da calculadora... Ate logo!" << endl;
            break;
        }

        // Se voce escolher Raiz Quadrada (opcao 6), precisamos apenas de UM numero
        if (opcao == 6) {
            cout <<"Digite o numero: ";
            cin >> num1;
        }         
        // Para outras opcoes (1 a 5), precisamos de DOIS numeros
         else if (opcao >= 1 && opcao <= 5) {
            cout << "Digite o primeiro numero: ";
            cin >> num1;
            cout << "Digite o segundo numero: ";
            cin >> num2;
        }

        // O SWITCH decide qual coonta fazer baseado na opcao escolhida
        switch(opcao) {
            case 1:
                resultado = num1 + num2;
                cout << "-> Resultado: " << resultado << endl;
                break; // O 'break' impede que ele execute os casos de baixo
            case 2:
                resultado = num1 - num2;
                cout << "-> Resultado: " << resultado << endl;
                break;
            case 3:
                resultado = num1 * num2;
                cout << "-> Resultado: " << resultado << endl;
                break;
            case 4:
                // Proteção para não deixar dividir por zero (erro matemático grave!)
                if (num2 == 0) {
                    cout << "-> Erro: Nao eh possivel dividir por zero!" << endl;
                } else {
                    resultado = num1 / num2;
                    cout << "-> Resultado: " << resultado << endl;
                }
                break;
            case 5:
                // 2. USO DA POTENCIA: num1 elevado a num2
                resultado = pow(num1, num2);
                cout << "-> Resultado: " << num1 << " elevado a " << num2 << " eh " << resultado << endl;
                break;
            case 6:
                // 3. USO DE RAIZ QUADRADA: Proteção para não aceitar numeros negativos
                if (num1 < 0) {
                    cout << "-> Erro: Nao existe raiz quadrada de numero negativo nos reais!" << endl;
                } else {
                    resultado = sqrt(num1);
                    cout << "-> Resultado: A raiz quadrada de " << num1 << " eh " << resultado << endl;
                }
                break;
            default:
                cout << "-> Opcao invalida! Tente novamente." << endl;
                break;
        

        }
    }

    return 0;
}               