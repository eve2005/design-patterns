#pragma once

#include <iostream>
#include <string>


using namespace std;

class Usuario {
private:
    string login;
    string senha;
    string nome;

public:
    
   
    Usuario();
    Usuario(string login, string senha, string nome);
    
    string getLogin();
    string getSenha();
    string getNome();

};
