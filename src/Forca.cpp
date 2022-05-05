#include <iostream>
#include <fstream>
#include <vector>
#include "Forca.hpp"
#include "sort.hpp"
#include <string>
#include <sstream>
#include <time.h>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * Cria a um objeto Forca
 * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com 
 * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
 * ou scores inválidos, use o método eh_valido.
 * @param palavras o arquivo que contém as palavras
 * @param scores o nome do arquivo que contém os scores
 * @see eh_valido
 */
Forca::Forca(string palavras, string scores){
    m_arquivo_palavras = palavras; 
    m_arquivo_scores = scores;
}

 /**
 * Valida os arquivos de entrada de acordo com as especificações.
 * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
 * razão correspondente de acordo com as especificações.
 * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
 */
std::pair<bool, std::string> Forca::eh_valido(){
    
    fstream file_palavras;
    string path_p = "../data/" + m_arquivo_palavras;
    string line;
    int linecont_p = 1;

    cout << "Verificando arquivos.." << endl;

    file_palavras.open(path_p);

    if (!file_palavras.is_open()) {

        return make_pair(false, "Arquivo inexistente: " + m_arquivo_palavras);

    } else {

        while (getline(file_palavras, line)) {
            
            istringstream sstream(line);
            vector<string> words;
            string word;
            string freq = "00";
            size_t wpos, fpos;

            while (getline(sstream, word, ' ')) {
                words.push_back(word);
            }

            for (unsigned int i = 0; i < words.size(); i++) {
                if (i == 0) {
                    word = words[i];
                } else if (i < words.size() - 1) {
                    word = word + " " + words[i];
                } else {
                    freq = words[i];
                }
            }

            wpos = word.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- ");
            fpos = freq.find_first_not_of("0123456789");

            if (wpos != string::npos) {
                
                return make_pair(false, "line " + to_string(linecont_p) + " word " + word);

            } else if (fpos != string::npos || freq[0] == '0' ){
                
                return make_pair(false, "line " + to_string(linecont_p) + " word " + word);

            } else if (word.size() <= 4) {

                return make_pair(false, "line " + to_string(linecont_p) + " word " + word);

            }

            linecont_p++;
        }
    }

    file_palavras.close();

    fstream file_scores;
    string path_s = "../data/" + m_arquivo_scores;
    int linecont_s = 1;

    file_scores.open(path_s);

    if (!file_scores.is_open()) {

        return make_pair(false, "Arquivo inexistente: " + m_arquivo_scores);

    } else {

        while (getline(file_scores, line)) {

            istringstream sstream(line);
            string word;
            vector<string> words;
            size_t ppos;

            while (getline(sstream, word, ';')) {
                
                words.push_back(word);
            }

            words[words.size()-1].erase(words[words.size()-1].begin());
            ppos = words[words.size()-1].find_first_not_of("-0123456789");

            if (words.size() != 4) {

                return make_pair(false, "Line: " + to_string(linecont_s));

            } else if (words[0] == "" || words[1] == "" || words[3] == "" || ppos != string::npos) {

                return make_pair(false, "Line: " + to_string(linecont_s));
            }

            linecont_s++;
        }
    }

    file_scores.close();

    cout << "Arquivos validados!" << endl;

    return make_pair(true, "");
}

/**
 * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
 * Calcula a média de frequências das palavras e atribui para m_media_freq
 */
