#include <random>
#include <iostream>
#include <stdlib.h>
#include <vector>

int main (int argc, char** argv) {
	int n;
	int distancia_max;
	n = std::atoi(argv[1]);
	distancia_max = std::atoi(argv[2]);

	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<int> conj_amx(1, distancia_max);
	
	for (int i = 1; i <= n; ++i) {
		std::vector<int> cidades;

		for (int k = 1; k <= n; ++k) {
			if (k == i) 
				continue;
			
			cidades.push_back(k);
		}


		for (int j = 0; j < n - 1; ++j) {
			int distancia = conj_amx(rng);
			std::cout << i << " " << cidades[j] << " " << distancia << "\n";
		}
	}
}
