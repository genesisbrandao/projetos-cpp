#include <iostream>
#include <fstream> // Biblioteca para trabalhar com arquivos                        
#include <string>

using namespace std;

int main() {
    int opcao = 0;
    string texto_nota;
    string linha;

    while (opcao !=3) {
        cout << "\n=========== MEU DIARIO EM C++ ===========" << endl;
        cout << "1. Escrever nova nota" << endl;
        cout << "2. Ler notas salvas" << endl;
        cout << "3. Sair" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        
        // Limpa o caractere de "Enter" do teclado para não bugar a leitura de textos comprimidos
        cin.ignore();

        if (opcao == 1) {
           // 2. GRAVANDO NO ARQUIVO
           // ios::app siginifica "Append" (anexar). Ele adiciona o texto no final do arquivo sem apagar o que já existe lá.
           ofstream arquivo_saida("diario.txt", ios::app);

           if (arquivo_saida.is_open()) {
              cout << "Digite a sua nota/pensamento; ";
              getline(cin, texto_nota); //getline lẽ a linha inteira incluindo os espaços

              arquivo_saida << "- " << texto_nota << endl; // Grava no arquivo igualzinho faria no cout
              arquivo_saida.close(); // OBRIGATÓRIO: Sempre feche o arquivo apos usar!

              cout << "-> Nota salva com sucesso no arquivo 'diario.txt'!" << endl;
        } else {
              cout << "Erro ao abrir o arquivo para escrita!" << endl;
        }
               
    }
    else if (opcao == 2) {
        // 3. LENDO DO ARQUIVO
        ifstream arquivo_entrada("diario.txt");

        if (arquivo_entrada.is_open()) {
            cout << "\n--- SUAS NOTAS GUARDADAS ---" << endl;

            // Enquanto conseguir ler uma linha do arquivo, exibe ela na tela
            while (getline(arquivo_entrada, linha)) {
                cout << linha << endl;
            }
            
            arquivo_entrada.close(); // OBRIGATORIO fechar arquivo 
            cout << "----------------------------" << endl;
        } else {
            cout << "Nenhum diario encontrado ou o arquivo ainda nao foi criado!" << endl;    
        }
       
    }


    }

    return 0;
}
