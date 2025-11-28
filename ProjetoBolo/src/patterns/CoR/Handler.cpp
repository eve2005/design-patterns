#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../Builder/BoloBuilder.cpp"
#include <fstream>

using namespace std;

//auxiliares
void atualizarQuantidade(const string& caminhoArquivo, const string& saborEscolhido) {
    ifstream arquivoIn(caminhoArquivo);

    if (!arquivoIn.is_open()) {
        return;
    }

    vector<pair<string, int>> linhas;
    string linha;

     
    while (getline(arquivoIn, linha)) {
        size_t pos = linha.find(';');
        if (pos != string::npos) {
            string sabor = linha.substr(0, pos);
            int qtd = stoi(linha.substr(pos+1));
            linhas.push_back({sabor, qtd});
        }
    }
    arquivoIn.close();

   
    for (auto &item : linhas) {
        if (item.first == saborEscolhido) {
            if (item.second > 0) 
                item.second -= 1;
            break;
        }
    }

    
    ofstream arquivoOut(caminhoArquivo, ios::trunc);

    for (auto &item : linhas) {
        arquivoOut << item.first << ";" << item.second << "\n";
    }

    arquivoOut.close();
}
void lerArquivo(string dirArquivo,vector<string>& opcoes){
    ifstream arquivo(dirArquivo); 

        if (arquivo.is_open()) {
            string linha;
            while (getline(arquivo, linha)) {
            
                size_t posDivisor = linha.find(';');
            
                if (posDivisor != string::npos) {
                
                    string sabor = linha.substr(0, posDivisor);//sabor
                    string qtdStr = linha.substr(posDivisor + 1);//qtd

                    int quantidade = stoi(qtdStr);
                    if (quantidade > 0) {
                        opcoes.push_back(sabor);
                    }
                    
                }
            }
            arquivo.close();
        } else {
            cout << "Erro: Nao foi possivel abrir o arquivo de massas." << endl;
            return; 
        }
}



// Interface
class Handler {
public:
    virtual Handler* setNext(Handler* handler) = 0;
    virtual void handle(BoloBuilder* builder) = 0; 
};

// Abstract
class AbstractHandler : public Handler {
private:
    Handler* nextHandler;
public:
    AbstractHandler() : nextHandler(nullptr) {}
    Handler* setNext(Handler* handler) override {
        this->nextHandler = handler;
        return handler;
    }
    void handle(BoloBuilder* builder) override {
        if (this->nextHandler) {
            this->nextHandler->handle(builder);
        }
    }
};



//  ESCOLHA DE MASSA
class TelaMassa : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override {
        cout << "\n--- PASSO 1: ESCOLHA A MASSA ---" << endl;
        
        
        vector<string> opcoes;
        lerArquivo("./massas.txt",opcoes);
        

        if (opcoes.empty()) {
            cout << "Desculpe, nao temos nenhuma massa disponivel hoje!" << endl;
            return; 
        }

        int escolha;
        while(escolha<=0 && escolha> opcoes.size()){
             for (int i = 0; i < opcoes.size(); i++) {
                    cout << i + 1 << " - " << opcoes[i] << endl;
            }
            cout << "Opcao: ";
            cin >> escolha;
        }
       
        
        string massa = opcoes[escolha - 1];
        
        //dimininuir quantidade
        atualizarQuantidade("massas.txt",massa);
        
        builder->setSaborMassa(massa);
        
        //  o próximo passo 
        AbstractHandler::handle(builder);

    }
};

class TelaRecheio : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override {
        cout << "\n--- PASSO 2: ESCOLHA O RECHEIO ---" << endl;
    
        vector<string> opcoes;
        lerArquivo("./recheio.txt",opcoes);
        

        if (opcoes.empty()) {
            cout << "Desculpe, nao temos nenhum recheio disponivel hoje!" << endl;
            return; 
        }

        int escolha;
        while(escolha<0 && escolha> opcoes.size()){
            cout << "0 - Sem Recheio " << endl;
             for (int i = 0; i < opcoes.size(); i++) {
                    cout << i + 1 << " - " << opcoes[i] << endl;
            }
            cout << "Opcao: ";
            cin >> escolha;
        }
        string recheio ;
        if(escolha > 0){
         recheio = opcoes[escolha - 1];
        
        //dimininuir quantidade
        atualizarQuantidade("./recheio.txt",recheio);
        
        }

        if(escolha == 0){
            recheio = "sem recheio";
        }
        builder->setSaborMassa(recheio);
        
        //  o próximo passo 
        AbstractHandler::handle(builder);
    }
};

class TelaCobertura : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override {
        cout << "\n--- PASSO 3: ESCOLHA A COBERTURA ---" << endl;
        vector<string> opcoes;
        lerArquivo("./cobertura.txt",opcoes);
        

        if (opcoes.empty()) {
            cout << "Desculpe, nao temos nenhuma cobertura disponivel hoje!" << endl;
            return; 
        }

        int escolha;
        while(escolha<0 && escolha> opcoes.size()){
            cout << "0 - Sem Cobertura " << endl;
             for (int i = 0; i < opcoes.size(); i++) {
                    cout << i + 1 << " - " << opcoes[i] << endl;
            }
            cout << "Opcao: ";
            cin >> escolha;
        }
        string cobertura ;
        if(escolha > 0){
         cobertura = opcoes[escolha - 1];
        
        //dimininuir quantidade
        atualizarQuantidade("./cobertura.txt",cobertura);
        
        }

        if(escolha == 0){
            cobertura = "sem cobertura";
        }
        builder->setSaborMassa(cobertura);
        
        //  o próximo passo 
        AbstractHandler::handle(builder);
    }

};



class TelaForma : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override {

        int escolha = -1;
        while (escolha<=0 && escolha>3)
        {
            cin >> escolha;
            cout << "\n---  DEFINA O FORMATO DO BOLO ---" << endl;
            cout << "\n1 - Redondo" << endl;
            cout << "\n2 - Quadrado" << endl;
            cout << "\n3 - Coracao " << endl;

        }
 
        string forma;
       
        switch (escolha)
        {
        case 1:
            forma = "Redondo";
            break;
        case 2:
            forma = "Quadrado";
            break;
        case 3:
            forma = "Coracao";
            break;
        default:
            break;
        }

      
        builder->addForma(forma);
        AbstractHandler::handle(builder);  
        
    }
};
class TelaPeso : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override {
        cout << "\n--- PASSO 5: DEFINIR O PESO (KG) ---" << endl;
        
        double peso;
        cout << "Digite o peso desejado (ex: 2.5): ";
        cin >> peso;

        if (peso > 0) {
            builder->setPeso(peso);
            AbstractHandler::handle(builder);  
        } else {
            cout << "Peso invalido!" << endl;
        }
    }
};
class TelaAndares: public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override {
        cout << "\n--- DEFINIR N DE ANDARES ---" << endl;
        
        int andar;
        while(andar<=0 && andar>3){
            cout << "Digite o numero de andares(1-3): ";
            cin >> andar;
        }  
        
        builder->addAndares(andar);
        AbstractHandler::handle(builder);  
        
    }
};
