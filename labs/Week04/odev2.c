#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word *next;
} Word;

void pushWord(Word **top, char *text) {
    Word *newWord = (Word *)malloc(sizeof(Word));

    strcpy(newWord->text, text);
    newWord->next = *top;
    *top = newWord;
}

void popWord(Word **top) {
    if (*top == NULL) {
        printf("Geri alinacak metin yok.\n");
        return;
    }

    Word *temp = *top;

    *top = (*top)->next;

    free(temp);

    printf("Undo yapildi.\n");
}

void showWords(Word *top) {
    if (top == NULL) {
        printf("Liste bos.\n");
        return;
    }

    Word *temp = NULL;
    Word *current = top;

    while (current != NULL) {
        Word *newWord = (Word *)malloc(sizeof(Word));

        strcpy(newWord->text, current->text);
        newWord->next = temp;
        temp = newWord;

        current = current->next;
    }

    current = temp;

    while (current != NULL) {
        printf("%s ", current->text);
        current = current->next;
    }

    printf("\n");

    while (temp != NULL) {
        Word *deleteNode = temp;
        temp = temp->next;
        free(deleteNode);
    }
}

void freeStack(Word **top) {
    Word *temp;

    while (*top != NULL) {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

int main() {
    Word *top = NULL;

    int secim;
    char text[50];

    while (1) {
        printf("\n");
        printf("1- Add\n");
        printf("2- Undo\n");
        printf("3- Show\n");
        printf("4- Cikis\n");
        printf("Secim: ");

        if (scanf("%d", &secim) != 1) {
            while (getchar() != '\n');
            printf("Gecersiz secim.\n");
            continue;
        }

        getchar();

        if (secim == 1) {
            printf("Metin ekle: ");

            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0';

            if (strlen(text) == 0) {
                printf("Metin bos olamaz.\n");
                continue;
            }

            pushWord(&top, text);

            printf("Metin eklendi.\n");
        }

        else if (secim == 2) {
            popWord(&top);
        }

        else if (secim == 3) {
            printf("Metin: ");
            showWords(top);
        }

        else if (secim == 4) {
            freeStack(&top);
            printf("Program sonlandirildi.\n");
            break;
        }

        else {
            printf("Gecersiz secim.\n");
        }
    }

    return 0;
}

