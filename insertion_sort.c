#include <stdio.h>

void swap (int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void insertion_sort(int v[], int size) {
    int i, j, key;
    for (i = 1; i < size; i++) {
        key = v[i];
        j = i - 1;
        while ((j >= 0) && (v[j] > key)) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
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

    insertion_sort(array, n);

    printf("Array ordenado: ");
    print_array(array, n);

    return 0;

}