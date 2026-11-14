#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* insert(Node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

int search(Node *root, int data) {
    if (root == NULL) {
        return 0;
    }

    if (root->data == data) {
        return 1;
    }

    if (data < root->data) {
        return search(root->left, data);
    }

    return search(root->right, data);
}

int findMin(Node *root) {
    while (root->left != NULL) {
        root = root->left;
    }

    return root->data;
}

void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *root = NULL;
    int values[] = {40, 20, 60, 10, 30, 50, 70};
    int n;
    int i;

    n = sizeof(values) / sizeof(values[0]);

    for (i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    if (search(root, 30)) {
        printf("30 agacta bulundu.\n");
    } else {
        printf("30 agacta bulunamadi.\n");
    }

    if (search(root, 90)) {
        printf("90 agacta bulundu.\n");
    } else {
        printf("90 agacta bulunamadi.\n");
    }

    printf("En kucuk eleman: %d\n", findMin(root));

    freeTree(root);

    return 0;
}
