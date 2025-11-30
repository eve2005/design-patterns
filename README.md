# 🍰 Cake Store - Sistema de Pedidos de Confeitaria

Este projeto é uma simulação de um sistema de gerenciamento para uma loja de bolos (**Cake Store**), desenvolvido em C++. O foco principal deste projeto não é apenas a lógica de vendas, mas a aplicação de **Design Patterns (Padrões de Projeto)** para resolver problemas comuns de arquitetura de software, garantindo um código limpo, escalável e de fácil manutenção.

Abaixo detalhamos como cada padrão foi implementado seguindo os princípios catalogados pelo *Refactoring Guru*.

---

## 🏛️ Catálogo de Design Patterns Aplicados


### 1. Builder (Padrão Criacional)
> **Propósito:** Separar a construção de um objeto complexo da sua representação. Ele permite criar diferentes configurações de um bolo (diferentes massas, recheios, andares) passo a passo usando o mesmo código de construção.

<p align="center">
  <img src="https://refactoring.guru/images/patterns/diagrams/builder/structure.png" alt="Demonstração do Sistema" width="600">
</p>


*  **O Problema:** Um **`Bolo`** é um objeto complexo. Ele precisa de massa, recheio, cobertura, forma, peso, número de andares e decoração inicial. Criar esse objeto exigiria um construtor monstruoso com 10 parâmetros (`new Bolo("Choc", "Morango", "Redondo", 2.5, ...)`), o que é difícil de ler e manter.
* **A Solução no Projeto:**
    * **Builder (`BoloBuilder`):** Uma classe dedicada apenas a configurar o bolo passo a passo (`setMassa()`, `addRecheio()`).
    * **Director (`Confeiteiro`):** Uma classe que usa o builder para executar "receitas prontas". Ele possui métodos como `fazerBoloFlorestaNegra()` que encapsulam a ordem exata de chamadas do builder para criar receitas prontas.
    * **Product (`Bolo`):** O objeto resultante, podendo ser constuido por diferentes builders.
  

### 2. Chain of Responsibility (Padrão Comportamental)
> **Propósito:** Permitir que você passe pedidos por uma corrente de manipuladores(handlers). Ao receber um pedido, cada handler decide se processa o pedido ou o passa para o próximo handler da corrente.

<p align="center">
  <img src="https://refactoring.guru/images/patterns/diagrams/singleton/structure-pt-br.png" alt="Demonstração do Sistema" width="600">
</p>


*   **O Problema:** O fluxo de montar um pedido personalizado envolve várias telas sequenciais: *Escolher Massa -> Escolher Recheio -> Escolher Cobertura -> Escolher Forma*. Fazer isso com um `if/else` gigante ou `switch` dentro da `main` criaria um código difícil de alterar (ex: se quiséssemos inverter a ordem das telas).
*   **A Solução no Projeto:**
    * Foi implementado interface **`Handler`** e classes concretas para cada tela (**`TelaMassa`**, **`TelaRecheio`**, etc).
    * Na `main`, ligamos a corrente: `passo1->setNext(passo2)->setNext(passo3)...`
    * Quando o usuário termina de escolher a massa, a `TelaMassa` chama automaticamente o `nextHandler->handle()`. Isso desacopla a navegação da lógica de negócio.

### 3. Decorator (Padrão Estrutural)
> **Propósito:** Permitir adicionar novos comportamentos a objetos dinamicamente, "embrulhando" este objeto em classes decoradoras. É uma alternativa flexível à herança para estender funcionalidades.

<p align="center">
  <img src="https://refactoring.guru/images/patterns/diagrams/decorator/structure.png" alt="Demonstração do Sistema" width="600">
</p>


