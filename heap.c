#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 11

typedef struct heap heap;

struct heap {
    int size;
    int data[MAX_SIZE];
};

void swap (int* a, int* b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

// Retorna o indice do pai;
int get_parent_index(heap *heap, int i) {
    return i / 2;
}

// Retorna o indice do filho à esquerda;
int get_left_index(heap *heap, int i) {
    return i * 2;
}

// Retorna o indice do filho à direita;
int get_right_index(heap *heap, int i) {
    return (i * 2) + 1;
}

// Retorna o item que estiver na posição i da heap;
int item_of(heap *heap, int i) {
    return heap->data[i];
}

// É a função responsavel para que a heap continue sendo uma heap;
void max_heapify(heap *heap, int i) {
    int largest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);

    if (left_index <= heap->size && heap->data[left_index] > heap->data[i]) {
        largest = left_index;
    } else {
        largest = i;
    }

    if (right_index <= heap->size && heap->data[right_index] > heap->data[largest]) {
        largest = right_index;
    }

    if (heap->data[i] != heap->data[largest]) {
        swap(&heap->data[i], &heap->data[largest]);
        max_heapify(heap, largest);
    }
}

// Remove o maior (ou menor se for uma min-heap) item da heap;
int dequeue (heap *heap) {
    printf ("AQUIIIII %d\n", heap->size);
    if (heap->size <= 0) {
        printf ("Heap Underflow\n");
        return -1;
    } else {
        printf ("... %d\n", heap->size);
        int item = heap->data[1];
        heap->data[1] = heap->data[heap->size];
        heap->size--;
        max_heapify (heap, 1);
        return item;
    }
}

// Adiciona um item à heap
heap *enqueue (heap *heap, int item) {
    if (heap->size >= MAX_SIZE) {
        printf ("Heap Overflow\n");
    } else {
        heap->data[++heap->size] = item; // Adiciono o item q eu quero;
        printf ("%d\n", heap->size);
        
        // Agora, tem que ordenar pra continuar sendo uma heap;
        int key_index = heap->size;
        int parent_index = get_parent_index(heap, heap->size);

        while (parent_index >= 1 && heap->data[key_index] > heap->data[parent_index]){
            swap(&heap->data[key_index], &heap->data[parent_index]);

            key_index = parent_index;

            parent_index = get_parent_index(heap, key_index);
        }
    }
    return heap;
}

// Cria uma nova heap;
heap *create_heap () {
    heap *new_heap = (heap*) malloc(sizeof(heap));
    new_heap->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        new_heap->data[i] = INT_MIN;
    }
    return new_heap;
}

int main () {
    int n;
    heap* heap = create_heap();
    while (scanf ("%d", &n) != EOF) {
        heap = enqueue(heap, n);       
    }

    while (heap->size > 0) {
        printf ("aq %d\n", heap->size);
        printf ("Desenfileirando o %d\n", dequeue(heap));
    }

    return 0;
}