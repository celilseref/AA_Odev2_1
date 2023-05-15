#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_SIZE 20
#define MAX_WEIGHT 10

#define INF INT_MAX

// Celil Þeref *1210505053*

void generateArray(int array[], int size);
void sortArray(int array[], int size);
int calculateAverage(int array[], int size);
void calculateAllPairsShortestPath(int graph[][MAX_SIZE], int size, int shortestPaths[][MAX_SIZE]);
void printArray(int array[], int size);
void printGraph(int graph[][MAX_SIZE], int size);
void printShortestPaths(int shortestPaths[][MAX_SIZE], int size, int threshold);

int main() {
    int array[MAX_SIZE];
    int graph[MAX_SIZE][MAX_SIZE] = {
        {0, 10,  3,  0,  0,  5,  0, 17,  0, 22},
        {10,  0,  5,  0,  2,  0, 13,  0,  0,  0},
        {3,  5,  0,  2,  0,  4,  0, 21,  0, 11},
        {0,  0,  2,  0,  7,  0,  6,  0,  0,  0},
        {0,  2,  0,  7,  0,  6,  0,  0, 19,  0},
        {5,   0,  4,  0,  6,  0,  9,  3,  0,  0},
        {0, 13,  0,  6,  0,  9,  0,  4,  0,  0},
        {17,  0, 21,  0,  0,  3,  4,  0,  8,  0},
        {0,   0,  0,  0, 19,  0,  0,  8,  0,  5},
        {22,  0, 11,  0,  0,  0,  0,  0,  5,  0}
    };
    int shortestPaths[MAX_SIZE][MAX_SIZE];
    int threshold;

    srand(time(NULL));

    clock_t start, end;
    double time;

    start = clock();

    generateArray(array, MAX_SIZE);
    printf("Array:\n");
    printArray(array, MAX_SIZE);

    sortArray(array, MAX_SIZE);
    printf("\nSorted Array:\n");
    printArray(array, MAX_SIZE);

    threshold = calculateAverage(array, MAX_SIZE);
    printf("\nAverage: %d\n", threshold);

    printf("\nGraph:\n");
    printGraph(graph, MAX_SIZE);

    calculateAllPairsShortestPath(graph, MAX_SIZE, shortestPaths);
    printf("\nShortest Paths:\n");
    printShortestPaths(shortestPaths, MAX_SIZE, threshold);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %f sec\n", time);

    return 0;
}

void generateArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (2 * MAX_WEIGHT + 1) - MAX_WEIGHT;
    }
}

void sortArray(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

int calculateAverage(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

void calculateAllPairsShortestPath(int graph[][MAX_SIZE], int size, int shortestPaths[][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            shortestPaths[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (shortestPaths[i][k] != INF && shortestPaths[k][j] != INF &&
                    shortestPaths[i][k] + shortestPaths[k][j] < shortestPaths[i][j]) {
                    shortestPaths[i][j] = shortestPaths[i][k] + shortestPaths[k][j];
                }
            }
        }
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
}

void printGraph(int graph[][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (graph[i][j] == INF) {
                printf("INF ");
            }
            else {
                printf("%3d ", graph[i][j]);
            }
        }
        printf("\n");
    }
}

void printShortestPaths(int shortestPaths[][MAX_SIZE], int size, int threshold) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (shortestPaths[i][j] < threshold) {
                printf("%3d ", shortestPaths[i][j]);
            }
            else {
                printf("INF ");
            }
        }
        printf("\n");
    }
}
