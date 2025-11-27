#include "../includes/Usuario.h"
#include <string> 

using namespace std;

Usuario::Usuario() {
        this->login = "";
        this->senha = "";
        this->nome = "";
}
Usuario::Usuario(string login, string senha, string nome) {
        this->login = login;
        this->senha = senha;
        this->nome = nome;
}

    
string Usuario::getLogin(){ 
    return this->login; 
}
string Usuario::getSenha(){ 
    return this->senha;
}
string Usuario::getNome(){ 
    return this->nome; 
}

