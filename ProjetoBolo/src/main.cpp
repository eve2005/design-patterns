#include <iostream>
#include "ascii/componentes.cpp"
#include "./includes/Usuario.h"
#include "./includes/ControllerUsuario.h"
#include "./includes/SessaoUsuario.h"
#include "./includes/BoloBuilder.h"
#include "./includes/Handler.h"
#include "./includes/IBolo.h"
#include "./includes/Decorator.h"

void criarPedidos(IBolo* bolofinal){
    ofstream arquivo("../dados/pedidos.txt", ios::app); 

    if (arquivo.is_open()) {
        Bolo* bolo = bolofinal->getBolo();
        // Escreve a linha no arquivo
        arquivo << bolo->saborMassa << ";" 
                << bolo->recheio << ";" 
                << bolo->cobertura << ";"
                << bolo->forma << ";"
                << bolo->quilo << ";"
                << bolo->numAndares << ";"
                << bolofinal->getListaDecoracoes()
                << endl;  

        arquivo.close();
    }
}

int listarPedidos(){
    ifstream arquivo("../dados/pedidos.txt");
    string linha;

    if (!arquivo.is_open()) {
        cout << "Nenhum pedido cadastrado ainda." << endl;
        return -1;
    }
    int i = 1;
    while (getline(arquivo, linha)) {
    stringstream ss(linha);
    string segmento;
    vector<string> dados;

    
        while (getline(ss, segmento, ';')) {
            dados.push_back(segmento);
        }
        cout << "---------------- PEDIDO " << i << " --------------------------------------------" << endl;
        cout << "Massa:" << dados[0] << endl;
        cout << "Recheio:" << dados[1] << endl;
        cout << "Cobertura:" << dados[2] << endl;
        cout << "Forma:" << dados[3] <<  endl;
        cout << "Peso:" << dados[4] << endl;
        cout << "Andares:" << dados[5] << endl;
        cout << "Decoracao:" << dados[6] << endl;
        cout << "------------------------------------------------------------------------\n" << endl;
        i++;
    }
    arquivo.close();
    return i;
}

bool liberarPedido(int numero){
    ifstream arquivo("../dados/pedidos.txt");
    string linha;
    vector<string> pedidosFicam;
    int i = 1;

    if (!arquivo.is_open()) {
        cout << "Nenhum pedido cadastrado ainda." << endl;
        return false;
    }
    while(getline(arquivo,linha))
    {
        if(  i != numero){
            pedidosFicam.push_back(linha);
        }
        i++;
    }
    arquivo.close();
    ofstream arquivoEscreve("../dados/pedidos.txt", ios::trunc);
    for(const string l : pedidosFicam)
    {
        arquivoEscreve << l << endl;
    }
    arquivoEscreve.close();
    return true;
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
            cout << "2. Ver Pedidos" << endl;
            cout << "3. Liberar Pedidos(excluir)" << endl;
            cout << "4. Deslogar (Sair da conta)" << endl;
            cout << "0. Encerrar Programa" << endl;
            cout << "----------------------------------------" << endl;
            cout << ">> Opcao: ";
            cin >> opcao;

            switch (opcao) {
                case 1:{
                    BoloBuilder* builder = new BoloBuilder();

                    // instancia todos os passos
                    Handler* passo1 = new TelaMassa();
                    Handler* passo2 = new TelaRecheio();
                    Handler* passo3 = new TelaCobertura();
                    Handler* passo4 = new TelaForma();    
                    Handler* passo5 = new TelaPeso();     
                    Handler* passo6 = new TelaAndares();  

                    //   (Massa -> Recheio -> Cobertura -> Forma -> Peso -> Andares)
                    passo1->setNext(passo2)
                        ->setNext(passo3)
                        ->setNext(passo4)
                        ->setNext(passo5)
                        ->setNext(passo6);

                    
                    passo1->handle(builder);

                    
                    IBolo* boloPed = builder->getBolo();

                    //add decoracao
                    int escolhaD = -1;
                    while(escolhaD != 0) {
                        limparTela();
                        cout << "\n--- DECORACOES ---" << endl;
                        cout << "Atual: " << boloPed->getListaDecoracoes() << endl;  
                        cout << "1. Frutas Frescas" << endl;
                        cout << "2. Papel de Arroz" << endl;
                        cout << "3. Embalagem de Presente" << endl;
                        cout << "0. Finalizar e Salvar" << endl;
                        cout << "Opcao: ";
                        cin >> escolhaD;

                        // O Decorator "embrulha" o bolo anterior
                        switch (escolhaD)
                        {
                        case 1:
                            boloPed = new DecoracaoFrutas(boloPed);
                            break;
                        case 2:
                            boloPed = new DecoracaoPapelArroz(boloPed);
                            break;
                        case 3:
                            boloPed = new EmbalagemPresente(boloPed);
                            break;
                        
                        default:
                            break;
                        }
                        
                    }
                    criarPedidos(boloPed);
                    
                    delete builder;
                    delete boloPed; 
                    delete passo1; delete passo2; delete passo3; 
                    delete passo4; delete passo5; delete passo6;
                    
                    pausar();
                    break;
                }
                case 2:{
                    listarPedidos();
                    pausar();
                    break;
                }
                case 3:
                {
                    cout << "Selecione o numero do pedido que deseja liberar(apos ENTER comecara a listagem)" << endl;
                    pausar();
                    int nTotal = listarPedidos();
                    int escolha = -1;
                    while(escolha<=0 || escolha>nTotal)
                    {
                        cout << "Numero do pedido: " << endl;
                        cin >> escolha;
                    }
                    liberarPedido(escolha);
                    cout << "Pedido liberado " << endl;
                    pausar();
                    break;
                }
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