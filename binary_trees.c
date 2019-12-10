#include <stdio.h>
#include <stdlib.h>

// NO VSCODE PRA APARECER O COMENTARIO E SO BOTAR NA LINHA A CIMA DA LINHA DA ASSINATURA DA FUNCAO

typedef struct tree tree;
struct tree {
    tree* left; // Ponteiro pro filho da esquerda
    int item;
    tree* right; // Ponteiro pro filho da direita;
};

// Quando "passa a direita" do nó, ou seja, vai imprimindo dos nós até a raiz;
void print_post_order (tree* bt) {
    if (bt != NULL) {
        print_post_order(bt->left);
        print_post_order(bt->right);
        printf("%d\n", bt->item);
    }
}

// Quando "passa a esquerda" do nó, imprime ao passar pelo nó;
void print_pre_order (tree* bt) { 
    if (bt != NULL) {
        printf("%d\n", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

// Quando "passa de baixo" do nó, imprime a folha, depoi o pai dela, depois a outra folha e o pai dela e assim vai;
void print_in_order (tree* bt) { 
    if (bt != NULL) {
        print_in_order(bt->left);
        printf("%d\n", bt->item);
        print_in_order(bt->right);
    }
}

// Procura um valor na arvore
tree* search(tree* bt, int item) { 
    // Funciona de forma semelhante à busca binaria;
    if ((bt == NULL) || bt->item == item) { // Se eu nao achei ou achei;
        return bt;
    } else if (bt->item >= item) {
        return search(bt->left, item);
    } else {
        return search(bt->right, item);
    }
}

tree* remove_node (tree* bt, int item) {
    tree* x = search(bt, item);
    if (x == NULL) {
        printf ("Você está tentando remover um nó que nao esta na arvore ????\n");
        return NULL;
    } else {
        if (x->left == NULL && x->right == NULL) { // Se eu to tentando remover uma folha;
            free(x);
            x = NULL;
        } else if (x->left == NULL && x->right != NULL) { // se so tiver filho na direita;

        } else if (x->left != NULL && x->right == NULL) { // Se so tiver filho na esquerda;

        } else { // Se tem filho dois lados;

        }
    }
    return bt;
}

// Adiciona um novo no filho
tree* create_tree(int item, tree* left, tree* right) {
    tree* new_child = (tree*) malloc(sizeof(tree));
    new_child->item = item;
    new_child->left = left;
    new_child->right = right;
    return new_child;
}

// Procura onde eu devo adicionar um novo no da lista;
tree* add(tree* bt, int item) { // Procura onde eu devo adicionar um novo no da lista;
    if (bt == NULL) {
        bt = create_tree(item, NULL, NULL);
    } else if (bt->item > item) {
        bt->left = add(bt->left, item);
    } else {
        bt->right = add(bt->right, item);
    }
    return bt;
}

// Cria uma nova arvore binaria vazia;
tree* create_empty_binary_tree() { 
    return NULL;
}

int main () {
    tree* arvore = create_empty_binary_tree();
    arvore = create_tree(4, NULL, NULL);
    arvore = add(arvore, 2);
    arvore = add(arvore, 1);
    arvore = add(arvore, 6);
    arvore = add(arvore, 9);
    arvore = add(arvore, 3);

    printf("#########################################\n");
    printf("ARVORE EM PRÉ ORDEM\n");
    print_pre_order(arvore);

    printf("#########################################\n");
    printf("ARVORE EM ORDEM\n");
    print_in_order(arvore);

    printf("#########################################\n");
    printf("ARVORE EM POS ORDEM\n");
    print_post_order(arvore);
    return 0;
}