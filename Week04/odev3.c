#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char fileName[50];
    struct PrintJob *next;
} PrintJob;

typedef struct Queue {
    PrintJob *front;
    PrintJob *rear;
} Queue;

void enqueuePrintJob(Queue *q, char *fileName) {
    PrintJob *newJob = (PrintJob *)malloc(sizeof(PrintJob));

    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    if (q->rear == NULL) {
        q->front = newJob;
        q->rear = newJob;
    } else {
        q->rear->next = newJob;
        q->rear = newJob;
    }

    printf("%s yazdirma kuyruguna eklendi.\n", fileName);
}

void processNextJob(Queue *q) {
    if (q->front == NULL) {
        printf("Yazdirma kuyrugu bos.\n");
        return;
    }

    PrintJob *temp = q->front;

    printf("%s yazdiriliyor...\n", temp->fileName);

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}

void showQueue(Queue *q) {
    if (q->front == NULL) {
        printf("Yazdirma kuyrugu bos.\n");
        return;
    }

    PrintJob *temp = q->front;

    printf("Yazdirma kuyrugu: ");

    while (temp != NULL) {
        printf("%s", temp->fileName);

        if (temp->next != NULL)
            printf(" -> ");

        temp = temp->next;
    }

    printf("\n");
}

void freeQueue(Queue *q) {
    while (q->front != NULL) {
        PrintJob *temp = q->front;
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
    char fileName[50];

    while (1) {
        printf("\n");
        printf("1- Yeni dosya ekle\n");
        printf("2- Yazdir\n");
        printf("3- Kuyrugu goster\n");
        printf("4- Cikis\n");
        printf("Secim: ");

        if (scanf("%d", &secim) != 1) {
            while (getchar() != '\n');
            printf("Gecersiz secim.\n");
            continue;
        }

        getchar();

        if (secim == 1) {
            printf("Dosya adi: ");

            fgets(fileName, sizeof(fileName), stdin);
            fileName[strcspn(fileName, "\n")] = '\0';

            if (strlen(fileName) == 0) {
                printf("Dosya adi bos olamaz.\n");
                continue;
            }

            enqueuePrintJob(&q, fileName);
        }

        else if (secim == 2) {
            processNextJob(&q);
        }

        else if (secim == 3) {
            showQueue(&q);
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

