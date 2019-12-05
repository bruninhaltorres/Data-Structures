#include <stdio.h>
#include <stdlib.h>

/* ==== RESUMINHO ===
° A stack (ou pilha) é uma estrutura de dados que funciona de forma semelhante a uma pilha da vida real, onde eu so posso acessar o item que estiver no topo da pilha;
° A pilha e util em situacoes que se deseja restringir o acesso aos dados, de forma que so se pode acessar o ultimo item adicionado;
° A pilha funciona de uma forma chamada "LIFO: Last In, First Out" (O ultimo a entrar e o primeiro a sair);
° A pilha possui duas formas de ser implementada: a forma estática, em que se usa Arrays e a forma dinamica, usando listas.
° Neste codigo, eu mostrarei a implementação estática.
 */

#define MAX_SIZE 4 // Defino o tamanho maximo da pilha

typedef struct stack { // Numa pilha estatica, a pilha tem um tamanho limitado, que e o tamanho do array;
    int current_size; // Serve para indicar qual o tamanho atual da pilha e tambem para navegar nela
    int itens[MAX_SIZE]; // A pilha propriamente dita;
} stack;

int is_empty (stack *stack) { // Verifica se a pilha ta vazia
    return (stack->current_size == 0);
}

int peek (stack *stack) { // Retorna qual o elemento no topo da lista
    if (is_empty(stack)) {
        printf ("Stack Overflow\n");
        return -1;
    } else {
        return stack->itens[stack->current_size - 1];
    }
}

int pop (stack *stack) { // Remove o elemento no topo da pilha, retornando-o
    if (is_empty(stack)) { // Se a stack ta vazia nao da pra remover :(
        printf ("Stack Overflow\n");
        return -1;
    } else {
        return stack->itens[--stack->current_size]; // Remove e diminui o tamanho atual
    }
}

int push (stack* stack, int item) { // Adiciona Um novo item na stack;
    if (stack->current_size >= MAX_SIZE) { // Se a stack ja estiver cheia
        printf ("Stack Overflow\n");
        return -1; // Imprimo uma mensagem indicando que ela esta cheia
    } else {
        stack->itens[stack->current_size++] = item; // Adiciono um novo item e aumento o current_size(so lembrar da diferença ente i++ e ++i);
        return 0;
    }
}

stack* create_stack () { // Cria uma nova pilha
    stack *new_stack = (stack*) malloc(sizeof(stack)); // Aloco na memoria espaco para uma nova pilha e faco a minha nova pilha apontar pra ela;
    new_stack->current_size = 0; // O tamanho da pilha começa como 0;
    return new_stack;
}

int main () {
    stack *pilha = create_stack();
    
    int x;
    scanf ("%d", &x);
    printf ("Adicionando o %d\n", x);
    while (push(pilha, x) != -1) {
        scanf ("%d", &x);
        printf ("Adicionando o %d\n", x);
    }

    printf ("O valor no topo da pilha eh: %d\n", peek(pilha));

    x = pop(pilha);
    while(x != -1) {
        printf ("Desempilhando o %d\n", x);
        x = pop(pilha);
    }
       
    return 0;
}