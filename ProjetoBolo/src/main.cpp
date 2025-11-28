#include <iostream>
#include "ascii/componentes.cpp"
#include "./includes/Usuario.h"
#include "./includes/ControllerUsuario.h"
#include "./includes/SessaoUsuario.h"
#include "./patterns/Builder/BoloBuilder.cpp"
#include "./patterns/CoR/Handler.cpp"

void criarPedidos(Bolo* bolo){
    ofstream arquivo("pedidos.txt", ios::app); 

        if (arquivo.is_open()) {
            
            // Escreve a linha no arquivo
            arquivo << bolo->saborMassa << ";" 
                    << bolo->recheio << ";" 
                    << bolo->cobertura << ";"
                    << bolo->forma << ";"
                    << bolo->quilo << ";"
                    << bolo->numAndares << ";"
                    << "sem decoracao"
                    << endl;  

            arquivo.close();
}
}

int main(){

    ControllerUsuario userControl = ControllerUsuario();

    desenharLinha();
    desenharCabecalho();
    desenharLinha();
    
    int opcao = -1;

    while (opcao != 0) {
        limparTela();
        desenharCabecalho();

        if (!SessaoUsuario::getInstance()->isLogado()) {
            cout << "STATUS: Deslogado" << endl;
            cout << "----------------------------------------" << endl;
            cout << "1. Login" << endl;
            cout << "2. Cadastrar Novo Atendente" << endl;
            cout << "0. Sair do Sistema" << endl;
            cout << "----------------------------------------" << endl;
            cout << ">> Opcao: ";
            cin >> opcao;

            if (opcao == 1) {
                string l, s , confirmacaoSenha;
                cout << "\n--- LOGIN ---" << endl;
                cout << "Usuario: "; cin >> l;
                cout << "Senha: ";   cin >> s;
               
                if (userControl.autenticar(l, s)) {
                    cout << "\nLogin realizado com sucesso!" << endl;
                } else {
                    cout << "\n[ERRO] Usuario ou senha incorretos." << endl;
                }
                pausar();


            } else if (opcao == 2) { // CADASTRO
                string l, s, n, confSenha;
                cout << "\n--- NOVO CADASTRO ---" << endl;
                cout << "Digite o Login: "; cin >> l;
                cout << "Digite o Nome: ";  
                cin.ignore(); getline(cin, n); // getline para aceitar espaços no nome
                cout << "Digite a Senha: "; cin >> s;
                cout << "Digite a Senha novamente: "; cin >> confSenha;
                
                if(s == confSenha){
                     if(userControl.cadastrarUsuario(l, s, n)){
                        cout << "\nUsuario cadastrado! Faca login para entrar." << endl;
                        pausar();
                    }else{
                        cout << "\nNão foi possivel realizar o cadastro" << endl;
                        pausar();
                    }
                }else{
                    cout << "\nSenhas não são iguais" << endl;
                    pausar();
                }
                

            } else if (opcao == 0) {
                cout << "Saindo..." << endl;
                break; // Sai do While
            } else {
                cout << "Opcao invalida!" << endl; pausar();
            }

        } 
        else {
            cout << "BEM-VINDO(A), " << SessaoUsuario::getInstance()->getNomeUsuario() << "!" << endl;
            cout << "----------------------------------------" << endl;
            cout << "1. Anotar Pedido (Personalizado)" << endl;
            cout << "2. Ver Bolos Prontos" << endl;
            cout << "3. Ver Historico de Pedidos" << endl;
            cout << "4. Deslogar (Sair da conta)" << endl;
            cout << "0. Encerrar Programa" << endl;
            cout << "----------------------------------------" << endl;
            cout << ">> Opcao: ";
            cin >> opcao;

            switch (opcao) {
                case 1:
                    BoloBuilder* builder = new BoloBuilder();

                    // 1. Instancia todos os passos
                    Handler* passo1 = new TelaMassa();
                    Handler* passo2 = new TelaRecheio();
                    Handler* passo3 = new TelaCobertura();
                    Handler* passo4 = new TelaForma();   // Novo
                    Handler* passo5 = new TelaPeso();    // Novo
                    Handler* passo6 = new TelaAndares(); // Novo

                    // 2. Liga a corrente (Massa -> Recheio -> Cobertura -> Forma -> Peso -> Andares)
                    passo1->setNext(passo2)
                        ->setNext(passo3)
                        ->setNext(passo4)
                        ->setNext(passo5)
                        ->setNext(passo6);

                    // 3. Inicia o processo
                    passo1->handle(builder);

                    // 4. Verifica se deu certo
                    Bolo* bolo = builder->getBolo();

                    criarPedidos(bolo);
                    // Limpeza
                    delete builder;
                    delete bolo; 
                    delete passo1; delete passo2; delete passo3; 
                    delete passo4; delete passo5; delete passo6;
                    
                    pausar();
                    break;
        
                case 2:
                    cout << "\n[TODO] Lista de bolos do estoque..." << endl;
                    pausar();
                    break;
                case 3:
                    cout << "\n[TODO] Leitura do arquivo de logs..." << endl;
                    pausar();
                    break;
                case 4:
                    userControl.logout();
                    cout << "\nVoce foi deslogado." << endl;
                    pausar();
                    break;
                case 0:
                    cout << "Encerrando..." << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl; pausar();
            }
        }
    }
    return 0;
}