
#include "../../includes/BoloBuilder.h"
     BoloBuilder::BoloBuilder(){
        this->reset();
    }
    BoloBuilder::~BoloBuilder(){
        delete this->bolo;
    }
    void BoloBuilder::reset(){
        this->bolo = new Bolo();
    }

    //---------------------NOSSA CONSTRUÇÃO-----------------------------------

    void BoloBuilder::setSaborMassa(string saborMassa){
        this->bolo->saborMassa = saborMassa;
    }   
    void BoloBuilder::setPeso(double kilo){
        this->bolo->quilo = kilo;
    }
    void BoloBuilder::addRecheio(string recheio){
        this->bolo->recheio = recheio;
    }
    void BoloBuilder::addForma(string forma){
        this->bolo->forma = forma;
    }
    void BoloBuilder::addCobertura(string cobertura){
        this->bolo->cobertura = cobertura;
    }
    void BoloBuilder::addDecoracao(string decoracao)
    {
        this->bolo->decoracao.push_back(decoracao);
    }
    void BoloBuilder::addAndares(int numAndares){
        this->bolo->numAndares = numAndares;
    }

    Bolo* BoloBuilder::getBolo(){
        Bolo * boloPronto = this->bolo;
        this->reset();
        return boloPronto;
    }
