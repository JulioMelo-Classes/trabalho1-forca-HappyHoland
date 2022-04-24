#include <iostream>   // cout, endl
#include <cassert>    // assert()
#include <random>     // random_device, mt19937
#include <iterator>   // std::begin(), std::end()
#include "test_manager.hpp"
#include "Forca.hpp"

using namespace std;

int main ()
{
    TestManager tm{ "Pessoa e cadastro tests" };
    //== all_of

    std::cout<<"running tests"<<std::endl;

    {
        BEGIN_TEST( tm,"Validação de arquivos", "Testa a validação com arquivos de ");

        auto result = procurar_cpf(base, "204.075.312-54");

        EXPECT_TRUE( (result == nullptr) , "Erro em tests/main.cpp::" + std::to_string(__LINE__));
    }

    {
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
    }


    tm.summary();
    std::cout << std::endl;
    //== Reverse
    return EXIT_SUCCESS;

}
