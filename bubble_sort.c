#include <stdio.h>

void swap (int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void bubble_sort(int *v, int size) {
    int i, j;
    for (j = size - 1; j >= 0; j--) {
        for (i = 0; i < j; i++) {
            if (v[i] > v[i+1]) {
                swap(&v[i], &v[i+1]);
            }
        }
    }
}

void print_array (int array[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf ("%d ", array[i]);
    }
    printf ("\n");
}

int main () {
    int n;
    scanf ("%d", &n);
    int array[n], i;
    for (i = 0; i < n; i++) {
        scanf ("%d", &array[i]);
    }

    printf ("Array antes de ser ordenado: ");
    print_array(array, n);

    bubble_sort(array, n);

    printf("Array ordenado: ");
    print_array(array, n);

    return 0;
}