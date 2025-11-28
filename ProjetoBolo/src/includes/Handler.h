#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "./BoloBuilder.h"
#include <fstream>

using namespace std;



// Interface
class Handler {
public:
    virtual Handler* setNext(Handler* handler) = 0;
    virtual void handle(BoloBuilder* builder) = 0; 
};

// Abstract
class AbstractHandler : public Handler {
private:
    Handler* nextHandler;
public:
    AbstractHandler() : nextHandler(nullptr) {}
    Handler* setNext(Handler* handler) override ;
    void handle(BoloBuilder* builder) override ;
};



//  ESCOLHA DE MASSA
class TelaMassa : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override ;
};

class TelaRecheio : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override;
};

class TelaCobertura : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override;

};



class TelaForma : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override ;
};
class TelaPeso : public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override ;
};
class TelaAndares: public AbstractHandler {
public:
    void handle(BoloBuilder* builder) override ;
};
