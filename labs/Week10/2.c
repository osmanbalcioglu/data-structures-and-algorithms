
#include <stdio.h>
#define N 5

int graph[N][N] = {
    {0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1},
    {0, 1, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0}
};
int i;
int visited[N] = {0};

void BFS(int start) {
    int queue[N];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        printf("%c ", 'A' + current);

        for (i = 0; i < N; i++) {
            if (graph[current][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    printf("BFS: ");
    BFS(0);

    return 0;
}

