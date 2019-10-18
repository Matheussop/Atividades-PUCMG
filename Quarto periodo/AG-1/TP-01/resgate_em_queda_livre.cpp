#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

float dist_pontos(int x1, int y1, int x2, int y2){
	return (float) sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int indice_menor(vector<float> vec){
	int indice {};
	float menor {__FLT_MAX__};
	for(int i = 0; i < vec.capacity(); i++){
		if((vec[i] != -1) && (vec[i] < menor)){
			menor = vec[i];
			indice = i;
		}
	}
	return indice;
}

float prim(vector<vector<float>> matriz_dist){
	int size = matriz_dist.capacity();
	vector<float> chave(size,__FLT_MAX__);
	float contador {};
	int menor {};

	chave[0] = -1;
	for (int i = 1; i < size; i++){
		for (int j = 0; j < size; j++){
			if((menor != j) && (chave[j])){
				if(matriz_dist[menor][j] < chave[j]){
					chave[j] = matriz_dist[menor][j];
				}
			}
		}
		menor = indice_menor(chave);
		contador += chave[menor];
		chave[menor] = -1;
	}
	return contador;
}

int main() {
	int num_testes {};
	int num_pessoas {};
	float compr_minimo {};

	cin >> num_testes;
	for(int t = 0; t < num_testes; t++){
		cin >> num_pessoas;
		//Criação e incialização da matriz de distancias.
		vector<vector<float>> matriz_dist(num_pessoas, vector<float>(num_pessoas));

		int x[num_pessoas] {-1};
		int y[num_pessoas] {-1};

		for (int p = 0; p < num_pessoas; p++){
			cin >> x[p] >> y[p];
		}

		for(int i = 0; i < num_pessoas; i++){
			for(int j = 0; j < num_pessoas; j++){
				if (i != j){
					matriz_dist[i][j] = dist_pontos(x[i], y[i], x[j], y[j]);
				}
			}
		}

		compr_minimo = prim(matriz_dist);
		cout.precision(2);
		cout << fixed;
		cout << (compr_minimo / 100.0) << "\n\n";

	}

	return 0;
}
