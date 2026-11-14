#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int musteriNumarasi;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

void enqueue(Queue *q, int musteriNumarasi) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->musteriNumarasi = musteriNumarasi;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    printf("Musteri #%d geldi.\n", musteriNumarasi);
}

void dequeue(Queue *q) {
    if (q->front == NULL) {
        printf("Kuyruk bos.\n");
        return;
    }

    Node *temp = q->front;

    printf("Musteri #%d islemi tamamladi.\n", temp->musteriNumarasi);

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}

void display(Queue *q) {
    if (q->front == NULL) {
        printf("Kuyruk bos.\n");
        return;
    }

    Node *temp = q->front;

    printf("Siradaki musteriler: ");

    while (temp != NULL) {
        printf("#%d ", temp->musteriNumarasi);
        temp = temp->next;
    }

    printf("\n");
}

void freeQueue(Queue *q) {
    while (q->front != NULL) {
        Node *temp = q->front;
        q->front = q->front->next;
        free(temp);
    }

    q->rear = NULL;
}

int main() {
    Queue q;

    q.front = NULL;
    q.rear = NULL;

    int secim;
    int musteriNumarasi = 1;

    while (1) {
        printf("\n");
        printf("1- Musteri geldi\n");
        printf("2- Islem tamamlandi\n");
        printf("3- Kuyrugu goster\n");
        printf("4- Cikis\n");
        printf("Secim: ");

        if (scanf("%d", &secim) != 1) {
            while (getchar() != '\n');
            printf("Gecersiz secim.\n");
            continue;
        }

        if (secim == 1) {
            enqueue(&q, musteriNumarasi);
            musteriNumarasi++;
        }

        else if (secim == 2) {
            dequeue(&q);
        }

        else if (secim == 3) {
            display(&q);
        }

        else if (secim == 4) {
            freeQueue(&q);
            printf("Program sonlandirildi.\n");
            break;
        }

        else {
            printf("Gecersiz secim.\n");
        }
    }

    return 0;
}

