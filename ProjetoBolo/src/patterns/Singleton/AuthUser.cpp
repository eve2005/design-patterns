#include <iostream>
#include <string>
#include "../../utils/Usuario.cpp"

using namespace std;

// --- SINGLETON DE SESSÃO  ---
class SessaoUsuario {
private:
    static SessaoUsuario* instancia;
    Usuario* usuarioLogado;

    // Construtor Privado
    SessaoUsuario() {
        usuarioLogado = nullptr;
    }

public:
    // Ponto de acesso global
    static SessaoUsuario* getInstance() {
        if (instancia == nullptr) {
            instancia = new SessaoUsuario();
        }
        return instancia;
    }

    void setUsuario(Usuario* u) 
    { 
        usuarioLogado = u; 
    }
    Usuario* getUsuario() 
    { 
        return usuarioLogado;
    }
    string getNomeUsuario(){
        if(usuarioLogado != nullptr)
            return usuarioLogado->getNome();
        return "Desconhecido";
    }
    
    bool isLogado()
    {
        return usuarioLogado != nullptr;
    }
    
    void logout() { 
        if (usuarioLogado != nullptr) {
            delete usuarioLogado; // Deleta o objeto criado no login
            usuarioLogado = nullptr;
        }
    }

    static void deleteSessao(){
        if (instancia != nullptr) {
            delete instancia;
            instancia = nullptr; 
        }
    }

};

//Inicialização da variável estática OBRIGATÓRIA fora da classe
SessaoUsuario* SessaoUsuario::instancia = nullptr;