#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define A_SIZE 20
#define G_SIZE 10
#define MAX_W 10

#define INF INT_MAX

void generate(int a[], int size);
void function1(int a[], int size);
int function2(int a[], int size);
void function3(const int g[][G_SIZE], int d[][G_SIZE], int size);
void printArray(const int arr[], int size);
void printMatrix(const int mat[][G_SIZE], int size);
void printShortestPaths(const int dist[][G_SIZE], int size, int threshold);

int main() {
    int a[A_SIZE];
    int g[G_SIZE][G_SIZE] = {
        {0, 10, 3, 0, 0, 5, 0, 17, 0, 22},
        {10, 0, 5, 0, 2, 0, 13, 0, 0, 0},
        {3, 5, 0, 2, 0, 4, 0, 21, 0, 11},
        {0, 0, 2, 0, 7, 0, 6, 0, 0, 0},
        {0, 2, 0, 7, 0, 6, 0, 0, 19, 0},
        {5, 0, 4, 0, 6, 0, 9, 3, 0, 0},
        {0, 13, 0, 6, 0, 9, 0, 4, 0, 0},
        {17, 0, 21, 0, 0, 3, 4, 0, 8, 0},
        {0, 0, 0, 0, 19, 0, 0, 8, 0, 5},
        {22, 0, 11, 0, 0, 0, 0, 0, 5, 0}
    };
    int d[G_SIZE][G_SIZE];
    int t;

    srand(time(NULL));

    clock_t start, end;
    double time;

    start = clock();

    generate(a, A_SIZE);
    printf("A:\n");
    printArray(a, A_SIZE);

    function1(a, A_SIZE);
    printf("\nFunction1 Sonuc:\n");
    printArray(a, A_SIZE);

    t = function2(a, A_SIZE);
    printf("\nFunction2 Sonuc: %d\n", t);

    printf("\nG:\n");
    printMatrix(g, G_SIZE);

    function3(g, d, G_SIZE);
    printf("\nFunction3 Sonuc:\n");
    printMatrix(d, G_SIZE);

    printf("\n%d icin sonuc:\n", t);
    printShortestPaths(d, G_SIZE, t);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCalisma Suresi: %f sn\n", time);

    return 0;
}
void generate(int a[], int size) {
for (int i = 0; i < size; i++) {
a[i] = rand() % (2 * MAX_W) - MAX_W;
}
}

void function1(int a[], int size) {
for (int i = 0; i < size - 1; i++) {
for (int j = 0; j < size - 1 - i; j++) {
if (a[j] > a[j + 1]) {
int tmp = a[j];
a[j] = a[j + 1];
a[j + 1] = tmp;
}
}
}
}

int function2(int a[], int size) {
int t = 0, current_sum = 0, count = 0;
for (int i = 0; i < size; i++) {
if (current_sum + a[i] > 0) {
current_sum += a[i];
}
else {
current_sum = 0;
}
if (current_sum > t) {
t = current_sum;
count++;
}
}
return (count != 0) ? t / count : 0;
}

void function3(const int g[][G_SIZE], int d[][G_SIZE], int size) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
if (i == j) {
d[i][j] = 0;
}
else if (g[i][j] != 0) {
d[i][j] = g[i][j];
}
else {
d[i][j] = INF;
}
}
}
for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (d[i][k] != INF && d[k][j] != INF &&
                d[i][k] + d[k][j] < d[i][j]) {
                d[i][j] = d[i][k] + d[k][j];
            }
        }
    }
}
}

void printArray(const int arr[], int size) {
for (int i = 0; i < size; i++) {
printf("%d ", arr[i]);
if ((i + 1) % 10 == 0) {
printf("\n");
}
}
}

void printMatrix(const int mat[][G_SIZE], int size) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
if (mat[i][j] == INF) {
printf("INF ");
}
else {
printf("%3d ", mat[i][j]);
}
}
printf("\n");
}
}

void printShortestPaths(const int dist[][G_SIZE], int size, int threshold) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
if (i != j && dist[i][j] < threshold) {
printf("%c -> %c: %d\n", 'A' + i, 'A' + j, dist[i][j]);
}
}
}
}