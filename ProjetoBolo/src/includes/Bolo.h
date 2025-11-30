#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "./IBolo.h"

class Bolo : public IBolo{
    public:

        string saborMassa;
        string forma;
        string recheio;
        string cobertura;
        vector <string> decoracao;
        int numAndares;
        double quilo;
    
        void descreverBolo(){
            std::cout << "+------------------| DESCRICAO DO BOLO |-------------------+" << endl;
            
            std::cout << "\t sabor da massa: " << this->saborMassa << endl;
            std::cout << "\t formato do bolo: " << this->forma << endl;
            std::cout << "\t recheio: " << this->recheio << endl;
            std::cout << "\t cobertura: " << this->cobertura << endl;
            std::cout << "\t anderes: " << this->numAndares << endl;
            std::cout << "\t peso: " << this->quilo << endl;
            cout << "Decoracoes: ";
            for (const string& d : this->decoracao) {
                cout << "[" << d << "] ";
            }
            std::cout << "+---------------------------------------------------------------+" << endl;
        }

        string getListaDecoracoes() override {
            return "Sem decoracao extra";
        }

        Bolo* getBolo () override {
            return this;
        }

};