void Forca::carregar_arquivos(){
    
    fstream file_palavras; //Stream que vai ser associada ao arquivo de palavras
    string path_p = "../data/" + m_arquivo_palavras; // Caminho relativo para o arquivo de palavras *rever*
    string line_p, word; // Armazenar a inha lida e a palavra contida na linha, respectivamente
    int freq, freq_sum = 0, word_cont = 0; // Frequência da palavra lida, soma das frequências lidas, contagem de palavras
    int media; // media de frequências
    
    // Mensagens para o usuário
    cout << ">> Lendo arquivos de palavras [" << m_arquivo_palavras << "] e de scores [" << m_arquivo_scores;
    cout << "], por favor aguarde.."<< endl;
    cout << "------------------------------------------------" << endl;

    // Abrindo o arquivo de palavras
    file_palavras.open(path_p);

    while (getline(file_palavras, line_p)) {
        
        istringstream sstream1(line_p);
        vector<string> words;

        while (getline(sstream1, word, ' ')) {
            words.push_back(word);
        }

        for (unsigned int i = 0; i < words.size(); i++) {
            if (i == 0) {
                word = words[i];
            } else if (i < words.size() - 1) {
                word = word + words[i];
            } else {
                freq = stoi(words[i]);
            }
        }

        for (unsigned int j = 0; j < word.size(); j++) {
            word[j] = toupper(word[j]);
        }

        freq_sum += freq;
        word_cont++;

        m_palavras.push_back(make_pair(word, freq));
    }

    media = freq_sum/word_cont;

    m_media_freq = media;

    file_palavras.close();

    fstream file_scores;
    string path_s = "../data/" + m_arquivo_scores;
    string line_s, palavras;
    unsigned int maior_nome = 7, maior_palavra = 8, maior_num = 6;
    score * aux;

    //Abrindo o arquivo de scores
    file_scores.open(path_s);

    while (getline(file_scores, line_s)) {
        
        aux = new score;
        istringstream sstream2(line_s);
        string score_str;
        vector <string> score;

        while (getline(sstream2, score_str, ';')) {
            score.push_back(score_str);
        }
        
        aux->dificuldade = score[0];

        score[1].erase(score[1].begin());
        aux->nome = score[1];

        if (aux->nome.size() > maior_nome) {
            maior_nome = aux->nome.size();
        }
        
        palavras = score[2];

        if (palavras.size() == 1 && palavras[0] == ' ') {
            palavras.clear();
        }

        istringstream sstream3(palavras);
        string p;

        while (getline(sstream3, p, ',')) {
            p.erase(p.begin());
            aux->palavras.push_back(p);
        }

        for (unsigned int k = 0; k < aux->palavras.size(); k++) {
            if (aux->palavras[k].size() > maior_palavra) {
                maior_palavra = aux->palavras[k].size();
            }
        }

        score[3].erase(score[3].begin());

        if (score[3].size() > maior_num) {
            maior_num = score[3].size();
        }

        aux->pontos = stoi(score[3]);

        m_scores.push_back(aux);
    }

    maiores[0] = maior_nome;
    maiores[1] = maior_palavra;
    maiores[2] = maior_num;

    file_scores.close();

    cout << "Arquivos OK!" << endl;
    cout << "------------------------------------------------" << endl << endl;
}

/**
 * Modifica a dificuldade do jogo.
 * Este método modifica a dificuldade do jogo gerando um novo vetor palavras_do_jogo
 * toda vez que é chamado.
 * @param d a dificuldade desejada
 * @see proxima_palavra
 */
void Forca::set_dificuldade(Forca::Dificuldade d){
    m_dificuldade = d;
    int index, i = 0, j = 0;
    vector<string> aux;

    m_palavras_do_jogo.clear();

    if (d == FACIL) {

        while (i < 10) {
            index = rand()%m_palavras.size();

            if (m_palavras[index].second > m_media_freq) {
                m_palavras_do_jogo.push_back(m_palavras[index].first);
                i++;
            }
        }

    } else if (d == MEDIO) {
        while (i + j < 20) {
            index = rand()%m_palavras.size();
                    
            if (m_palavras[index].second < m_media_freq && j < 7) {
                m_palavras_do_jogo.push_back(m_palavras[index].first);
                j++;
            } else if (m_palavras[index].second >= m_media_freq && i < 13) {
                m_palavras_do_jogo.push_back(m_palavras[index].first);
                i++;
            }
        }

    } else {

        while (i + j < 30) {
            index = rand()%m_palavras.size();

            if (m_palavras[index].second < m_media_freq && j < 22) {
                m_palavras_do_jogo.push_back(m_palavras[index].first);
                j++;
            } else if (m_palavras[index].second >= m_media_freq && i < 8) {
                m_palavras_do_jogo.push_back(m_palavras[index].first);
                i++;
            }
        }
    }

    sort(m_palavras_do_jogo);
}

/**
 * Retorna a próxima palavra de acordo com a dificuldade atual.
 * Este método deve atualizar o valor dos atributos m_palavra_atual, com a palavra atual,
 * do atributo m_palavra_jogada com um texto no formato "_ _ _ _ ... _".
 * O método também deve sortear as letras que devem aparecer dependendo do nível de dificuldade,
 * alterando o valor de m_palavra_jogada de acordo.
 * @return o valor do atributo m_palavra_jogada.
 */
