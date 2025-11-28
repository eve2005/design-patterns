#include <iostream>
#include <string>
#include <fstream>  // Arquivos
#include <sstream>  // Processar strings
#include <vector>

#include "./Usuario.h"
#include "./SessaoUsuario.h"

using namespace std;

class ControllerUsuario {
private:
    const string dirArqUsuario = "../dados/usuarios.txt";

    
    bool loginJaExiste(string loginParaVerificar) ;
public:
    
    ControllerUsuario();

    // CADASTRAR 
    bool cadastrarUsuario(string login, string senha, string nome);
    
    bool autenticar(string loginDigitado, string senhaDigitada);
    void logout();
};