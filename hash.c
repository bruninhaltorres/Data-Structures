#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* 
========= HASH TABLES =======
° Tabela hash é uma estrutura de dados em que se guarda coisas, e cada coisa possui uma chave. 
° Dessa forma, estando em posse da chave é possivel tanto buscar quanto acessar essa "coisa" com O(1), pois já se vai direto no item desejado.
° Essa chave, ela pode ser qualquer coisa, como por exemplo o nome de um funcionário. Utilizando uma formula, (q o proprio programador decide qual é), se obtem a chave.
° Porém podem ocorrer casos em que dois itens acabem possuindo a mesma chave, por isso existem algumas tecnicas para tentar contornar essas "colisões".
° Um deles, é a utilização de numeros primos no cálculo da chave, que torna mais dificil a ocorrência de colisões, mas mesmo assim elas ainda podem ocorrer.
    * Lembrar de Array circular: usar modulo (%)
° Com isso, duas principais soluções são adotadas: A solução linear(a do vizinho) e a com listas encadeadas.
° Na solução linear, se ocorrer a colisão, os valores são salvos na proxima casa vazia. O problema disso é que as operações podem acabar ocorrendo em O(n).
° Na solução com listas, em cada posição do array há uma lista. Se ocorrer uma colisão, é adicionado mais um nó na lista daquela casa. O que com certeza é bem mais rapido.

° Aqui tem com a solução listas;
 */

#define HASH_SIZE 11

typedef struct element element;
typedef struct hash_table hash_table;
typedef struct node node;

struct node {
    node* next;
    int item;
    int key;
};

struct hash_table {
    node *table[HASH_SIZE]; // Pq um array de ponteiros e nao um array normal? Por questões de memoria!
};

// Verifica se ja foi adicionado um valor com aquela chave, retornando 1 se for encontrado e 0 caso contrario;
int contains_key(hash_table *ht, int key) {
    int h = key % HASH_SIZE;
    node* aux = ht->table[h];
    while (aux != NULL) {
        if (aux->key == key) return 1; 
        aux = aux->next;
    }
    return 0;
}

// Imprime uma lista encadeada;
void print_linked_list (node* head) {
    while (head != NULL) {
        printf ("Chave: %d, Item: %d ", head->key, head->item);
        head = head->next;
    }
    printf ("\n");
}

// Imprime uma hash table;
void print_hash_table(hash_table *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Posicao %d: ", i);
        print_linked_list(ht->table[i]);
    }
}

// Remove um valor na hash_table;
void remove_value(hash_table *ht, int key){
    int h = key % HASH_SIZE;
    node* aux = ht->table[h];
    node* previous = NULL;
    while (aux != NULL) {
        if (aux->key == key) {
            if (previous == NULL) {
                ht->table[h] = aux->next;
            } else {
                previous->next = aux->next;
            }
            free(aux);
            aux = NULL;
            return;
        }
        previous = aux;
        aux = aux->next;
    }
}

// Procura um valor na hash table
int get(hash_table *ht, int key) {
    int h = key % HASH_SIZE;
    node* aux = ht->table[h];
    while (aux != NULL) {
        if (aux->key == key) {
            return aux->item;
        }
        aux = aux->next;
    }
    return -1;
}

node* add_node(node* head, int item, int key) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node ->next = head;
    new_node->item = item;
    new_node->key = key;
    return new_node;
}

// Adiciona um novo valor na hash table;
void put (hash_table *ht, int key, int value) {
    int h = key % HASH_SIZE; // Esse aqui que e o meu calculo que diz qual vai ser a posição no array que eu vou adicionar o elemento  
    ht->table[h] = add_node(ht->table[h], value, key);
    return;
}

// Cria uma nova hash table;
hash_table* create_hash_table () {
    hash_table *new_hash_table = (hash_table*) malloc (sizeof(hash_table)); // Aquela alocação de espaço na memoria que a gente ja ta acostumado
    for (int i = 0; i < HASH_SIZE; i++) { // Navego pelo array e faço cada elemento apontar para nulo;
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}

int main () {
    char option;
    int key;
    printf ("Digite 'h' para iniciar a hash table, 's' para sair\n");
    scanf ("%c", &option);
    option = tolower(option);
    hash_table *hash;
    if (option == 'h') {
        hash = create_hash_table();
    }

    while (option != 's') {
        printf ("==========HASH TABLE==========\n");
        printf ("Digite 'p' para adicionar um valor à hash table\n");
        printf ("Digite 'g' para procurar um valor na hash table\n");
        printf ("Digite 'r' para remover um valor da hash table\n");
        printf ("Digite 'i' para imprimir a hash table\n");
        printf ("Digite 's' para sair\n");
        scanf ("%c", &option);
        option = tolower(option);
        
        switch (option) {
        case 'p':
            printf ("Insira a chave:");
            scanf ("%d", &key);
            if (!(contains_key(hash, key))) {
                printf ("Insira o valor:");
                int x;
                scanf ("%d", &x);
                put(hash, key, x);
            } else {
                printf ("Chave já utilizada!\n");
            }
            break;
        
        case 'g':
            printf ("Insira a chave:");
            scanf ("%d", &key);
            int x = get(hash, key);
            if (x == -1) {
                printf ("Não existe nenhum valor associado a essa chave\n");
            } else {
                printf ("O valor associado a essa chave é: %d\n", x);
            }
            break;
        

        case 'r':
            printf ("Insira a chave:");
            scanf ("%d", &key);
            remove_value(hash, key);
            break;

        case 'i':
            print_hash_table(hash);
            break;
        }
    } 
    return 0;
}