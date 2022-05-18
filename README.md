# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Avaliação e Feedback

## Geral

- Implementção da Classe forca ou similar | 10 / 10 pontos
	- ok

- Implementação da Interface textual | 10 / 10 pontos
	- ok

- Execução completa do jogo | 15 / 15 pontos
	- Sorteio correto de paralavras para o jogo: cp1
	- Configuração correta da palavra jogada, dependendo da dificuldade: 5 / 5 
	- Execução correta do jogo (não pode repetir palpites, contabilização correta dos pontos e loop): 3 / 3
	- Salvamento correto do score: 2 / 2
	- Exibição correta dos scores: 5 / 5

- Validação dos arquivos de texto | 5 / 5 pontos
	- ok

- Arquivos de teste de validação dos casos de erro | 5 / 5 pontos
	- realmente foi uma boa sacada usar a estrutura das listas!

## Código

- Documentação do código e readme | 10 / 10 pontos
	- ok

- Organização e indentação do código | 10 / 10 pontos
	- ok

- Compilação automatizada | 5 / 5 pontos
	- ok
	
## Comentários
- Um erro de especificação que vocÊ cometeu foi o de não carregar os arquivos recebidos pelo terminal mas sim arquivos que estão na pasta 'data'. Veja que essa é uma limitação que não deveria haver pela especificação, uma vez que o usuário pode passar o diretório absoluto onde o arquivo está pela linha de comando da execução do programa.
- Acho que o main ficou muito bem organizado, talvez faltasse só organizar o Forca.cpp para usar algum outro .hpp relacionado com a interface

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
