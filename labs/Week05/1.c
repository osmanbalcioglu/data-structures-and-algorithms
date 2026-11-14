#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PatientNode {
    int id;
    char name[50];
    char status[20];
    struct PatientNode* next;
} PatientNode;

typedef struct Queue {
    PatientNode* front;
    PatientNode* rear;
} Queue;

typedef struct Stack {
    PatientNode* top;
} Stack;

typedef struct LinkedList {
    PatientNode* head;
} LinkedList;

PatientNode* createNode(int id, const char* name, const char* status) {
    PatientNode* newNode = (PatientNode*)malloc(sizeof(PatientNode));
    newNode->id = id;
    strcpy(newNode->name, name);
    strcpy(newNode->status, status);
    newNode->next = NULL;
    return newNode;
}

void enqueue(Queue* q, int id, const char* name) {
    PatientNode* newNode = createNode(id, name, "bekliyor");
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

PatientNode* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    PatientNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    temp->next = NULL;
    return temp;
}

void push(Stack* s, PatientNode* node) {
    if (node == NULL) return;
    strcpy(node->status, "muayenede");
    node->next = s->top;
    s->top = node;
}

PatientNode* pop(Stack* s) {
    if (s->top == NULL) {
        return NULL;
    }
    PatientNode* temp = s->top;
    s->top = s->top->next;
    temp->next = NULL;
    return temp;
}

void addHistory(LinkedList* list, PatientNode* node) {
    if (node == NULL) return;
    strcpy(node->status, "tamamlandi");
    node->next = NULL;
    
    if (list->head == NULL) {
        list->head = node;
        return;
    }
    PatientNode* temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

void printQueue(Queue* q) {
    printf("--- Bekleyen Hastalar ---\n");
    if (q->front == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    PatientNode* temp = q->front;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->name, temp->status);
        temp = temp->next;
    }
}

void printStack(Stack* s) {
    printf("--- Muayene Odasindaki Hastalar ---\n");
    if (s->top == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    PatientNode* temp = s->top;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->name, temp->status);
        temp = temp->next;
    }
}

void printHistory(LinkedList* list) {
    printf("--- Tamamlanan Hastalar ---\n");
    if (list->head == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    PatientNode* temp = list->head;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->name, temp->status);
        temp = temp->next;
    }
}

void printSystemState(const char* title, Queue* q, Stack* s, LinkedList* list) {
    printf("=== %s ===\n", title);
    printQueue(q);
    printStack(s);
    printHistory(list);
    printf("\n");
}

void freeQueue(Queue* q) {
    PatientNode* current = q->front;
    while (current != NULL) {
        PatientNode* temp = current;
        current = current->next;
        free(temp);
    }
    q->front = q->rear = NULL;
}

void freeStack(Stack* s) {
    PatientNode* current = s->top;
    while (current != NULL) {
        PatientNode* temp = current;
        current = current->next;
        free(temp);
    }
    s->top = NULL;
}

void freeLinkedList(LinkedList* list) {
    PatientNode* current = list->head;
    while (current != NULL) {
        PatientNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

int main() {
    Queue waitQueue = {NULL, NULL};
    Stack examStack = {NULL};
    LinkedList historyList = {NULL};

    enqueue(&waitQueue, 1, "Ahmet");
    enqueue(&waitQueue, 2, "Mehmet");
    enqueue(&waitQueue, 3, "Ayse");

    PatientNode* p1 = dequeue(&waitQueue);
    push(&examStack, p1);
    PatientNode* p1_done = pop(&examStack);
    addHistory(&historyList, p1_done);

    PatientNode* p2 = dequeue(&waitQueue);
    push(&examStack, p2);
    PatientNode* p2_done = pop(&examStack);
    addHistory(&historyList, p2_done);

    printSystemState("Tum Islemler Sonrasi", &waitQueue, &examStack, &historyList);

    freeQueue(&waitQueue);
    freeStack(&examStack);
    freeLinkedList(&historyList);

    return 0;
}