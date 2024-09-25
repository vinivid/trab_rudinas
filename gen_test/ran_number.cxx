#include <random>
#include <iostream>
#include <stdlib.h>
#include <vector>

struct prop_cidade {
	int ori;
	int con;
	int dist;
};

int main (int argc, char** argv) {
	//Quantidade de cidades 
	int n;
	//É o limite da poll de distribuição de inteiros que o gerador usa para distancias
	int distancia_max;
	//Se vc colocar em 0 ele sempre vai gerar grafos completamente conexos
	//Eu nao acho q e mt bom colocar numero mt alto
	int por_n_conexao;
	n = std::atoi(argv[1]);
	distancia_max = std::atoi(argv[2]);
	por_n_conexao = std::atoi(argv[3]);

	int qtd_vertices = 0;

	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<int> conj_amx(1, distancia_max);
	std::uniform_int_distribution<int> cem(1, 100);
	
	std::vector<prop_cidade> props;

	for (int i = 1; i <= n; ++i) {
		std::vector<int> cidades;

		for (int k = 1; k <= n; ++k) {
			if (k == i) 
				continue;
			
			cidades.push_back(k);
		}

		int delta_vertice = qtd_vertices;
		for (int j = 0; j < n - 1; ++j) {
			if (por_n_conexao > cem(rng))
				continue;

			int distancia = conj_amx(rng);
			props.push_back(prop_cidade{i , cidades[j], distancia});
			++qtd_vertices;
		}

		if ((qtd_vertices - delta_vertice) == 0) {
			int distancia = conj_amx(rng);

			std::uniform_int_distribution<int> choose(0, cidades.size() - 1);
			props.push_back(prop_cidade{i , cidades[choose(rng)], distancia});
			++qtd_vertices;
		}
	}

	std::cout << n << "\n" << qtd_vertices << "\n";

	for (auto a:props) {
		std::cout << a.ori << " " << a.con << " " << a.dist << "\n";
	}

}
