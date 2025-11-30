
#include "../../includes/Decorator.h"  
// Decorator Base
Decorator::Decorator(IBolo* b) : boloEnvolvido(b) {}

Decorator::~Decorator() {
    delete boloEnvolvido;
}

Bolo* Decorator::getBolo() {
    return boloEnvolvido->getBolo();
}

string Decorator::getListaDecoracoes(){
    return boloEnvolvido->getListaDecoracoes();
}


// --- Decoradores Concretos ---

DecoracaoFrutas::DecoracaoFrutas(IBolo* b) : Decorator(b) {}

string DecoracaoFrutas::getListaDecoracoes(){
    string anterior = boloEnvolvido->getListaDecoracoes();
    if(anterior == "Sem decoracao extra") return "Com Frutas Frescas";
    return anterior + " + Frutas Frescas";
}

    
DecoracaoPapelArroz::DecoracaoPapelArroz(IBolo* b) : Decorator(b) {}

string DecoracaoPapelArroz::getListaDecoracoes() {
    string anterior = boloEnvolvido->getListaDecoracoes();
    if(anterior == "Sem decoracao extra") return "Com Papel de Arroz";
    return anterior + " + Papel de Arroz";
}


EmbalagemPresente::EmbalagemPresente(IBolo* b) : Decorator(b) {}

string EmbalagemPresente::getListaDecoracoes(){
    string anterior = boloEnvolvido->getListaDecoracoes();
    if(anterior == "Sem decoracao extra") return "Para Presente";
    return anterior + " + Para Presente";
}
