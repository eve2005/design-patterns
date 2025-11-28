#pragma once
#include "./IBoloBuilder.h"
#include "./Bolo.h"
#include <vector>

class BoloBuilder : public IBoloBuilder{
    private:
        Bolo* bolo;
    public:

    BoloBuilder();
    ~BoloBuilder();
    void reset();

    void setSaborMassa(string saborMassa);
    void setPeso(double kilo);
    void addRecheio(string recheio);
    void addForma(string forma);
    void addCobertura(string cobertura);
    void addDecoracao(string decoracao);
    void addAndares(int numAndares);
    Bolo* getBolo();
};