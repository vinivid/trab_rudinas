#include "menor_dist.h"
#include "dinamica.h"

int main(void) {
	mapa o_mapa = ler_entrada();
	res o_caminho = caminho_mais_curto(o_mapa.tam, o_mapa.perm_inicial, o_mapa.lista_mapa);
	printar_resposta(o_mapa.tam, o_caminho);
}

