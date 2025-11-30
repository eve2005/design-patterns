#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

 
class IBolo {
public:
    virtual string getListaDecoracoes() = 0;  
    virtual class Bolo* getBolo () = 0;      
    virtual ~IBolo() = default;
};