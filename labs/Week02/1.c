#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    struct Node* ilkDugum = (struct Node*)malloc(sizeof(struct Node));
    ilkDugum->data = 10;
    ilkDugum->next = NULL;
    
    printf("Dugumun Verisi: %d\n", ilkDugum->data);
    
    free(ilkDugum);
    return 0;
}