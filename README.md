# SB-JVM

Projeto destinado para confeção dos trabalhos da turma de Software Básico
relacionados à JVM.

Atualmente o software é capaz de ler arquivos `.class` e exibir o seu conteúdo
em formato JSON, de modo que seja possível a visualização dos dados contidos no
arquivo. Além disso, o software é capaz de executar os mesmos arquivos `.class`
e exibir o resultado da execução dependendo do bytecod nele contido
(funcionalidade ainda em desenvolvimento).

## Requisitos

- g++ 11.3.0
- make 4.3
- cppcheck 2.7 ou maior
- valgrind 3.19.0 ou maior
- yajl-tools

Em sistemas Linux (Ubuntu) os seguintes comandos podem ser utilizados para
instalar os requisitos (caso não estejam instalados):

```sh
sudo apt install cppcheck
sudo apt install valgrind
sudo apt install yajl-tools
```

## Como executar

Para executar quais quer dos casos de uso é necessário primeiro compilar o
projeto com o comando `make` na raiz do projeto.

### Caso de uso 1: Ler arquivo .class

Para ler o conteúdo de um arquivo `.class`, basta executar o comando `make read
file=<caminho/do/arquivo.class>` na raiz do projeto. Dessa forma, o software
irá exibir na saída padrão o conteúdo do arquivo `.class` em formato JSON.

```bash
make read file=assets/test-JVM/Soma.class
>  "major_version": "52 [1.8]",
    "constant_pool_count": 15,
    ...
  }
```

### Caso de uso 2: Executar arquivo .class

Para executar um arquivo `.class`, basta executar o comando `make exec
file=<caminho/do/arquivo.class>` na raiz do projeto. Dessa forma, o software
irá exibir na saída padrão o resultado da execução do arquivo `.class`.

```bash
make exec file=assets/test-JVM/Soma.class
```

## Como contribuir

Os arquivos fontes do projeto estão localizados na pasta `src`. Contribuidores
podem criar arquivos de extensão `.c` e `.h` para implementar novas
funcionalidades. Depois, basta criar um Pull Request para que o código seja
revisado e, caso aprovado, será adicionado ao projeto.

### Como testar

Para adicionar testes ao projeto, basta criar um arquivo de extensão `test.c`
na pasta `test`. Após isso, basta executar o comando `make test` para que os
testes sejam executados.

Este projeto utiliza o Catch2 para testes unitários. Para mais informações
sobre o Catch2, acesse o [repositório
oficial](https://github.com/catchorg/Catch2). Caso seja necessário adicionar
arquivos com dados necessários para os testes, você pode adicioná-los dentro da
pasta `assets`.

### Análise Estática e Dinâmica

#### Utilização

Para realizar uma análise estática basta executar:

```sh
make lint
```

Para executar uma análise dinâmica de todos os casos de uso com o valgrind
basta executar:

```sh
make valgrind command="read" file="path para .class"
```

## Participantes

- Eduardo Xavier
- Gabriel Guerra
- Lucas Azuma
- Luigi Minardi
- Thiago Tokarski

> Todos os participantes do projeto se envolveram de alguma forma em todas as
> funcionalidades do projeto.

## Instruções implementadas

<!-- Markdown table -->
| Instrução | Implementado no Leitor | Implementado na JVM |
|-----------|------------------------|---------------------|
| sipush    | :heavy_check_mark:     | :heavy_check_mark:  |
| bipush    | :heavy_check_mark:     | :heavy_check_mark:  |
| istore_1  | :heavy_check_mark:     | :heavy_check_mark:  |
| istore_2  | :heavy_check_mark:     | :heavy_check_mark:  |
| iload_1   | :heavy_check_mark:     | :heavy_check_mark:  |
| iload_2   | :heavy_check_mark:     | :heavy_check_mark:  |
| iadd      | :heavy_check_mark:     | :heavy_check_mark:  |
| return    | :heavy_check_mark:     | :heavy_check_mark:  |
| if_icmpeq | :heavy_check_mark:     | :heavy_check_mark:  |
| wide      | :x:                    | :x:                 |
| (outros)  | :heavy_check_mark:     | :x:                 |
