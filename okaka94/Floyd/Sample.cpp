#include <iostream>

#define V 4
#define INF 99999

void PrintDistance(int dist[][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                std::cout << "  BLOCK  ";
            }
            else {
                std::cout << "     " << dist[i][j] << "   ";
            }
        }
        std::cout << std::endl;
    }
}

void Floyd(int dist[][V]) {
    int i, j, k;                                                // i : start , j : end , k : intermediate

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    PrintDistance(dist);
}

int main()
{
    int graph[V][V] = { { 0, 5, INF, 10 },
                        { INF, 0, 3, INF },
                        { INF, INF, 0, 1 },
                        { INF, INF, INF, 0 } };

    Floyd(graph);

    return 0;
}