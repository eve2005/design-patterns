#include "../includes/ControllerUsuario.h"

using namespace std;


    
    bool ControllerUsuario::loginJaExiste(string loginParaVerificar) {
        ifstream arquivo(dirArqUsuario);
        string linha;

        if (!arquivo.is_open()) return false; 

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string loginNoArquivo;
            
            getline(ss, loginNoArquivo, ';');

            if (loginNoArquivo == loginParaVerificar) {
                return true; 
            }
        }
        return false;
    }

public:
    
    ControllerUsuario::ControllerUsuario() 

    // CADASTRAR 
    bool ControllerUsuario::cadastrarUsuario(string login, string senha, string nome) {
        
        // Verifica se login já existe
        if (loginJaExiste(login)) {
            cout << "Erro: O login '" << login << "' ja esta em uso." << endl;
            return false;
        }

       
        ofstream arquivo(dirArqUsuario, ios::app);
        
        if (arquivo.is_open()) {
            arquivo << login << ";" << senha << ";" << nome << endl;
            arquivo.close();
            return true;
        } 
        return false;
    }

    
    bool ControllerUsuario::autenticar(string loginDigitado, string senhaDigitada) {
        ifstream arquivo(dirArqUsuario);
        string linha;

        if (!arquivo.is_open()) {
            cout << "Nenhum usuario cadastrado ainda." << endl;
            return false;
        }

       
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string segmento;
            vector<string> dados;

            // Transforma em vetor  ["login", "senha", "nome"]
            while (getline(ss, segmento, ';')) {
                dados.push_back(segmento);
            }

            
            if (dados.size() >= 3) {//valida p/ dados com as 3 info completas
                string loginArq = dados[0];
                string senhaArq = dados[1];
                string nomeArq  = dados[2];

                
                if (loginArq == loginDigitado && senhaArq == senhaDigitada) {
                    
                    Usuario* usuarioAutenticado = new Usuario(loginArq, senhaArq, nomeArq);
                    
                    // Salva na sessão
                    SessaoUsuario::getInstance()->setUsuario(usuarioAutenticado);
                    
                    return true;
                }
            }
        }

        return false; 
    }

    void ControllerUsuario::logout(){
        SessaoUsuario::getInstance()->logout();
    }
