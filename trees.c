#include <stdio.h>
#include <stdlib.h>

typedef struct tree tree;
struct tree {
    tree* left; // Ponteiro pro filho da esquerda
    int item;
    tree* right; // Ponteiro pro filho da direita;
};

void print_post_order (tree* bt) { // Quando "passa a direita" do nó, ou seja, vai imprimindo dos nós até a raiz;
    if (bt != NULL) {
        print_in_order(bt->left);
        print_in_order(bt->right);
        printf("%d\n", bt->item);
    }
}

void print_pre_order (tree* bt) { // Quando "passa a esquerda" do nó, imprime ao passar pelo nó;
    if (bt != NULL) {
        printf("%d\n", bt->item);
        print_in_order(bt->left);
        print_in_order(bt->right);
    }
}

void print_in_order (tree* bt) { // Quando "passa de baixo" do nó, imprime a folha, depoi o pai dela, depois a outra folha e o pai dela e assim vai;
    if (bt != NULL) {
        print_in_order(bt->left);
        printf("%d\n", bt->item);
        print_in_order(bt->right);
    }
}

tree* search(tree* bt, int item) {
    if (bt->item == item || bt == NULL) {
        return bt;
    }
    search(bt->left, item);
    search(bt->right, item);
}


tree* create_child(int item, tree* left, tree* right) { // Adicionar um novo no filho
    tree* new_child = (tree*) malloc(sizeof(tree));
    new_child->item = item;
    new_child->left = left;
    new_child->right = right;
    return new_child;
}

tree* create_empty_binary_tree() { // Cria uma nova arvore binaria;
    return NULL;
}

int main () {
    tree* arvore = create_empty_binary_tree();
}

/* tree* search(tree* bt, int item) { // Procura um valor na arvore -- > ignora
    // Funciona de forma semelhante à busca binaria;
    if ((bt == NULL) || bt->item == item) { // Se eu nao achei ou achei;
        return bt;
    } else if (bt->item >  item) {
        return search(bt->left, item);
    } else {
        return search(bt->right, item);
    }
} */