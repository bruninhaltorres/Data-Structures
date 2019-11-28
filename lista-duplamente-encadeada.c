#include <stdio.h>
#include <stdlib.h>

// Neste codigo irei apenas comentar oq tiver diferente em relacao à outra lista;

/* 
    ° A lista duplamente encadeada, diferente da outra lista, possui a vantagem de que nela é possivel ir e voltar de um nó para o outro, pois agr, no struct eu salvo tanto a posicao do proximo, como a do anterior;
    ° Nela e mais facil remover um nó, pois agr eu preciso de apenas um ponteiro;
    ° Uma lista duplamente encadeada começa e termina num ponteiro nulo
 */

struct node {
    struct node *previous;
    int item;
    struct node *next;
};

typedef struct node node;

void print_list_normal(node *head) { // Imprime uma lista normalmente
    while(head != NULL) {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

void print_list_ao_contrario(node *tail) { // Imprime uma lista de trás pra frente
    while(tail->next != NULL){
        tail = tail->next;
    }
    while(tail != NULL){
        printf("%d ", tail->item);
        tail = tail->previous;
    }
    printf("\n");
}

node* remove_node (node *head, int item) { // Remove um nó na lista;
    node *current = head;

    while(current != NULL){
        if (current->item == item) { // Achei! :)
            if (current == head) { // Se o nó que eu quero remover for o primeiro da lista;
                head = current->next; // A minha cabeça agr aponta pro nó que vem logo após;
                // head->previous = NULL;//acho q precisa disso;
            } else { // Se o no nao for o primeiro da lista (incluindo o ultimo da lista);
                current->previous->next = current->next; // Eu faço o que vem antes dele apontar pro que vem depois dele;
            }
            if (current->next != NULL) { // Se o nó que eu quero remover nao for ultimo nó da lista;
                current->next->previous = current->previous; // O no que vem antes dele agora aponta pro que vem depois dele;
            }
            free(current); // Libero espaco na memoria;
            return head; // Retorno a nova lista;
        }
        current = current->next;
    }
    return head; // Se eu chegar aqui significa que eu percorri toda a lista e nao achei o nó com o item que eu quero remover;
}

node* search (node *head, int item) { // Procura um nó na lista;
    node *aux = head;
    while (aux != NULL) {
        if (aux -> item == item) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

node* add (node *head, int item) { // Adiciona um novo nó à lista;
    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = item;
    new_node->next = head;
    new_node->previous = NULL; // Como uma lista duplamente encadeada sempre começa e termina em um ponteiro nulo, sempre que adicionar um novo nó, eu devo dizer q o previous dele aponta pra um ponteiro nulo;
    if (head != NULL) head->previous = new_node;
    return new_node;
}

int is_empty(node* head) { // Verifica se a lista está vazia;
    return (head == NULL);
}

node* create_list() { // Cria uma nova lista;
    return NULL;
}

int main () {
    node* list = create_list();

    list = add(list, 7);
    list = add(list, 2);
    list = add(list, 0);
    list = add(list, 4);

    printf("Lista normal: ");
    print_list_normal(list);

    printf("Lista ao contrario: ");
    print_list_ao_contrario(list);
    printf("\n");

    printf("REMOVENDO ALGUNS VALORES\n\n");
    list = remove_node(list, 1);
    list = remove_node(list, 4);

    printf("Lista normal: ");
    print_list_normal(list);

    printf("Lista ao contrario: ");
    print_list_ao_contrario(list);
    
    return 0;
}