std::string Forca::proxima_palavra(){
    unsigned int n_letras_rev;
    string letras_possiveis;

    m_palavra_jogada.clear();

    if (m_palavras_do_jogo.size() == 0) {
        set_dificuldade(m_dificuldade);
    }

    for (unsigned int i = 0; i < m_palavras_jogadas.size(); i++) {
        if (m_palavras_do_jogo[0] == m_palavras_jogadas[i]) {  
            m_palavras_do_jogo.erase(m_palavras_do_jogo.begin());
        }
    }

    m_palavra_atual = m_palavras_do_jogo[0];
    m_palavras_jogadas.push_back(m_palavra_atual);
    m_palavras_do_jogo.erase(m_palavras_do_jogo.begin());

    for (unsigned int j = 0; j < m_palavra_atual.size(); j++) {
        if (m_palavra_atual[j] != ' ' && m_palavra_atual[j] != '-') {
            m_palavra_jogada.push_back('_');
        } else {
            m_palavra_jogada.push_back(m_palavra_atual[j]);
        }
        
    }

    if (m_dificuldade == FACIL) {

        int max = m_palavra_atual.size()/5;
        n_letras_rev = rand()%max + 1;
        letras_possiveis = "CDFGHJKLMNPQRSTVWXZ";

    } else if (m_dificuldade == MEDIO) {

        n_letras_rev = 1;
        letras_possiveis = "AEIOUY";

    } else if (m_dificuldade == DIFICIL) {

        n_letras_rev = 0;
        letras_possiveis = "";
    }

    for (unsigned int k = 0, l = 0; k < n_letras_rev && letras_possiveis.size() != 0;) {
        l = rand()%letras_possiveis.size();

        bool in = false;

        for (unsigned int m = 0; m < m_palavra_atual.size(); m++) {
            if (letras_possiveis[l] == m_palavra_atual[m]) {
                        
                m_palavra_jogada[m] = letras_possiveis[l];
                in = true;
            }
        }

        if (in) {
            k++;
            m_letras_palpitadas.push_back(letras_possiveis[l]);
            letras_possiveis.erase(letras_possiveis.begin() + l); 
        }
    }

    return m_palavra_jogada;
}

/**
 * Retorna a palavra atual que está sendo jogada.
 * Diferente do método proxima_palavra(), este método __não atualiza__ o atributo
 * m_palavra_atual, apenas retorna o atributo m_palavra_jogada que é a palavra no
 * formato  "_ _ _ _ ... _" contendo todas as letras
 * já acertadas/sorteadas ao invés de “_”.
 * @return a palavra atualmente sendo jogada.
 */
std::string Forca::get_palavra_jogada(){
    return m_palavra_jogada;
}

/**
 * Retorna o valor da palavra atual, útil no caso de um game over, para mostrar a palavra que estava
 * sendo jogada
 * @return o valor do atributo palavra_atual
 **/
std::string Forca::get_palavra_atual() {
    return m_palavra_atual;
}

/**
 * Testa se uma letra pertence á palavra atual e se já foi jogada pelo jogador.
 * Este método testa se uma letra pertence à palavra atual, caso a letra pertença a palavra
 * e ainda não foi jogada o método retorna {T, T}, caso a letra não pertença à palavra o método retorna {F,T}; 
 * Caso a letra já tenha sido jogada o método retorna {T, F}, quando a letra pertence à palavra e {F, F}, quando
 * não pertence.
 * Este método deve atualizar os atributos m_tentativas, m_palavra_jogada e m_letras_palpitadas, para refletir
 * as situações citadas. No caso da letra já ter sido escolhida, o método não deve atualizar m_tentativas.
 * @param palpite uma letra, que deve ser testada se pertence à palavra.
 * @return {T,T} se o palpite pertence à palavra e é um palpite novo, {F,T} caso não pertença e é novo.
 *         {T,F} ou {F,F} no caso do palpite pertencer/não pertencer à palavra, mas não é novo.
 */
std::pair<bool, bool> Forca::palpite(std::string palpite) {
    bool pertence = false;
    bool novo = true;

    for (unsigned int i = 0; i < m_letras_palpitadas.size(); i++) {
        if (m_letras_palpitadas[i] == palpite[0]) {
            novo = false;
        }
    }

    if (novo) {
        m_letras_palpitadas.push_back(palpite[0]);
    }

    for (unsigned int j = 0; j < m_palavra_atual.size(); j++) {
        if (m_palavra_atual[j] == palpite[0]) {
            pertence = true;

            if (novo) {
                m_palavra_jogada[j] = palpite[0];
                m_score_atual->pontos++;

                if (m_palavra_jogada.find_first_of('_') == string::npos) {
                    m_score_atual->pontos = m_score_atual->pontos + 2;
                }
            }
        }
    }

    if (novo && !pertence) {
        m_tentativas_restantes--;
        m_score_atual->pontos--;
    }

    return make_pair(pertence, novo);
}

