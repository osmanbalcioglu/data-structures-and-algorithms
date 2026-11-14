#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song *next;
    struct Song *prev;
} Song;

void addSongToEnd(Song **head, char *name) {
    Song *newSong = (Song *)malloc(sizeof(Song));

    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        return;
    }

    Song *temp = *head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->prev = temp;
}

void removeSong(Song **head, char *name) {
    Song *temp = *head;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                *head = temp->next;

            if (temp->next != NULL)
                temp->next->prev = temp->prev;

            free(temp);
            printf("Sarki silindi.\n");
            return;
        }

        temp = temp->next;
    }

    printf("Sarki bulunamadi.\n");
}

void playNext(Song **current) {
    if (*current == NULL) {
        printf("Calan sarki yok.\n");
        return;
    }

    if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Calinan sarki: %s\n", (*current)->name);
    } else {
        printf("Son sarkidasiniz.\n");
    }
}

void playPrevious(Song **current) {
    if (*current == NULL) {
        printf("Calan sarki yok.\n");
        return;
    }

    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Calinan sarki: %s\n", (*current)->name);
    } else {
        printf("Ilk sarkidasiniz.\n");
    }
}

void displayPlaylist(Song *head) {
    Song *temp = head;

    if (temp == NULL) {
        printf("Liste bos.\n");
        return;
    }

    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

void freeList(Song **head) {
    Song *temp;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    Song *head = NULL;
    Song *current = NULL;

    int secim;
    char name[50];

    while (1) {
        printf("\n");
        printf("1- Sarki ekle\n");
        printf("2- Sarki sil\n");
        printf("3- Sonraki sarki\n");
        printf("4- Onceki sarki\n");
        printf("5- Listeyi goster\n");
        printf("6- Cikis\n");
        printf("Secim: ");

        if (scanf("%d", &secim) != 1) {
            while (getchar() != '\n');
            printf("Gecersiz secim.\n");
            continue;
        }

        getchar();

        if (secim == 1) {
            printf("Sarki adi: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            if (strlen(name) == 0) {
                printf("Sarki adi bos olamaz.\n");
                continue;
            }

            addSongToEnd(&head, name);

            if (current == NULL)
                current = head;

            printf("Sarki eklendi.\n");
        }

        else if (secim == 2) {
            printf("Silinecek sarki: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            if (current != NULL && strcmp(current->name, name) == 0) {
                if (current->next != NULL)
                    current = current->next;
                else
                    current = current->prev;
            }

            removeSong(&head, name);

            if (head == NULL)
                current = NULL;
        }

        else if (secim == 3) {
            playNext(&current);
        }

        else if (secim == 4) {
            playPrevious(&current);
        }

        else if (secim == 5) {
            displayPlaylist(head);

            if (current != NULL)
                printf("Calan sarki: %s\n", current->name);
        }

        else if (secim == 6) {
            freeList(&head);
            break;
        }

        else {
            printf("Gecersiz secim.\n");
        }
    }

    return 0;
}

