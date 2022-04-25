#include <iostream>   // cout, endl
#include <cassert>    // assert()
#include <random>     // random_device, mt19937
#include <iterator>   // std::begin(), std::end()
#include "test_manager.hpp"
#include "Forca.hpp"

using namespace std;

int main ()
{
    TestManager tm{ "Forca tests" };
    //== all_of

    std::cout<<"running tests"<<std::endl;

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Palavras não existente", "Testa a validação com arquivo de palavras não existente");

        Forca forca("words.txt", "scores.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "Arquivo inexistente: words.txt") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Palavras com caracteres especiais", "Testa a validação no caso do arquivo de palavas conter uma palavra com caractere especial");

        Forca forca("tests/words_test1.txt", "scores.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "line 10 word cabeça") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Palavras com palavra sem frequência", "Testa a validação no caso do arquivo de palavas conter uma palavra sem frequência");

        Forca forca("tests/words_test2.txt", "scores.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "line 12 word amarelo") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Palavras com palavra de frequência negativa", "Testa a validação no caso do arquivo de palavas conter uma palavra de frequência negativa");

        Forca forca("tests/words_test3.txt", "scores.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "line 7 word mesmo") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Palavras menor ou igual a 4", "Testa a validação no caso do arquivo de palavas conter uma palavra de tamanho 4 ou menor");

        Forca forca("tests/words_test4.txt", "scores.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "line 3 word fora") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Scores não existente", "Testa a validação com arquivo de scores não existente");

        Forca forca("palavras.txt", "score_list.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "Arquivo inexistente: score_list.txt") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Scores com uma linha com mais de 3 ';'", "Testa a validação no caso de uma linha do scores ter mais de 3 ';'");

        Forca forca("palavras.txt", "tests/score_test1.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "Line: 3") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Scores com uma linha com menos de 3 ';'", "Testa a validação no caso de uma linha do scores ter menos de 3 ';'");

        Forca forca("palavras.txt", "tests/score_test2.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "Line: 4") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Scores com uma linha sem dificuldade", "Testa a validação no caso de uma linha do scores ter dificuldade vazia");

        Forca forca("palavras.txt", "tests/score_test3.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "Line: 2") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Scores com uma linha sem nome", "Testa a validação no caso de uma linha do scores ter nome vazio");

        Forca forca("palavras.txt", "tests/score_test4.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "Line: 6") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Validação de arquivos - Arquivo de Scores com uma linha sem pontos", "Testa a validação no caso de uma linha do scores ter pontuação vazia");

        Forca forca("palavras.txt", "tests/score_test5.txt");
        
        auto result = forca.eh_valido();

        EXPECT_TRUE( (result.first == false && result.second == "Line: 5") , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    /*{
        BEGIN_TEST( tm,"Teste de inseção", "Testa se a inserção funciona;");

        auto p = criar_pessoa("Joana Ayla Rocha",
                              "204.075.312-54",
                              "Quadra J1, 677, Primavera");
        
        EXPECT_TRUE( (p != nullptr) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
        bool result = inserir_pessoa(base, p);
        EXPECT_TRUE( result , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
        result = inserir_pessoa(base, p);
        EXPECT_FALSE( result , "Erro em tests/main.cpp::" + std::to_string(__LINE__));

        p = criar_pessoa("Joana Ayla Rocha",
                         "204.213.314-12",
                         "Quadra J1, 677, Primavera II");
        result = inserir_pessoa(base, p);
        EXPECT_TRUE( result , "Erro em tests/main.cpp::" + std::to_string(__LINE__));

        p = criar_pessoa("Joana Ayla Rocha",
                         "212.21.122-12",
                         "Quadra J1, 677, Primavera III");
        result = inserir_pessoa(base, p);
        EXPECT_TRUE( result , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Teste de buca", "Testa se a busca funciona;");
        auto result = procurar_cpf(base, "212.21.122-12");
        
        EXPECT_TRUE( (result != nullptr) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));

        result = procurar_cpf(base, "204.763.446-12");
        EXPECT_TRUE( (result == nullptr) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));

        auto pessoas = procurar_nome(base, "Joana Ayla Rocha");

        EXPECT_TRUE( (pessoas.size() == 3) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Teste de remoção", "Testa se a remoção funciona;");
        auto result = remover_pessoa(base, "212.21.122-12");

        EXPECT_TRUE( (result != nullptr) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
        delete result;

        result = remover_pessoa(base, "212.21.122-12");
        EXPECT_TRUE( (result == nullptr) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));

        auto pessoas = procurar_nome(base, "Joana Ayla Rocha");

        EXPECT_TRUE( (pessoas.size() == 2) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
        BEGIN_TEST( tm,"Teste de insere/remove/insere", "Testa se as operações funcionam em sequencia;");

        auto p = criar_pessoa("Eliane Sophie Cavalcanti",
                              "234.471.164-39",
                              "Rua Barra de São Francisco, 552, Terra Vermelha");

        auto result = inserir_pessoa(base, p);

        EXPECT_TRUE( result , "Erro em tests/main.cpp::" + std::to_string(__LINE__));

        p = criar_pessoa("Ryan Levi Davi Duarte",
                         "175.659.343-48",
                         "Rua São Gonçalo, 831, Santa Terezinha");

        result = inserir_pessoa(base, p);

        EXPECT_TRUE( result , "Erro em tests/main.cpp::" + std::to_string(__LINE__));

        Pessoa* removed = remover_pessoa(base, "234.471.164-39");
        EXPECT_TRUE( (removed != nullptr) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
        delete removed;

        p = criar_pessoa("Eliane Sophie Cavalcanti",
                              "234.471.164-39",
                              "Rua Barra de São Francisco, 552, Terra Vermelha");

        result = inserir_pessoa(base, p);

        EXPECT_TRUE( result , "Erro em tests/main.cpp::" + std::to_string(__LINE__));

        removed = remover_pessoa(base, "234.471.164-39");
        EXPECT_TRUE( (removed != nullptr) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
        delete removed;
    }*/


    tm.summary();
    std::cout << std::endl;
    //== Reverse
    return EXIT_SUCCESS;

}
