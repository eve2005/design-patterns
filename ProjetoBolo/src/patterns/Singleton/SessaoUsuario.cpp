
#include <string>
#include "../../includes/SessaoUsuario.h"

using namespace std;

SessaoUsuario::SessaoUsuario() {
        usuarioLogado = nullptr;
    }


    SessaoUsuario* SessaoUsuario::getInstance() {
        if (instancia == nullptr) {
            instancia = new SessaoUsuario();
        }
        return instancia;
    }

    void SessaoUsuario::setUsuario(Usuario* u) 
    { 
        usuarioLogado = u; 
    }
    Usuario* SessaoUsuario::getUsuario() 
    { 
        return usuarioLogado;
    }
    string SessaoUsuario::getNomeUsuario(){
        if(usuarioLogado != nullptr)
            return usuarioLogado->getNome();
        return "Desconhecido";
    }
    
    bool SessaoUsuario::isLogado()
    {
        return usuarioLogado != nullptr;
    }
    
    void SessaoUsuario::logout() { 
        if (usuarioLogado != nullptr) {
            delete usuarioLogado; // Deleta o objeto criado no login
            usuarioLogado = nullptr;
        }
    }

    void SessaoUsuario::deleteSessao(){
        if (instancia != nullptr) {
            delete instancia;
            instancia = nullptr; 
        }
    }



//Inicialização da variável estática OBRIGATÓRIA fora da classe
SessaoUsuario* SessaoUsuario::instancia = nullptr;