/**
 * Em caso de Game Over ou do jogador ter acertado a palavra este método deve retornar T.
 * @return T caso o m_tentativas_restantes do jogo esteja igual a 0 ou se o usuário 
 *         acertou toda a palavra, F caso contrário.
 */
bool Forca::rodada_terminada() {
    bool terminou = false;
    size_t pos;

    if (m_tentativas_restantes == 0) {
        terminou = true;
    } else {
        pos = m_palavra_jogada.find_first_of('_');

        if (pos == string::npos) {
            terminou = true;
            m_score_atual->palavras.push_back(m_palavra_atual);
        }
    }

    return terminou;
}

/**
 * Reseta o valor de tentativas restantes para 5 e do atributo m_letras_palpitadas para vazio
 * Este método é útil no caso do jogador escolher continuar o jogo, ou no início
 * de cada rodada, resetando o valor de tentativas restantes para 5 e do atributo
 * m_letras_palpitadas como sendo um vetor vazio
 */
void Forca::reset_rodada(){
    m_letras_palpitadas.clear();
    m_tentativas_restantes = 6;
}

/**
 * Retorna a quantidade de tentativas restantes.
 * @return a quantidade de tentativas restantes.
 */
int Forca::get_tentativas_restantes() {
    return m_tentativas_restantes;
}

// Criadas pelo grupo: 

/**
 * @brief Imprime a tela de início do jogo com as opções para o usuário.
 * Retorna a opção escolhida pelo usuário.
 * @return int  
 */
int Forca::tela_de_inicio () {
    int opcao;
    
    cout << "Bem vindo ao Jogo da Forca!" << endl << endl;
    cout << "Escolha uma das alternativas:" << endl << endl;
    cout << "1 - Iniciar Jogo" << endl;
    cout << "2 - Ver scores anteriores" << endl;
    cout << "3 - Sair do Jogo" << endl;

    cout << "Sua escolha: ";
    
    cin >> opcao;

    cout << endl;

    return opcao;
}

/**
 * @brief Imprime a tela de escolha de dificuldade com as opções para o usuário.
 * Recebe a escolha do usuário e retorna a dificuldade correspondente.
 * @return Dificuldade: FACIL, se o usuário escolher 1, MÉDIO, se o usuário escolher 2, ou DIFÍCIL, se o usuário escolher 3. 
 */
Forca::Dificuldade Forca::select_dif() {
    Forca::Dificuldade d;
    string diff;
    int escolha = 0;
    
    cout << "Por favor, selecione a dificuldade:" << endl;
    cout << "1 - Facil" << endl << "2 - Medio" << endl << "3 - Dificil" << endl;
    cout << "Sua escolha: ";
    cin >> escolha;

    while (escolha < 1 || escolha > 3) {
        cout << "Escolha inválida, por favor escolha 1, 2 ou 3" << endl; 
        cout << "Sua escolha: ";  
        cin >> escolha;
    }

    switch (escolha) {
        case 1:
            d = Forca::Dificuldade::FACIL;
            diff = "Facil";
            break;

        case 2:
            d = Forca::Dificuldade::MEDIO;
            diff = "Medio";
            break;

        case 3:
            d = Forca::Dificuldade::DIFICIL;
            diff = "Dificil";
            break;
    }

    m_score_atual = new score;
    m_score_atual->pontos = 0;
    m_score_atual->dificuldade = diff;
    cout << "Iniciando o jogo no nivel " << diff << ", sera que voce conhece essa palavra?" << endl;

    return d;
}

/**
 * @brief Imprime a interface do jogo
 * Mostra as letras palpitadas, as letras acertadas e as tentativas restantes
 */
