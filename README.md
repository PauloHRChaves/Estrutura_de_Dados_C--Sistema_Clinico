# Trabalho - Estrutura de Dados

Este projeto é um trabalho proposto na disciplina de **Estrutura de Dados**.

## Estrutura do Projeto

Este projeto está organizado da seguinte forma:

- **build/:** Contém o arquivo executável .exe que é gerado após a compilação do código-fonte.

- **include/:** Armazena os arquivos de cabeçalho (.h), que declaram funções e estruturas usadas no projeto.

- **source/:** Contém os arquivos de código-fonte (.c), onde a lógica principal do programa é implementada.

## Como Configurar o Ambiente de Desenvolvimento

Para rodar este projeto no VS Code, você precisa ter as seguintes ferramentas instaladas:

### Extensão C/C++ do VS Code:

Essa extensão é essencial para a compilação e depuração de projetos C e C++ no editor. Para instalar, abra o VS Code, vá para a aba de Extensões (ou pressione Ctrl+Shift+X), procure por "C/C++" e clique em Instalar.

### MinGW (Minimalist GNU for Windows):

É um conjunto de ferramentas de desenvolvimento que inclui o compilador GCC/G++. Você pode baixá-lo e seguir as instruções de instalação no site oficial do VS Code.

## Como Compilar e Executar o Código

Execute o seguinte comando para compilar o código modularizado e gerar o arquivo .exe na pasta build:

```
gcc src/main.c services/chamadas.c services/lista_encadeada.c services/fila_fifo.c services/pilha.c -I include -o build/SyClin_v1  
```
E o comando seguinte para rodar o .exe:
```
./build/SyClin_v1
```
Ou simplesmente compile e rode o arquivo monolito:
```
gcc SyClin.c -o SyClin
```
```
./SyClin
```