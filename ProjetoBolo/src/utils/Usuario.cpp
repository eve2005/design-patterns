#include <iostream>
#include <string>

using namespace std;

class Usuario {
private:
    string login;
    string senha;
    string nome;

public:
    
    // Construtor
    Usuario() {
        this->login = "";
        this->senha = "";
        this->nome = "";
    }
    Usuario(string login, string senha, string nome) {
        this->login = login;
        this->senha = senha;
        this->nome = nome;
    }

    
    string getLogin(){ 
        return this->login; 
    }
    string getSenha(){ 
        return this->senha;
    }
    string getNome(){ 
        return this->nome; 
    }

};
