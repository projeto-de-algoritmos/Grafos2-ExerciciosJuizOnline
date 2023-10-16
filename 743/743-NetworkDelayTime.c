#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//Funcao para retornar o valor maximo entre dois numeros.
int max(int a,int b){
    return a>b?a:b;
}

//Funcao principal que calcula o tempo minimo para que um sinal alcance todos os Nós na rede.
int networkDelayTime(int** times, int arestas, int* numColunas, int n, int noInicial){

    //Matriz para representar os tempos de viagem entre todos os pares de Nós.
    //Eh definido todos os tempos como "infinito" exeto para o Nó de partida.
    int map[n+1][n+1];
    for(int i=1; i < n+1; i++){
        for(int j=1;j<n+1;j++){

            if(i == j){
                map[i][j] = 0;
            }else{
                map[i][j] = INT_MAX;
            }
        }
    }

    //Preenche a matriz 'map' com os tempos de viagem reais a partir da matriz principal.
    for(int i=0; i < arestas; i++){
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        map[u][v] = w;
    }

    //Array para as distancias minimas do Nó de partida para todos os outros Nós. 
    int dis[n+1];
    for(int i=1; i < n+1; i++){
        dis[i] = map[noInicial][i];
    }

    //Array alocado dinamicamente e inicializado com zeros para rastrear quais Nós ja foram visitados.
    //O Nó de partida é marcado como visitado = 1.
    int *visited = (int*)calloc(n+1,sizeof(int));
    visited[noInicial] = 1;

    //Seleciona o Nó mais proximo que ainda nao foi visitado. 
    for(int i=1; i < n+1; i++){
        int menorDistancia = INT_MAX;
        int u = -1;

        //Verifica se o Nó ja foi visitado e se a distancia é menor do que o a encontrada até agora.
        for(int j=1; j < n+1; j++){
            if(visited[j] == 0 && dis[j]<menorDistancia){
                menorDistancia = dis[j];
                u = j;
            }
        }

        //Verifica se nao ha mais Nós não visitados.
        if(u == -1) continue;

        //Faz a marcacao do Nó como visitado.
        visited[u]=1;

        //Verifica se a rota de um Nó para outro é mais rapida que a atual.
        //Se sim, a distancia minima eh atualizada.
        for(int v=1; v < n+1; v++){
            if(map[u][v] < INT_MAX){
                if(dis[v] > map[u][v] + dis[u]){
                    dis[v] = map[u][v] + dis[u];
                }
            }
        }
    }

    //Inicializando variavel com o menor numero possivel.
    int res = INT_MIN;

    //Atualiza para o tempo mínimo necessário para um sinal alcançar o Nó mais distante
    for(int i=1; i < n+1; i++){
        res = max(res,dis[i]);
    }

    //Verifica se alguns Nós não são alcançáveis a partir do Nó de partida, e a função retorna -1.
    //Caso contrario retorna tempo mínimo para o sinal alcançar todos os Nós na rede.
    return res == INT_MAX?-1:res;
}