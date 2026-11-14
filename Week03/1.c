#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void addOrdered(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    if (value <= (*head)->data) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;

    while (current->next != NULL &&
           current->next->data < value) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}


void removeNode(Node** head, int value) {
    if (*head == NULL) {
        return;
    }

    Node* temp;

    if ((*head)->data == value) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node* current = *head;

    while (current->next != NULL &&
           current->next->data != value) {
        current = current->next;
    }

    if (current->next != NULL) {
        temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}


int count(Node* head) {
    int counter = 0;

    while (head != NULL) {
        counter++;
        head = head->next;
    }

    return counter;
}


void printList(Node* head) {
    Node* current = head;

    while (current != NULL) {
        printf("%d", current->data);

        if (current->next != NULL) {
            printf(" -> ");
        }

        current = current->next;
    }

    printf("\n");
}


void clear(Node** head) {
    Node* temp;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}


int main() {
    Node* head = NULL;

    addOrdered(&head, 23);
    addOrdered(&head, 11);
    addOrdered(&head, 5);
    addOrdered(&head, 9);
    addOrdered(&head, 6);
    addOrdered(&head, 4);
    addOrdered(&head, 12);
    addOrdered(&head, 24);

    printf("Liste: ");
    printList(head);

    printf("Dugum sayisi: %d\n", count(head));

    removeNode(&head, 9);

    printf("9 silindikten sonra: ");
    printList(head);

    printf("Dugum sayisi: %d\n", count(head));

    clear(&head);

    printf("Clear sonrasi dugum sayisi: %d\n", count(head));

    return 0;
}

