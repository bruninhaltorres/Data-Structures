#include <stdio.h>

void swap (int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void selection_sort(int array[], int n) {
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
            swap(&array[i], &array[min]);
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

    selection_sort(array, n);

    printf("Array ordenado: ");
    print_array(array, n);

    return 0;
}