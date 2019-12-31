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

tree *create_tree (int item) {
    tree *new_tree = (tree*) malloc(sizeof(tree));
    new_tree->item = item;
    new_tree->left = NULL;
    new_tree->right = NULL;
    return new_tree;
}

void insere (tree *tree, int pai, int esquerda, int direita) {
    if (tree == NULL) {
        return;
    } else if (tree->item == pai) {
        if (esquerda != -1) tree->left = create_tree(esquerda);
        if (direita != -1) tree->right = create_tree(direita);
        return;
    }
    insere(tree->left, pai, esquerda, direita);
    insere(tree->right, pai, esquerda, direita);
}

int main () {
    tree* arvore = create_empty_binary_tree();
}

int main () {
    int n;
    scanf ("%d", &n);
    
    int i;
    int x, e, d;
    scanf ("%d %d %d", &x, &e, &d);
    tree *tree = create_tree(x);
    tree->right = create_tree(d);
    tree->left = create_tree(e);

    for (i = 1; i < n; i++) {
        scanf ("%d %d %d", &x, &e, &d);
        insere (tree, x, e, d);
    }

    return 0;
}