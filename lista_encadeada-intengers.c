#include <stdio.h>
#include <stdlib.h>

#define DEBUG if(1)

/* ========= RESUMO ========= (admito que estou com preguiça de usar o "marcadão" (markdown))
° Uma lista encadeada é uma estrutura de dado semelhante ao array, porém a sua principal vantagem em relação ao array é que nela os "espaços" de memoria não precisam estar juntos.
° Para a lista encadeada se faz necessário usar um struct (~ate q pq e ESTRUTURAS de dados ne kkkkj~), pois além de salvar o que eu desejo guardar (int, char, float, etc...), eu também desejo salvar o elemento do próximo elemento na lista.
° Cada um desses "elementos" da lista encadeada recebe o nome de nó. Uma lista encadeada acaba no nó que apontar para um ponteiro nulo (nó == NULL). O inicio da lista recebe o nome de "head".
° Além de não precisar de espaços contiguos de memória, para a inserção de um novo nó custa apenas O(1), em contrapartida, acessar um elemento da lista custa O(n), pois devemos percorrer a lista linearmente até achar o que queremos.
° Ao adicionarmos um novo nó na lista, ao invés de adicionarmos no final (como normalmente e feito no array), adicionamos no inicio, este novo nó sera agora a cabeça da minha lista.
 */

struct node {
    struct node *next;
    int item;
};

typedef struct node node;

node* remove_node (node *head, int item) { // Remove um nó da lista;
    node *previous = NULL;
    node *current = head;
    while (current != NULL) {
        if (current->item == item) { // Achei! :)
            if (previous == NULL) {
                head = head->next;
                free(current);
                current = NULL;
                return head;
            } else {
                previous->next = current->next;
                free(current);
                current = NULL;
                return head;
            }
        }
        previous = current;
        current = current->next;
    }
    return NULL;
}

node* search (node *head, int item) { // Procura um elemento na lista;
    node *aux = head;
    while (aux != NULL) { // Enquanto o meu ponteiro head nao for nulo;
        if (aux->item == item) { // Achei! :)
            return aux; //retorno o endereço do item;
        }
        aux = aux->next; // Se não, eu vou pro próximo;
    }
    return NULL; // Se eu cheguei no final da lista e não achei, retorno NULL;
}

void print_list(node *head) { // Printa os elementos da lista;
    while (head != NULL) { // Enquanto o meu ponteiro nao for nulo(final da lista);
        printf ("%d ", head->item); // Printo o valor;
        head = head->next; // Vou para o proximo;
    }
    printf("\n");
}

node* add(node* head, int item) { // Adiciona um novo nó à lista encadeada;
    node *new_node = (node*) malloc(sizeof(node)); // Crio um nó auxiliar, alocando na memória o espaço para um nó;
    new_node->item = item; // Salvo o item no nó;
    new_node->next = head; // Faço o next apontar para o endereço de memória de head;
    return new_node; // Retorno o endereço de memoria do novo nó;
}

int is_empty (node* head) { // Verifica se a lista está vazia.
    return (head == NULL); // Se a lista está vazia, significa o head (O ultimo nó adicionado na lista) é o vetor nulo;
}

node* creat_list() { // Cria uma nova lista encadeada;
    return NULL; // Como o ultimo elemento da lista encadeada sempre é um ponteiro nulo, ao fazer isso, estamos dizendo onde a lista encadeada "termina";
}

int main () {
    node *list = creat_list(); // Crio uma nova lista, (começando com o NULL);

    if (is_empty(list)) printf ("A lista esta vazia\n");
    else printf ("A lista nao esta vazia\n");

    // Quando eu adiciono um novo nó na minha lista, eu preciso dizer que a minha head é agora o meu novo nó;
    list = add(list, 3);
    list = add(list, 5);
    list = add(list, 1);
    list = add(list, 8);
    list = add(list, 2);
    
    if (is_empty(list)) printf ("A lista esta vazia\n");
    else printf ("A lista nao esta vazia\n");

    printf ("Lista: ");
    print_list(list);
    
    node *aux1, *aux2;
    aux1 = search (list, 0);
    aux2 = search (list, 1);
    if (aux1 ==  NULL) printf ("O numero 0 nao esta na lista\n");
    else printf ("O numero 0 esta na lista\n");
    if (aux2 ==  NULL) printf ("O numero 1 nao esta na lista\n");
    else printf ("O numero 1 esta na lista\n");
    /* free(aux1);
    free(aux2); */
    DEBUG print_list(list);

    DEBUG printf ("Apagando o 2:\n");
    remove_node(list, 2); // Removendo o primeiro item da lista;
    print_list(list);

    DEBUG printf ("Apagando o 4\n");
    remove_node(list, 4); // Tentando remover um item que nao esta na lista;
    print_list(list);

    DEBUG printf ("Apagando o 5\n");
    remove_node(list, 5); // Removendo um item qualquer da lista;
    print_list(list);

    return 0;
}
