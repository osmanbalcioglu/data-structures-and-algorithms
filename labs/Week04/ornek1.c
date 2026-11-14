#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int numara;
    char isim[50];
    struct Node *next;
    struct Node *prev;
} Node;

void insertOrdered(Node **head, int numara, char *isim) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->numara = numara;
    strcpy(newNode->isim, isim);
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    if (numara < (*head)->numara) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
        return;
    }

    Node *current = *head;

    while (current->next != NULL && current->next->numara < numara) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL) {
        current->next->prev = newNode;
    }

    current->next = newNode;
}

void displayForward(Node *head) {
    Node *current = head;

    if (current == NULL) {
        printf("Liste bos.\n");
        return;
    }

    while (current != NULL) {
        printf("Numara: %d, Isim: %s\n", current->numara, current->isim);
        current = current->next;
    }
}

void displayBackward(Node *head) {
    Node *current = head;

    if (current == NULL) {
        printf("Liste bos.\n");
        return;
    }

    while (current->next != NULL) {
        current = current->next;
    }

    while (current != NULL) {
        printf("Numara: %d, Isim: %s\n", current->numara, current->isim);
        current = current->prev;
    }
}

void freeList(Node **head) {
    Node *current = *head;
    Node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL;
}

int main() {
    Node *head = NULL;
    int secim;
    int numara;
    char isim[50];

    do {
        printf("\n1- Ogrenci ekle\n");
        printf("2- Bastan sona yazdir\n");
        printf("3- Sondan basa yazdir\n");
        printf("4- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("Numara: ");
                scanf("%d", &numara);

                printf("Isim: ");
                scanf(" %49[^\n]", isim);

                insertOrdered(&head, numara, isim);
                break;

            case 2:
                displayForward(head);
                break;

            case 3:
                displayBackward(head);
                break;

            case 4:
                freeList(&head);
                printf("Program sonlandirildi.\n");
                break;

            default:
                printf("Gecersiz secim.\n");
        }

    } while (secim != 4);

    return 0;
}