*   **O Problema:** Após o bolo ser construído, o cliente pode pedir adicionais: "Quero com frutas", "Quero papel de arroz", "Quero para presente". Se usássemos herança, teríamos que criar classes como `BoloChocolateComFruta`, `BoloChocolateComPresente`, `BoloChocolateComFrutaEPresente`. Isso causaria uma **explosão de subclasses**.
*   **A Solução no Projeto:**
    * Implemente a interface **`IBolo`**. Tanto o `Bolo` original quanto os Decorators (`DecoracaoFrutas`, `EmbalagemPresente`) implementam essa interface.
    * O Decorator contém um ponteiro para o objeto anterior (`boloEnvolvido`).
    * Quando chamamos `getListaDecoracoes()`, o decorador executa sua parte e chama o objeto de dentro. Isso nos permite criar camadas infinitas (ex: Um bolo embrulhado em presente, que tem frutas, que é de chocolate) sem criar classes novas.

---
### EXTRA. Singleton (Padrão Criacional)
> **Propósito:** Garantir que uma classe tenha apenas uma instância única e fornecer um ponto global de acesso a ela.

<p align="center">
  <img src="https://refactoring.guru/images/patterns/diagrams/singleton/structure-pt-br.png" alt="Demonstração do Sistema" width="600">
</p>

*   **O Problema:** O sistema precisa saber, em todas as telas (Menu Principal, Criação de Pedido, Histórico), quem é o funcionário que está logado. Passar o objeto `Usuario` como parâmetro para dezenas de funções sujaria o código e aumentaria o acoplamento.
*   **A Solução no Projeto:** Foi implementado a classe **`SessaoUsuario`**.
    * O construtor é privado (ninguém pode dar `new SessaoUsuario` de fora).
    * Ela guarda a instância única (`static SessaoUsuario* instancia`).
    * Qualquer parte do código pode chamar `SessaoUsuario::getInstance()->getUsuario()` para saber quem está operando o sistema, sem precisar receber isso por parâmetro.

## 📂 Estrutura de Arquivos

O projeto separa estritamente as declarações (interfaces) das implementações:

```text
ProjetoBolo/
│
├── dados/ /* ARQUIVOS QUE ARMAZENAM DADOS ( ESPECIE DE BANCO DE DADOS )*/
│   ├── cobertura.txt
│   ├── massa.txt
│   ├── pedidos.txt
│   ├── recheio.txt
│   └── usuarios.txt
│
├── src/
│   ├── ascii/
│   │   └── componentes.cpp
│   │
│   ├── controllers/
│   │   └── ControllerUsuario.cpp
│   │
│   ├── includes/ /* CABEÇALHO DOS ARQUIVOS */
│   │   ├── Bolo.h
│   │   ├── BoloBuilder.h
│   │   ├── Confeiteiro.h
│   │   ├── ControllerUsuario.h
│   │   ├── Decorator.h
│   │   ├── Handler.h
│   │   ├── IBolo.h
│   │   ├── IBoloBuilder.h
│   │   ├── SessaoUsuario.h
│   │   └── Usuario.h
│   │
│   └── patterns/ /* IMPLEMENTAÇÃO DOS DESIGN PATTERNS */
│       ├── Builder/
│       │   └── BoloBuilder.cpp
│       │
│       ├── CoR/
│       │   └── Handler.cpp
│       │
│       ├── Decorator/
│       │   └── Decorator.cpp
│       │
│       └── Singleton/
│           └── SessaoUsuario.cpp
│
├── main/
│   ├── main.cpp
│   
│
└── README.md


```

## EXECUÇÃO

Pré-requisitos

    Compilador C++ .

Compilação (Via Terminal)
## Como Executar


```bash
#1. Navegue até a pasta raiz do projeto e execute:
cd ./ProjetoBolo/src

# Compilar todos os arquivos .cpp
g++ main.cpp ./controllers/ControllerUsuario.cpp ./patterns/Builder/BoloBuilder.cpp ./patterns/Decorator/Decorator.cpp ./patterns/CoR/Handler.cpp ./patterns/Singleton/SessaoUsuario.cpp -o cakeStore

# Executar 
./cakeStore

```
A implementação foi desenvolvida por Evellyn Cipriano com ajuda da LLM GEMINI e SITE: https://refactoring.guru/ 
