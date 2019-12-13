#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Essa é a versão da bruna, vou fazer a minha dps

typedef struct node NODE;
typedef struct graph GRAPH;
typedef struct queue QUEUE;

struct node {
    NODE *next;
    int value;
};

struct queue{
    NODE *front;
    NODE *end;
};

struct graph {
    NODE *vertex[90000];
    bool visited[90000];
    int graph_size;
};

// Adiciona um nó à lista;
NODE *create_node(int new_value) { 
    NODE *new_node = (NODE*) malloc(sizeof(NODE));
    new_node->next = NULL;
    new_node->value = new_value;
    return new_node;
}

// Cria uma nova fila;
QUEUE *create_queue(){
    QUEUE *queue = (QUEUE*) malloc(sizeof(QUEUE));
    queue->front = NULL;
    queue->end = NULL;
    return queue;
}

// Verifica se a fila está vazia
bool is_empty(QUEUE *queue) {
    return queue->front == NULL;
}

// Enfileira, adicionado ao final da fila
void enqueue(QUEUE *queue, int value){
    if(is_empty(queue)){ // Se a fila estiver vazia
        NODE *new_node = create_node(value);

        queue->front = new_node;
        queue->end = new_node;
    } else {
        NODE *end_node = queue->end;

        queue->end = create_node(value);
        end_node->next = queue->end;
    }
}

// Desenfileira (foi essa aq que eu tirei os asteriscos)
int dequeue(QUEUE **queue) {
    if (is_empty(*queue)) {
        printf("Empty *queue");
        return -1;
    } else if ((*queue)->front->next == NULL) { //ver se so possui um elemento
        NODE *saved = (*queue)->front;
        int value = saved->value;

        (*queue)->front = NULL;
        free(saved);
        return value;
    } else {
        NODE *saved = (*queue)->front;
        int value = saved->value;
        (*queue)->front = saved->next;
        
        free(saved);
        return value;
    }
}

// Imprime uma lista;
void print_list(NODE *head) {
    NODE *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);    
        current = current->next;
    }
    printf("\n");
}

// Imprime uma fila;
void print_queue(QUEUE *queue) {
    print_list(queue->front);
}

// Printa um grafo
void print_graph(GRAPH *graph) {
    // Eu vou num vertice e imprimo todos que com quem ele possui conexão;  
    for (int i = 0; i < graph->graph_size; ++i) {
        printf("Vertice de numero %d: ", i);
        NODE *head = graph->vertex[i];

        while (head != NULL) {
            printf("%d -> ", head->value);
            head = head->next;
        }
        printf("\n");
    }
}

// Cria um novo grafo
GRAPH *create_graph (int sz) {
    GRAPH *new_graph = (GRAPH*) malloc(sizeof(GRAPH)); // Alocando o espaço para um grafo na memoria;
    new_graph->graph_size = sz;

    for (int i = 0; i < sz; ++i) { // Inicializo todos os elementos do array;
        new_graph->vertex[i] = NULL;
        new_graph->visited[i] = false;
    }  
    return new_graph;
}

// Adiciona um novo nó no final da lista
NODE *insert_end(NODE *head, int new_value) {
    NODE *current = head;
    if (current == NULL) { // Se a minha lista estiver vazia;
        return create_node(new_value);
    }

    while (current->next != NULL) { // Vou ate o final da lista naquela posição do array;
        current = current->next;
    }
    
    current->next = create_node(new_value); // Adiciono um novo nó da lista;
    return head;
}

// Adiciona uma nova aresta
void add_edge(GRAPH *graph, int from, int to) {
    // Se for um grafo direcionado so adiciona a ida, se nao for, adiciona a ida e a volta;
    graph->vertex[from] = insert_end(graph->vertex[from], to); // para grafos direcionados
    // graph->vertex[to] = insert_end(graph->vertex[to], from); // para grafos nao direcionados
}

// Realiza a busca em largura em um grafo;
void BFS(GRAPH *graph, int source) { 
    // FUnciona de maneira semelha a busca por altura de uma arvore, ja que eu primeiro visito os nós de um nivel para depois visitar os nós de outro nivel;7
    // Para fazer isso eu uso uma lista, eu adiciono o nó na lista, enfileiro ele, visito ele, e adiciono os filhos dele à fila
    // busca em largura costuma ser útil para descobrir o menor caminho entre dois pontos para grafos não ponderados.
    graph->visited[source] = true; // Digo que eu ja visitei aquela aresta
    QUEUE *queue = create_queue(); // Crio uma fila
    enqueue(queue, source); // Enfileiro a minha aresta atual;

    while (!(is_empty(queue))) {
        int from = dequeue(&queue);// Desenfileiro um nó
        NODE *adjacence_list = graph->vertex[from]; // Crio uma lista que aponte pra lista de adjacencia do meu no desenfileirado;
        printf("Iniciando Busca em Largura a partir do %d\n", from);
        
        while (adjacence_list != NULL) { // Percorro a lista de adjacencia
            int to = adjacence_list->value;
            if (!(graph->visited[to])) { // Se eu nao visitei aquela aresta
                graph->visited[to] = true; // Digo que ja visitei;
                printf("Enfileirando o %d\n", to);
                enqueue(queue, to); // Enfileiro;
            }
            adjacence_list = adjacence_list->next;
        }    
    }
}

// Realiza a busca em profundidade em um grafo
void DFS(GRAPH *graph, int source) {
    if (graph->visited[source]) return;
    
    graph->visited[source] = true; // Marco como visitado aquele vertice
    NODE *head = graph->vertex[source]; //pego a cabeca da lista de adjacencia daquele 
    
    printf("Iniciando Busca em Profundidade a partir do %d\n", source);
    
    while (head != NULL) { // Vou nos nós conectados ao meu no atual (Ex.: Se o 2 é conectado no 3 e no 8 e o 3 é conectado no 4, 5, 6 e 7. Eu vou primeiro no dois, do dois eu vou pro 3, do 3 eu vou pro 4, ai eu volto e dps do 3 eu vou pro 5, ai eu volto e do 3 eu vou pro 6, ai volto de novo e do 3 eu vou pro 7. Agora que ja visitei todos os filhos do 3, eu volto pro 2 de novo e agr vou visitar o 8 seguindo mesmo processo que foi para o três, e fim :));
        DFS(graph, head->value); 
        head = head->next;
    }
}

void reset (GRAPH *graph) {
    for (int  i = 0; i < graph->graph_size; i++) {
        graph->visited[i] = false;
    }
}

int main() {
    int number_of_vertex, number_of_edges;
    scanf("%d", &number_of_vertex);
    
    GRAPH *graph = create_graph(number_of_vertex);
    scanf("%d", &number_of_edges);

    for (int i = 0; i < number_of_edges; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        add_edge(graph, from, to);
    }
    
    BFS(graph, 0);
    print_graph(graph);
    reset (graph);
    DFS(graph, 0); 
    return 0;
}