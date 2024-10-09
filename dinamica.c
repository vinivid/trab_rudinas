#include "menor_dist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool naoTaAi(check, sub);

res dinamica(int tamanho, int *caminho, lsa *lsa) {
    int inicio = caminho[0];
    
    int **memo = malloc(tamanho*sizeof(int*));
    for(int i = 0; i < tamanho; i++) {
        memo[i] = malloc((1 << tamanho)*sizeof(int));
    }

    for(int i = 0; i < tamanho; i++) {
        if(i==inicio) continue;
        memo[i][1 << inicio | 1 << i] = custo_a_b_lsa(lsa, inicio, i);
    }

    for(int rota = 3; rota <= tamanho; rota++) {
        for(int sub; sub < combinacoes(); ){//Não entendi essa parte
            if(naoTaAi(inicio, sub)) continue;
            for(int prox = 0; prox < tamanho; prox++) {
                if(prox == inicio || naoTaAi(prox, sub)) continue;
                int estado = sub ^ (1 << prox);
                int minDist = 100000000;
                for(int i = 0; i < tamanho; i++) {
                    if(i == inicio || naoTaAi(i, sub)) continue;
                    int novaDist = memo[i][estado] + custo_a_b_lsa(lsa, i, prox);
                    if(novaDist < minDist) minDist = novaDist;
                }
                memo[prox][sub] = minDist;
            }
        }
    }
    
    int custoMinimo = achaMelhorCusto(tamanho, inicio, memo, lsa);
    caminho = achaMelhorRota(tamanho, inicio, memo, lsa);

}

bool naoTaAi(check, sub) {
    return ((1 << check) & sub) == 0;
}



int achaMelhorCusto(int tamanho, int inicio, int **memo, lsa *lsa) {
    int estadoFinal = (1 << tamanho) - 1;
    int custoMinimo = 100000000;

    for(int i = 0; i < tamanho; i++) {
        if(i == inicio) continue;

        int custo = memo[i][estadoFinal] + custo_a_b_lsa(lsa, i, inicio);
        if(custo < custoMinimo) {
            custoMinimo = custo;
        }
    }
    return custoMinimo;
}

int* achaMelhorRota(int tamanho, int inicio, int **memo, lsa *lsa) {
    int ultimo = inicio;
    int estado = (1 << tamanho) - 1;
    int *rota = malloc((tamanho+1)*sizeof(int));

    for(int i = tamanho-1; i >= 1; i--) {
        int indice = -1;
        for(int j = 0; j < tamanho; j++) {
            if(j == inicio || naoTaAi(j, estado)) continue;
            if(indice == -1) indice = j;
            int distanciaPrevia = memo[indice][estado] + custo_a_b_lsa(lsa, indice, ultimo);
            int distanciaNova = memo[j][estado] + custo_a_b_lsa(lsa, j, ultimo);
            if(distanciaNova < distanciaPrevia) indice = j;
        }
        rota[i] = indice;
        estado = estado ^ (1 << indice);
        ultimo = indice;
    }

    rota[0] = rota[tamanho] = inicio;
    return rota;
}