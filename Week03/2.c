#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

void insertAt(Node** head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (*head == NULL || position <= 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    int index = 0;

    while (current->next != NULL && index < position - 1) {
        current = current->next;
        index++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void deleteAt(Node** head, int position) {
    if (*head == NULL || position < 0) {
        return;
    }

    Node* temp = *head;

    if (position == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    Node* previous = NULL;
    int index = 0;

    while (temp != NULL && index < position) {
        previous = temp;
        temp = temp->next;
        index++;
    }

    if (temp == NULL) {
        return;
    }

    previous->next = temp->next;
    free(temp);
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}

void clear(Node** head) {
    Node* current = *head;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL;
}

int main() {
    Node* head = NULL;

    insertAt(&head, 10, 0);
    insertAt(&head, 30, 1);
    insertAt(&head, 20, 1);
    insertAt(&head, 5, -2);
    insertAt(&head, 40, 100);

    printf("Liste: ");
    printList(head);

    deleteAt(&head, 0);
    deleteAt(&head, 2);

    printf("Silme sonrasi: ");
    printList(head);

    clear(&head);

    return 0;
}