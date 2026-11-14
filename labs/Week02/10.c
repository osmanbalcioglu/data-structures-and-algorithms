#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node3 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node4 = (struct Node*)malloc(sizeof(struct Node));
    
    head->data = 10;
    head->next = node2;
    
    node2->data = 20;
    node2->next = node3;
    
    node3->data = 30;
    node3->next = node4;
    
    node4->data = 40;
    node4->next = NULL;
    
    int silinecek;
    printf("Silinmesini istediginiz degeri giriniz: ");
    scanf("%d", &silinecek);
    
    struct Node* current = head;
    struct Node* previous = NULL;
    
    if (current != NULL && current->data == silinecek) {
        head = current->next;
        free(current);
    } else {
        while (current != NULL && current->data != silinecek) {
            previous = current;
            current = current->next;
        }
        if (current != NULL) {
            previous->next = current->next;
            free(current);
        }
    }
    
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    
    while (head != NULL) {
        struct Node* nextNode = head->next;
        free(head);
        head = nextNode;
    }
    return 0;
}