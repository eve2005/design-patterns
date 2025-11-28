#pragma once
#include "./IBoloBuilder.h"
#include <string>

class Confeiteiro {
private:
    IBoloBuilder* builder;

public:
    void setBuilder(IBoloBuilder* b) {
        this->builder = b;
    }

    // --- Cardapio Fixo (pre-montado)---
    void fazerBoloFlorestaNegra(string forma, double kg) {
        builder->reset();
        builder->setSaborMassa("Chocolate");
        builder->setPeso(kg);
        builder->addRecheio("Creme com Cerejas");
        builder->addForma(forma);
        builder->addCobertura("Raspas de Chocolate");
        builder->addDecoracao("Cerejas Inteiras");
        builder->addAndares(1);
    }


    void fazerBoloAniversario( string nomeAniversariante,  string saborMassa, double kg) {
        builder->reset();
        builder->setSaborMassa(saborMassa);
        builder->setPeso(kg);
        builder->addRecheio("Creme com Cerejas");
        builder->addForma("Redondo");
        builder->addCobertura("Raspas de Chocolate");
        builder->addDecoracao("Confetes");
        builder->addDecoracao("Vela");
        builder->addDecoracao("Placa feliz aniversario com nome:" + nomeAniversariante);
        builder->addAndares(1);
    }

        void fazerBoloCenoura( double kg) {
        builder->reset();
        builder->setSaborMassa("Cenoura");
        builder->setPeso(kg);
        builder->addRecheio("Sem recheio");
        builder->addForma("Quadrado");
        builder->addCobertura("Chocolate");
        builder->addDecoracao("Sem Decoracao");
        builder->addAndares(1);
    }
};