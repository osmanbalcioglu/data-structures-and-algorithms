
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

void printTree(struct Node* root, int space);

struct Node* createNode(int data) {
    struct Node* newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int height(struct Node* root) {
    int leftHeight;
    int rightHeight;

    if (root == NULL)
        return 0;

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int balanceFactor(struct Node* root) {
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

struct Node* rotateLeft(struct Node* x) {
    struct Node* y;
    struct Node* T2;

    y = x->right;
    T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

struct Node* insertBST(struct Node* root, int data) {
    int bf;

    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertBST(root->left, data);

    else if (data > root->data)
        root->right = insertBST(root->right, data);

    else
        return root;

    bf = balanceFactor(root);

    if (bf < -1 && data > root->right->data) {
        printf("\nRotasyon oncesi:\n");
        printTree(root, 0);

        printf("\nRR dengesizligi olustu.\n");
        printf("Tek sola rotasyon uygulaniyor.\n");

        root = rotateLeft(root);

        printf("\nRotasyon sonrasi:\n");
        printTree(root, 0);
    }

    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void printTree(struct Node* root, int space) {
    int i;

    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    printf("\n");

    for (i = 5; i < space; i++)
        printf(" ");

    printf("%d\n", root->data);

    printTree(root->left, space);
}

int main() {
    struct Node* root = NULL;
    int numbers[3] = {10, 20, 30};
    int i;

    for (i = 0; i < 3; i++) {
        root = insertBST(root, numbers[i]);

        printf("\n%d eklendikten sonra kok denge faktoru: %d\n",
               numbers[i], balanceFactor(root));
    }

    printf("\nSon agacin Inorder dolasimi: ");
    inorder(root);

    printf("\nSon agacin Preorder dolasimi: ");
    preorder(root);

    printf("\n");

    return 0;
}

