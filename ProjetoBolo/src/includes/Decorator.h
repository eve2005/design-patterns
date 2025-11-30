#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "./BoloBuilder.h"  
// Decorator Base
class Decorator : public IBolo {
protected:
    IBolo* boloEnvolvido;  
public:
    Decorator(IBolo* b) ;
    virtual ~Decorator();
     
    Bolo* getBolo() override;
    string getListaDecoracoes() override ;
};

// --- Decoradores Concretos ---

class DecoracaoFrutas : public Decorator {
public:
    DecoracaoFrutas(IBolo* b);

    string getListaDecoracoes() override;
};

class DecoracaoPapelArroz : public Decorator {
public:
    DecoracaoPapelArroz(IBolo* b);

    string getListaDecoracoes() override;
};

class EmbalagemPresente : public Decorator {
public:
    EmbalagemPresente(IBolo* b) ;

    string getListaDecoracoes() override;
};