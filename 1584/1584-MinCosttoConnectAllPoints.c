#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//Funcao para garantir que as diferencas nas coordenadas sejam sempre positivas.
int mod(int x) {
    if (x < 0) return -1 * x;
    return x;
}

//Funcao para calcular a distancia de manhattan.
int manhattanDistance(int** points, int x, int y, int* pointsColSize) {
    int* p1 = points[x];
    int* p2 = points[y];
    int distancia = 0;

    for (int i = 0; i < *pointsColSize; i++) {
        distancia = distancia + mod(p1[i] - p2[i]);
    }

    return distancia;
}

//Funcao auxiliar para encontrar o indice do Nó com o menor custo e ainda não incluso na MST.
int custoMinimo(int custo[], bool mstSet[], int pointsSize) {
    int min = INT_MAX, menorIndice;

    //Verifica se o Nó esta dentro da MST e se o custo é menor que o menor custo encontrado ate o momento.
    for (int i = 0; i < pointsSize; i++) {
        if (!mstSet[i] && custo[i] < min) {
            min = custo[i];
            menorIndice = i;
        }
    }

    return menorIndice;
}

//Funcao principal que encontra o custo minimo para conectar todos os pontos no plano cartesiano usando o Algoritmo de Prim.
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize) {
    int distancia = 0;
    //Alocacao de memoria.
    int* parent = (int*)malloc(pointsSize * sizeof(int));
    int* custo = (int*)malloc(pointsSize * sizeof(int));
    bool* mstSet = (bool*)malloc(pointsSize * sizeof(bool));

    //Inicializa todos os custos como "infinito" e marca todos os Nós como nao pertencentes a MST.
    for (int i = 0; i < pointsSize; i++) {
        custo[i] = INT_MAX;
        mstSet[i] = false;
    }

    custo[0] = 0;
    parent[0] = -1;

    //Encontra o Nó com custo minimo que não esta na MST, ele passa por todos os Nós, atualiza seus custos e a origem dos Nós.
    for (int contador = 0; contador < pointsSize - 1; contador++) {
        int u = custoMinimo(custo, mstSet, pointsSize);
        mstSet[u] = true;

        for (int v = 0; v < pointsSize; v++) {
            int dist = manhattanDistance(points, u, v, pointsColSize);

            if (!mstSet[v] && dist < custo[v]) {
                parent[v] = u;
                custo[v] = dist;
            }
        }
    }

    //Com a MST completa, passa por todos os Nós, calcula a distancia total
    //somando as distancias de Manhattan entre o Nó e sua origem na MST.
    for (int i = 1; i < pointsSize; i++) {
        distancia += manhattanDistance(points, parent[i], i, pointsColSize);
    }

    //Desaloca a memoria utilizada.
    free(parent);
    free(custo);
    free(mstSet);

    return distancia;
}