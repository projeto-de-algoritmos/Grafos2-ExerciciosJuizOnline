#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 40050
#define MAXSIZE_P 40000

typedef struct {
    int u, v, w;
} edge;

edge g[MAXSIZE];
int p[MAXSIZE_P];

int comparaArestas(const void *a, const void *b) {
    edge *aresta1 = (edge *)a;
    edge *aresta2 = (edge *)b;
    return aresta1->w - aresta2->w;
}

int componente(int i) {
    if (i == p[i]) {
        return i;
    }

    return componente(p[i]);
}

int kruskal(int quantidadeArestas) {
    int i, ans, v, u;

    for (i = 0, ans = 0; i < quantidadeArestas; ++i) {
        v = componente(g[i].v);
        u = componente(g[i].u);

        if (v != u) {
            p[v] = p[u], ans += g[i].w;
        }
    }

    return ans;
}

int main() {
    int quantidadeCidades, quantidadeCaminhos, i;

    while (scanf("%d %d", &quantidadeCidades, &quantidadeCaminhos), quantidadeCidades && quantidadeCaminhos) {
        memset(g, 0, sizeof(g));
        memset(p, 0, sizeof(p));

        for (i = 0; i < quantidadeCaminhos; ++i) {
            scanf("%d %d %d", &g[i].v, &g[i].u, &g[i].w);
        }
        qsort(g, quantidadeCaminhos, sizeof(edge), comparaArestas);

        for (i = 1; i <= quantidadeCidades; ++i) {
            p[i] = i;
        }

        printf("%d\n", kruskal(quantidadeCaminhos));
    }

    return 0;
}

