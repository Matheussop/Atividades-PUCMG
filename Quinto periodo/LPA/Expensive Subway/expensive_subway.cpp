#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

enum Cor {
    Branco,
    Cinza,
    Preto
};

enum GrafoType {
    Comum,
    Orientado,
    Ponderado,
    Orientado_Ponderado,
};

class Grafo {
    private:
        vector<vector<int>> *matriz_adj;
        int numVertices;
        GrafoType tipo;
    public:
        Grafo(int vertices) : Grafo(vertices, GrafoType::Comum){};
        Grafo(int vertices, GrafoType tipo);
        ~Grafo();
        void display();
        int get_numVertices();
        int get_conexao(int v1, int v2);
        void add_conexao(int v1, int v2, int peso);
        void add_conexao(int v1, int v2);
        void del_conexao(int v1, int v2);
        int grau_vertice(int v);
        int dijkstra(bool caminho_unico);
        int dijkstra();
};

Grafo::Grafo(int vertices, GrafoType t) {
    tipo = t;
    numVertices = vertices;
    matriz_adj = new vector<vector<int>>(numVertices,vector<int>(numVertices, -1));
}

Grafo::~Grafo() {
    delete matriz_adj;
    matriz_adj = nullptr;
}

void Grafo::display() {
    for (auto& linha : *matriz_adj){
        for (auto v : linha){
            cout << v << " ";
        }
        cout << endl;
    }
}

void Grafo::add_conexao(int v1, int v2, int peso) {
    if(v1 < numVertices && v2 < numVertices){
        switch(tipo){
            case Comum:
                if (v1 == v2) matriz_adj->at(v1).at(v1) = 2;
                else {
                    matriz_adj->at(v1).at(v2) = 1;
                    matriz_adj->at(v2).at(v1) = 1;
                }
                break;
            case Ponderado:
                matriz_adj->at(v1).at(v2) = peso;
                matriz_adj->at(v2).at(v1) = peso;
                break;
            case Orientado:
                matriz_adj->at(v1).at(v2) = 1;
                break;
            case Orientado_Ponderado:
                matriz_adj->at(v1).at(v2) = peso;
                break;
        }
    }
}//end Grafo::add_conexao();

void Grafo::add_conexao(int v1, int v2){
    add_conexao(v1,v2,1);
}

void Grafo::del_conexao(int v1, int v2){
    if (v1 < numVertices && v2 < numVertices){
        if(tipo == Orientado || tipo == Orientado_Ponderado){
            matriz_adj->at(v1).at(v2) = -1;
        }
        else {
            matriz_adj->at(v1).at(v2) = -1;
            matriz_adj->at(v2).at(v1) = -1;
        }
    }
}

int Grafo::get_conexao(int v1, int v2){
    return matriz_adj->at(v1).at(v2);
}

int Grafo::get_numVertices(){
    return numVertices;
}

// função que retorna o indice do menor vertice não visitado
int menor_nao_visitado(vector<int> &vec, vector<int> &visitado){
    int indice {};
    int menor {__INT_MAX__};
    for(int i = 0; i < vec.capacity() && i < visitado.capacity(); i++){
        if(visitado.at(i) != 1 && vec.at(i) < menor){
            menor = vec.at(i);
            indice = i;
        }
    }
    return indice;
}

// Algoritmo de dijkstra que retorna o somatorio dos pesos do caminho
// Modificado de forma a não usar o mesmo caminho na proxima chamada
int Grafo::dijkstra(bool caminho_unico){
    vector<int> dist (numVertices, __INT_MAX__);
    vector<int> pai (numVertices, -1);
    vector<int> visitado (numVertices,0);
    dist.at(0) = 0;
    visitado.at(0) = 1;
    int menor {};
    for (int i = 0; i < numVertices; i++){
        for (int j = 0; j < numVertices; j++){
            if(visitado.at(j) != 1 && j != menor && matriz_adj->at(menor).at(j) != -1){
                if(dist.at(j) > dist.at(menor) + matriz_adj->at(menor).at(j)){
                    dist.at(j) = dist.at(menor) + matriz_adj->at(menor).at(j);
                    pai.at(j) = menor;
                }
            }
        }
        visitado.at(menor) = 1;
        menor = menor_nao_visitado(dist, visitado);
    }

    if(caminho_unico) {
        int v = numVertices - 1;
        while(pai.at(v) != -1){
            del_conexao(pai.at(v), v);
            v = pai.at(v);
        }
        if (v != 0) return -1;//Caso a volta não seja possivel
    }
    return dist.at(numVertices - 1);
}

int Grafo::dijkstra() {
    return dijkstra(false);
}


int main(){
    int number_stations {};
    int number_connections {};
    while(number_stations != 0 && number_connections != 0){
        Grafo* g = new Grafo(number_stations, GrafoType::Ponderado);
        vector<string> stations(number_stations, "");
        for(int i = 0; i < number_stations; i++){
            string temp {};
            cin >> temp;
            stations.push_back(temp);
        }
    }

    return 0;
}