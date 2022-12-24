# SB-JVM

Projeto destinado para confeção dos trabalhos da turma de Software Básico
relacionados à JVM.

Atualmente o software é capaz de ler arquivos `.class` e exibir o seu conteúdo
em formato JSON, de modo que seja possível a visualização dos dados contidos no
arquivo.

## Requisitos

- g++ 11.3.0
- make 4.3

## Como executar

Para executar o software, é necessário primeiro compilar o mesmo. Para isso,
basta executar o comando `make` na raiz do projeto. Após a compilação, basta
executar o comando `./build/sb.exe <arquivo .class>`

Dessa forma, ele irá exibir na saída padrão o conteúdo do arquivo `.class` em
formato JSON.

### Exemplo

```bash
make
./build/sb.exe ./assets/test-class/SimpleClass.class

> {__cls:"Class",magic_number:CAFEBABE ...
```

## Como contribuir

Os arquivos fontes do projeto estão localizados na pasta `src`. Contribuiodores
podem criar arquivos de extensão `.c` e `.h` para implementar novas
funcionalidades. Depois, basta criar um Pull Request para que o código seja
revisado e, caso aprovado, será adicionado ao projeto.

### Como testar

Para adicionar testes ao projeto, basta criar um arquivo de extensão `test.c` na
pasta `test`. Após isso, basta executar o comando `make test` para que os testes
sejam executados.

Este projeto utiliza o Catch2 para testes unitários. Para mais informações sobre
o Catch2, acesse o [repositório oficial](https://github.com/catchorg/Catch2).
Caso seja necessário adicionar arquivos com dados necessários para os testes,
você pode adicioná-los dentro da pasta `assets`.
