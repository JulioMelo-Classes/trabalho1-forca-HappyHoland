# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Avaliação e Feeback

- Implementação do carregamento dos arquivos | 9 / 10 pontos
    - blz, boa ideia usar o getline para fazer o split da palavra. O unico ponto aqui é que vc fixou a localização dos arquivos de entrada

- Implementação de parte da validação | 9 / 10 pontos
    - Aqui você fixou o path dos arquivos para '../data', a epecificação diz que vc deve abrir os arquivos recebidos por parâmetro!

- Implementação de um main funcional com parte da UI | 5 / 5 pontos

- Implementação de parte da lógica de sorteio de palavras | 8 / 10 pontos 
    - Entendi a ideia de implementar um "embaralhamento" mas realmente não é uma forma ok de fazer, você poderia ao menos gerar aqueles vetores
    automaticamente com rand ou usar shuffle!

- Estrutura básica dos arquivos e processo de compilação definido | 5 / 5 pontos

- Observações gerais
    - Muito boa a ideia de testar com o test_manager, mas como vc faria para testar uma execução inteira do programa? ;D fica de desafio


# Compilação do Projeto:
No terminal, execute os comandos:
```
cd build
cmake ..
cmake --build .
```
# Execução do Programa
Execute 'forca.exe' com os argumentos 'palavras.txt' e 'scores.txt':

```
./forca palavras.txt scores.txt
```

# Testes de validação de arquivos:
No terminal, execute os comando:

(se não tiver criado os arquivos de build na pasta build ainda):
```
cd build
cmake ..
cmake --build . --target run_tests
```
(se já tiver criado os arquivos de build):
```
cmake --build . --target run_tests
```

# Limitações:
1. Este programa considera que arquivos ilegíveis contam como não existentes. 
1. Este programa não permite carregar arquivos não validados
3. 