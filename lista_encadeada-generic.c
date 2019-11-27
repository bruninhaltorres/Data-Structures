#include <stdio.h>
#include <stdlib.h>

/* ========= RESUMO ========= (admito que estou com preguiça de usar o "marcadão" (markdown))
° Uma lista encadeada é uma estrutura de dado semelhante ao array, porém a sua principal vantagem em relação ao array é que nela os "espaços" de memoria não precisam estar juntos.
° Para a lista encadeada se faz necessário usar um struct (~ate q pq e ESTRUTURAS de dados ne kkkkj~), pois além de salvar o que eu desejo guardar (int, char, float, etc...), eu também desejo salvar o elemento do próximo elemento na lista.
° Cada um desses "elementos" da lista encadeada recebe o nome de nó. Uma lista encadeada acaba no nó que apontar para um ponteiro nulo (nó == NULL). O inicio da lista recebe o nome de "head".
° Além de não precisar de espaços contiguos de memória, para a inserção de um novo nó custa apenas O(1), em contrapartida, acessar um elemento da lista custa O(n), pois devemos percorrer a lista linearmente até achar o que queremos.
° Ao adicionarmos um novo nó na lista, ao invés de adicionarmos no final (como normalmente e feito no array), adicionamos no inicio, este novo nó sera agora a cabeça da minha lista.
° EXTRA: Para criar funcoes genericas, devemos usar ponteiros para void (Ponteiros para void são variaveis q recebem qualquer tipo (char, float, int, etc...), diferente de um ponteiro para int que receberia apenas inteiros).
 */

struct node {
    struct node *next;
    int *item;
};

typedef struct node node;

int int_compare (void* a, void* b) { // Funcao de comparacao de 2 inteiros;
    return (*((int*) a) == *((int*) b)); 
}

node* remove_node (node *head, void* item, int(*compare_function)(void*, void*)) { // Remove um nó da lista;
    // A lógica por trás de remover um nó da lista é: Eu salvo o endereço do nó que eu quero remover, e salvo o endereço q ele apontava (em duas variaveis diferentes), ai eu digo, que o nó que vem antes do que eu quero excluir agora aponta para onde o que eu quero excluir apontava, e dou um free() no que eu quero excluir;
    node *previous = NULL; // Eu devo salvar o nó anterior ao que eu quero apagar no previous;
    node *current = head; // Eu devo salvar o nó que eu quero apagar no current;
    while (current != NULL && (!((*compare_function)(current->item, item)))) { // Enquando current for diferente de NULL (ou seja, eu estiver nos limites da lista) e o item salvo no nó atual for diferente do item cujo nó desejo apagar (ou seja, se eu achar o nó que possui o item que eu desejo apagar eu paro);
        previous = current; // O meu anterior vai ser o meu atual;
        current = current->next; // Vou para o próximo;
    }
    if (current ==  NULL) { // Se eu cheguei ao final da lista, significa que eu nao achei o que queria apagar;
        return head; // Retorno a lista;
    }
    if (previous == NULL) { // Se previous for NULL, significa que o nó que eu quero apagar é o primeiro nó da lista
        head = current->next; // O inicio da lista agora aponta para onde o nó que eu quero apagar apontava;
    } else { // Se não, é um nó em qualquer outra posição da lista;
        previous->next = current->next; // O nó anterior ao que eu quero apagar agora aponta para onde o nó que eu quero apagar aponta;
    }
    free(current); // Apago o nó que eu quero;
    return head; // Retorno a nova lista;
}

node* search (node *head, void* item, int(*compare_function)(void*, void*)) { // Procura um elemento na lista;
    // Como eu desejo criar uma funcao generica e para isso uso ponteiro para void, faz-se necessario usar alguma outra forma de comparação ao invés de simplesmente (head->item == item), logo, uma das alternativas e utilizar ponteiro para função, essa função irá dar qual o parametro de comparação de dois elementos.
    node *aux = head;
    while (aux != NULL) { // Enquanto o meu ponteiro aux nao for nulo;
        if ((*compare_function)(aux->item, item)) { // Se o retorno da minha funcao de comparacao for 1 (ou seja, oq e quero e igual a oq eu tenho);
            return aux; //retorno o endereço do item;
        }
        aux = aux->next; // Se não, eu vou pro próximo;
    }
    return NULL; // Se eu cheguei no final da lista e não achei, retorno NULL;
}

void print_list(node *head) { // Printa os elementos da lista;
    while (head != NULL) { // Enquanto o meu ponteiro nao for nulo(final da lista);
        printf ("%d ", *((int*) head->item)); // Printo o valor;
        head = head->next; // Vou para o proximo;
    }
    printf("\n");
}

node* add(node* head, void* item) { // Adiciona um novo nó à lista encadeada;
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
    int i;
    node *aux;

    if (is_empty(list)) printf ("A lista esta vazia\n");
    else printf ("A lista nao esta vazia\n");

    // Quando eu adiciono um novo nó na minha lista, eu preciso dizer que a minha head é agora o meu novo nó;
    i = 3;
    list = add(list, &i);
    i = 5;
    list = add(list, &i);
    i = 1;
    list = add(list, &i);
    i = 8;
    list = add(list, &i);
    i = 2;
    list = add(list, &i);
    
    if (is_empty(list)) printf ("A lista esta vazia\n");
    else printf ("A lista nao esta vazia\n");

    print_list(list);
    
    /* i = 0;
    
    aux = search (list, &i, int_compare);
    if (aux ==  NULL) printf ("O numero %d nao esta na lista\n", i);
    else printf ("O numero %d esta na lista\n", i);
    
    free(aux);

    printf ("Lista antes de apagar alguns elementos: ");
    print_list(list);

    i = 2;
    remove_node(list, &i, int_compare); // Removendo o primeiro item da lista;
    print_list(list);
 
    i = 4;
    remove_node(list, &i, int_compare); // Tentando remover um item que nao esta na lista;
    print_list(list);

    i = 5;
    remove_node(list, &i, int_compare); // Removendo um item qualquer da lista;
    print_list(list); */

    return 0;
}