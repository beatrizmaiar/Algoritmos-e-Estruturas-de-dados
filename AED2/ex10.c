#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node {
    int num_keys;
    int* keys;
    struct Node** children;
    bool is_leaf;
} Node;
 
Node* create_node(int M) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->num_keys = 0;
    new_node->is_leaf = true;
    new_node->keys = (int*)malloc(sizeof(int) * (M - 1));
    new_node->children = (Node**)malloc(sizeof(Node*) * M);
    for (int i = 0; i < M - 1; i++) {
        new_node->keys[i] = 0;
    }
    for (int i = 0; i < M; i++) {
        new_node->children[i] = NULL;
    }
    return new_node;
}
 
void split_childimpar(Node* parent, int child_index, int M) {
    Node* child = parent->children[child_index];
    Node* new_node = create_node(M);
    new_node->is_leaf = child->is_leaf;
    new_node->num_keys = M / 2;
 
    for (int i = 0; i < M / 2; i++) {
        new_node->keys[i] = child->keys[i + M / 2];
    }
 
    if (!child->is_leaf) {
        for (int i = 0; i <= M / 2; i++) {
            new_node->children[i] = child->children[i + M / 2];
        }
    }
 
    child->num_keys = M / 2 - 1;
 
    for (int i = parent->num_keys; i > child_index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
 
    parent->children[child_index + 1] = new_node;
 
    for (int i = parent->num_keys - 1; i >= child_index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
 
    parent->keys[child_index] = child->keys[M / 2 - 1];
    parent->num_keys++;
}
 
void split_childpar(Node* parent, int child_index, int M) {
    Node* child = parent->children[child_index];
    Node* new_node = create_node(M);
    new_node->is_leaf = child->is_leaf;
    new_node->num_keys = (M - 1) / 2;
 
    for (int i = 0; i < (M - 1) / 2; i++) {
        new_node->keys[i] = child->keys[i + (M - 1) / 2 + 1];
    }
 
    if (!child->is_leaf) {
        for (int i = 0; i < M / 2; i++) {
            new_node->children[i] = child->children[i + (M - 1) / 2 + 1];
        }
    }
 
    child->num_keys = (M - 1) / 2;
 
    for (int i = parent->num_keys; i > child_index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
 
    parent->children[child_index + 1] = new_node;
 
    for (int i = parent->num_keys - 1; i >= child_index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
 
    parent->keys[child_index] = child->keys[(M - 1) / 2];
    parent->num_keys++;
}
 
void insert_non_fullimpar(Node* node, int key, int M) {
    int i = node->num_keys - 1;
 
    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
 
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
 
        i++;
 
        if (node->children[i]->num_keys == M - 1) {
            split_childimpar(node, i, M);
 
            if (key > node->keys[i]) {
                i++;
            }
        }
 
        insert_non_fullimpar(node->children[i], key, M);
    }
}
 
void insert_non_fullpar(Node* node, int key, int M) {
    int i = node->num_keys - 1;
 
    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
 
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
 
        i++;
 
        if (node->children[i]->num_keys == M - 1) {
            split_childpar(node, i, M);
 
            if (key > node->keys[i]) {
                i++;
            }
        }
 
        insert_non_fullpar(node->children[i], key, M);
    }
}
 
void insertimpar(Node** root, int key, int M) {
    Node* old_root = *root;
 
    if (old_root->num_keys == M - 1) {
        Node* new_root = create_node(M);
        *root = new_root;
        new_root->is_leaf = false;
        new_root->num_keys = 0;
        new_root->children[0] = old_root;
        split_childimpar(new_root, 0, M);
        insert_non_fullimpar(new_root, key, M);
    } else {
        insert_non_fullimpar(old_root, key, M);
    }
}
 
void insertpar(Node** root, int key, int M) {
    Node* old_root = *root;
 
    if (old_root->num_keys == M - 1) {
        Node* new_root = create_node(M);
        *root = new_root;
        new_root->is_leaf = false;
        new_root->num_keys = 0;
        new_root->children[0] = old_root;
        split_childpar(new_root, 0, M);
        insert_non_fullpar(new_root, key, M);
    } else {
        insert_non_fullpar(old_root, key, M);
    }
}
 
Node* search_key(Node* node, int key) {
    int i = 0;
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
 
    if (i < node->num_keys && key == node->keys[i]) {
        return node;
    }
 
    if (node->is_leaf) {
        return NULL;
    }
 
    return search_key(node->children[i], key);
}
 
int count_keys(Node* node) {
    int count = 0;
 
    if (!node)
        return 0;
 
    if (!node->is_leaf) {
        for (int i = 0; i < node->num_keys; i++) {
            count += count_keys(node->children[i]);
            count++;
        }
        count += count_keys(node->children[node->num_keys]);
    } else {
        count += node->num_keys;
    }
 
    return count;
}
 
void print_keys(Node* node) {
    if (!node)
        return;
 
    if (!node->is_leaf) {
        for (int i = 0; i < node->num_keys; i++) {
            print_keys(node->children[i]);
            printf("%d ", node->keys[i]);
        }
        print_keys(node->children[node->num_keys]);
    } else {
        for (int i = 0; i < node->num_keys; i++) {
            printf("%d ", node->keys[i]);
        }
    }
}
 
void print_tree(Node* node) {
    int i;
    for (i = 0; i < node->num_keys; i++) {
        if (!node->is_leaf) {
            print_tree(node->children[i]);
        }
        printf("%d ", node->keys[i]);
    }
 
    if (!node->is_leaf) {
        print_tree(node->children[i]);
    }
}
 
void free_tree(Node* node) {
    if (node == NULL) {
        return;
    }
 
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            free_tree(node->children[i]);
        }
    }
 
    free(node->keys);
    free(node->children);
    free(node);
}
 
int main() {
    int M, num, chave;
    scanf("%d", &M);
 
    Node* root = create_node(M);
 
    scanf("%d", &num);
 
    while (num != -1) {
        if (M % 2 == 1) {
            insertimpar(&root, num, M);
        } else {
            insertpar(&root, num, M);
        }
        scanf("%d", &num);
    }
    
    printf("%d\n", root->num_keys);
 
    scanf("%d", &chave);
 
    Node* result = search_key(root, chave);
    
    if (result != NULL) {
        int num_elements = count_keys(result);  // result é o nó retornado pela função search_key
        printf("%d\n", num_elements);
        print_keys(result);
        } else {
        printf("Valor nao encontrado\n");
    }
 
    free_tree(root);
 
    return 0;
}