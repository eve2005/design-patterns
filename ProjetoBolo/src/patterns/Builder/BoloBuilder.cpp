#pragma once
#include "../../includes/IBoloBuilder.h"
#include "../../includes/Bolo.h"
#include <vector>

class BoloBuilder : public IBoloBuilder{
    private:
        Bolo* bolo;
    public:

    BoloBuilder(){
        this->reset();
    }
    ~BoloBuilder(){
        delete this->bolo;
    }
    void reset(){
        this->bolo = new Bolo();
    }

    //---------------------NOSSA CONSTRUÇÃO-----------------------------------

    void setSaborMassa(string saborMassa){
        this->bolo->saborMassa = saborMassa;
    }   
    void setPeso(double kilo){
        this->bolo->quilo = kilo;
    }
    void addRecheio(string recheio){
        this->bolo->recheio = recheio;
    }
    void addForma(string forma){
        this->bolo->forma = forma;
    }
    void addCobertura(string cobertura){
        this->bolo->cobertura = cobertura;
    }
    void addDecoracao(string decoracao)
    {
        this->bolo->decoracao.push_back(decoracao);
    }
    void addAndares(int numAndares){
        this->bolo->numAndares = numAndares;
    }

    Bolo* getBolo(){
        Bolo * boloPronto = this->bolo;
        this->reset();
        return boloPronto;
    }
};