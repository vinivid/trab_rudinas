#include "menor_dist.h"
#include <time.h>
#include <stdio.h>

int main(void) {
	mapa o_mapa = ler_entrada();
	clock_t a, b;
	a = clock();
	res o_caminho = caminho_mais_curto(o_mapa.tam, o_mapa.perm_inicial, o_mapa.lista_mapa);
	b = clock();
	printf("%d %lf\n", o_mapa.tam, (double)(b - a)/CLOCKS_PER_SEC);
	//printar_resposta(o_mapa.tam, o_caminho);
}

