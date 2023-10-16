#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 600
#define INF 0x3f3f3f3f // representa infinito 

int matrizAdjacencia[MAXSIZE][MAXSIZE];

void dijkstra(int n, int src, int destino) {
    int i, j;
    int visitado[n + 1];
    int distancia[n + 1];

    memset(visitado, false, sizeof(visitado));

    for (i = 0; i <= n; ++i) {
        distancia[i] = INF;
    }

    distancia[src] = 0;
    for (i = 0; i <= n; ++i) {
        int v = -1;
        for (j = 0; j <= n; ++j) {
            if (!visitado[j] && (v == -1 || distancia[j] < distancia[v])) {
                v = j;
            }
        }

        if (distancia[v] == INF) {
            break;
        }

        visitado[v] = true;

        for (j = 0; j <= n; ++j) {
            if (distancia[v] + matrizAdjacencia[v][j] < distancia[j]) {
                distancia[j] = matrizAdjacencia[v][j] + distancia[v];
            }
        }
    }

    if (distancia[destino] < INF) {
        printf("%d\n", distancia[destino]);
    } else {
        puts("Nao e possivel entregar a carta");
    }
}

int main() {
    int u, v, w;
    int numeroCidades, acordos, i, j, t;

    while (scanf("%d %d", &numeroCidades, &acordos), numeroCidades || acordos) {
        for (i = 0; i <= numeroCidades; ++i) {
            for (j = 0; j <= numeroCidades; ++j) {
                matrizAdjacencia[i][j] = INF;
            }
        }

        for (i = 0; i < acordos; ++i) {
            scanf("%d %d %d", &u, &v, &w);

            if (matrizAdjacencia[v][u] != INF) {
                matrizAdjacencia[u][v] = matrizAdjacencia[v][u] = 0;
            } else {
                matrizAdjacencia[u][v] = w;
            }
        }

        scanf("%d", &t);
        
        while (t--) {
            scanf("%d %d", &u, &v);
            dijkstra(numeroCidades, u, v);
        }

        printf("\n");
    }

    return 0;
}


