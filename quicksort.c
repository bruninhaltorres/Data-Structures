// TA ERRADO!!!

#include <stdio.h>

#define DEBUG(x) if(x)

void array_print(int array[], int n) {
    int i;
    for (i = 0; i < n; i++) printf ("%d ", array[i]);
    printf ("\n");
}

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
    DEBUG(1) printf("trocando %d e %d...\n", *a, *b);
}

void quick_sort(int *v, int size) {
    if (size <= 1) {
        return;
    }
    
    int c = size / 2;
    int pivot = v[c];
    int a = 0;
    int b = size - 1;

    DEBUG(1) printf("size ::: %d e pivot :: %d\n", size, pivot);
    DEBUG(1) array_print(v, size);

    while (a < b) {
        while (v[a] < pivot) a++;
        while (v[b] > pivot) b--;
        if (v[a] > v[b])
            swap(&v[a], &v[b]);
        else {
            if (a < c) a++;
            else if (b > c) b--;
        }
    }
    
    DEBUG(1) printf("a :: %d e b :: %d\n", a, b);
    DEBUG(1) array_print(v, size);

    quick_sort(v, b);
    quick_sort(v + a, size - a);
}

int main () {
    int n, i;
    scanf ("%d", &n);
    int array[n];
    for (i = 0; i < n; i++) scanf ("%d", &array[i]);

    printf ("Array antes de ser ordenado: ");
    array_print(array, n);

    printf("Array depois de ser ordenado: ");
    DEBUG(1) printf("\n");
    quick_sort(array, n);
    array_print (array, n);

    return 0;
}