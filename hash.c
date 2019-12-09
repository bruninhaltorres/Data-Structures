#include <stdio.h>
#include <stdlib.h>

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

° Aqui tem com a solução linear pq e a que tem no slide;
 */

#define HASH_SIZE 11

typedef struct element element;
typedef struct hash_table hash_table;

struct element {
    int key, value;
};

struct hash_table {
    element *table[HASH_SIZE]; // Pq um array de ponteiros e nao um array normal? Por questões de memoria!
};

/* FALTA IMPLEMENTAR:
int get(hash_table *ht, int key); // Procura
void remove(hash_table *ht, int key); // Remove
int contains_key(hash_table *ht, int key); // ???????????
void print_hash_table(hash_table *ht); // Printa
 */

void put (hash_table *ht, int key, int value) { // Adiciona um novo valor na hash table;
    int h = key % HASH_SIZE; // Esse aqui que e o meu calculo que diz qual vai ser a posição no array que eu vou adicionar o elemento  
    while (ht->table[h] != NULL) {
        if (ht->table[h]->key == key) {
            ht->table[h]->value = value;
            break;
        }
        h = (h + 1) % 11;
    }
    if (ht->table[h] == NULL) {
        element *new_element = (element*) malloc(sizeof(element));
        new_element->key = key;
        new_element->value = value;
        ht->table[h] = new_element;
    }
}

hash_table* create_hash_table () { // Cria uma nova hash table;
    hash_table *new_hash_table = (hash_table*) malloc (sizeof(hash_table)); // Aquela alocação de espaço na memoria que a gente ja ta acostumado
    int i;
    for (i = 0; i < HASH_SIZE; i++) { // Navego pelo array e faço cada elemento apontar para nulo;
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}

int main () {
    hash_table *hash = create_hash_table();

}