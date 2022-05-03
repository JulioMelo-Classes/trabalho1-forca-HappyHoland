# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Compilação do Projeto:
No terminal, execute os comandos:
```
mkdir build
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
mkdir build
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
3. O processo de embaralhamento do container m_palavras_do_jogo é o mesmo toda vez que o programa é executado.
4. Interface limitada, através do terminal
