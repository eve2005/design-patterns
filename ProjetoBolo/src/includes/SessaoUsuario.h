#ifndef SESSAO_USUARIO_H
#define SESSAO_USUARIO_H

#include <iostream>
#include <string>
#include "./Usuario.h"

using namespace std;

class SessaoUsuario {
private:
    static SessaoUsuario* instancia;
    Usuario* usuarioLogado;

    SessaoUsuario();
public:

    static SessaoUsuario* getInstance() ;

    void setUsuario(Usuario* u) ;
    Usuario* getUsuario() ;
    string getNomeUsuario();
    
    bool isLogado();
    
    void logout() ;

    static void deleteSessao();

};

#endif // SESSAO_USUARIO_H