void Forca::interface() {
    int erros = 6 - m_tentativas_restantes;

    cout << "____" << endl;
    cout << "|   |" << endl;
    cout << "|  ";
    
    if (erros >= 1) {
        
        cout << " o" << endl;
        cout << "| ";

        if (erros == 2) {
            cout << "  |" << endl << "| " << endl << "|___" << endl;
        } else if ( erros == 3) {
            cout << " /|" << endl << "| " << endl << "|___" << endl;
        } else if (erros >= 4){
            cout << " /|\\" << endl;
            cout << "| ";

            if (erros >= 5) {
                cout << " / ";

                if (erros == 6) {
                    cout << "\\" << endl << "|___" << endl;
                } else {
                    cout << endl << "|___" << endl;
                }
            } else {
                cout << endl << "|___" << endl;
            }

        } else {
            cout << endl << "| " << endl << "| " << endl << "|___" << endl;
        }

    } else {
        cout << endl << "| " << endl << "| " << endl << "|___" << endl;
    }

    cout << m_palavra_jogada << endl;
    cout << "Pontos: " << m_score_atual->pontos << endl; 
}

/**
 * @brief Imprime a interface de continuar/parar e recebe a escolha do usuário
 * @return bool, true se o usuário decidir continuar, false se o usuário decidir parar
 */
bool Forca::parar() {
    int escolha;
    
    cout << "Deseja continuar?" << endl;
    cout << "1 - Parar" << endl;
    cout << "2 - Continuar" << endl;

    cout << "Sua escolha: ";
    cin >> escolha;

    cout << endl;

    switch(escolha) {
        case 1:
            return true;
            break;
        default:
            return false;
            break;
    }

}

/**
 * @brief imprime tela de game over com a palavra atual
 */
void Forca::game_over() {
    cout << "GAME OVER" << endl << endl;

    cout << "Palavra: " << m_palavra_atual << endl << endl;
}

/**
 * @brief Pede o nome do usuário e salva as informações dele no arquivo e no container
 * 
 */
void Forca::save_score() {
    ofstream file_score;
    string path = "../data/" + m_arquivo_scores;
    size_t pos;

    cout << "Informe o seu nome: ";

    getline(cin, m_score_atual->nome, '\n');
    getline(cin, m_score_atual->nome, '\n');

    pos = m_score_atual->nome.find_first_of(';');

    while (pos != string::npos) {
        cout << "Nome inválido. Nomes não podem conter ';'." << endl;
        cout << "Informe o seu nome: ";

        getline(cin, m_score_atual->nome);

        pos = m_score_atual->nome.find_first_of(';');
    }

    m_scores.push_back(m_score_atual);

    file_score.open(path, ios::app);

    if (file_score.is_open()){
        file_score << m_score_atual->dificuldade <<"; " << m_score_atual->nome << "; ";

        if (m_score_atual->palavras.size() == 0) {
            file_score << "; ";
        } else {
            for (unsigned int i = 0; i < m_score_atual->palavras.size(); i++) {
                file_score << m_score_atual->palavras[i];

                if (i < m_score_atual->palavras.size() - 1) {
                    file_score << ", ";
                } else {
                    file_score << "; ";
                }
            }
        }

        file_score << m_score_atual->pontos << endl;
    }

    file_score.close();

    cout << endl << endl;
}

/**
 * @brief Imprime os scores de partidas passadas
 * 
 */
void Forca::print_scores() {
    auto dw = setw(12);
    auto nw = setw(maiores[0] + 1);
    auto pw = setw(maiores[1] + 1);
    auto iw = setw(maiores[2]);

    cout << dw << left << "Dificuldade" << "| ";
    cout << nw << left << "Jogador" << "| ";
    cout << pw << left << "Palavras" << "| ";
    cout << iw << left << "Pontos" << endl;

    for (unsigned int i = 0; i < m_scores.size(); i++) {
        cout << dw << left << m_scores[i]->dificuldade << "| ";
        cout << nw << left << m_scores[i]->nome << "| ";
        if (m_scores[i]->palavras.size() == 0) {
            cout << pw << left << "<nenhuma>" << "| ";
        } else {
            cout << pw << left << m_scores[i]->palavras[0] << "| ";
        }
        cout << iw << left << m_scores[i]->pontos << endl;

        for (unsigned int j = 1; j < m_scores[i]->palavras.size(); j++) {
            cout << dw << left << "" << "| ";
            cout << nw << left << "" << "| ";
            cout << pw << left << m_scores[i]->palavras[j] << "| ";
            cout << iw << left << "" << endl;
        }

        cout << string(14 + maiores[0] + maiores[1] + maiores[2] + 10, '-') << endl;
    }

    cout << endl << endl;

}

 /**
 * @brief desaloca os ponteiros de scores armazenados no vetor m_scores
 * 
 */
void Forca::delete_m_scores() {
    for (unsigned int i = 0; i < m_scores.size(); i++) {
        delete(m_scores[i]);
    }
}