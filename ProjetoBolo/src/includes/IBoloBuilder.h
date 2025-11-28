#include <iostream>
#include <string>
#include <vector>
using namespace std;

class IBoloBuilder{
    public:
        virtual ~IBoloBuilder() = default;

        //basicos
        virtual void reset() = 0;
        virtual void setSaborMassa(string saborMassa) = 0;
        virtual void setPeso(double kilo) = 0; 
        //opcionais
        virtual void addRecheio(string recheio) = 0;
        virtual void addForma(string forma) = 0;
        virtual void addCobertura(string cobertura) = 0;
        virtual void addDecoracao(string decoracao) = 0;
        virtual void addAndares(int numAndares) = 0;

   

};