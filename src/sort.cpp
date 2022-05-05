#include <iostream>
#include <vector>
#include "sort.hpp"

using namespace std;

/**
 * @brief recebe um vetor de strings e o ordena de forma aleatória
 * @param palavras - um vetor de strings
 */
void sort (vector<string>& palavras) {
    int n = palavras.size();
    vector <pair <string, int>> vec_aux;
    pair <string, int> pair_aux;

    for (int i = 0; i < n; i++) {
        vec_aux.push_back(make_pair(palavras[i], rand()));
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vec_aux[i].second > vec_aux[j].second) {
                pair_aux.first = vec_aux[i].first;
                pair_aux.second = vec_aux[i].second;

                vec_aux[i].first = vec_aux[j].first;
                vec_aux[i].second = vec_aux[j].second;

                vec_aux[j].first = pair_aux.first;
                vec_aux[j].second = pair_aux.second;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        palavras[i] = vec_aux[i].first;
    }
}