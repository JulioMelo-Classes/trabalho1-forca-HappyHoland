#include <iostream>
#include "Forca.hpp"
#include <ctime>

using namespace std;



int main(int argc, char *argv[]){
    srand(time(0));

    Forca forca(argv[1], argv[2]);
    auto valid = forca.eh_valido();
    int escolha;
    
    if(!valid.first){ //sai do programa ao encontrar um erro
        cout<<"Erro "<<valid.second<<endl;
        exit(-1);
    } else {
        forca.carregar_arquivos();
    }
    while(true){
        /*imprime o menu principal e a escolha do usuário*/
         escolha = forca.tela_de_inicio();
        
        if(/*iniciar jogo*/ escolha == 1){
            /*Seleciona dificuldade*/
            Forca::Dificuldade d;
            d = forca.select_dif();
            forca.set_dificuldade(d);
            forca.reset_rodada();

            while(true){ //
                string p = forca.proxima_palavra();
                
                /*exibe interface do jogo*/
                forca.interface();

                while (!forca.rodada_terminada()){ //loop da rodada
                    /*ler palpite*/
                    string palpite;
                    string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    size_t pos;

                    cout << "Palpite: ";
                    cin >> palpite;

                    palpite.erase(1);

                    pos = palpite.find_first_not_of(alfabeto);

                    while (pos != string::npos) {
                        cout << "Palpite inválido! Escolha uma letra do alfabeto." << endl;
                        cout << "Palpite: ";
        
                        cin >> palpite;

                        palpite.erase(1);

                        pos = palpite.find_first_not_of(alfabeto);
                    }

                    auto result = forca.palpite(palpite);


                    if (result.second == false) {
                        cout << "Você ja tentou com a letra " << palpite << "." << endl;
                    } else if (result.first == false) {
                        cout << "Não achei a letra " << palpite << "na palavra." << endl;
                    } else {
                        cout << "Muito bem! A palavra contém a letra " << palpite << "!" << endl;
                    }

                    forca.interface();
                }
                if(forca.get_palavra_atual() == forca.get_palavra_jogada()){
                    /*imprime interface de continuar / parar*/
                    bool stop = forca.parar();
                    
                    if (stop)
                        break;
                    else
                        forca.reset_rodada();
                }
                else{ /*perdeu*/
                    /*imprime gameover e a palavra que estava sendo jogada*/
                    forca.game_over();
                    break;
                }
            }
            forca.save_score();
        }
        else if(/*mostrar score*/ escolha == 2)
            forca.print_scores();
        else //qualquer outro número sai do jogo
            break;
    }

    forca.delete_m_scores();

    return 0;
}