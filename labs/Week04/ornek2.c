#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

void push(Node **top, char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

char pop(Node **top) {
    if (*top == NULL)
        return '\0';

    Node *temp = *top;
    char data = temp->data;

    *top = temp->next;
    free(temp);

    return data;
}

int isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int checkBalance(char *expression) {
    Node *top = NULL;
    int i;

    for (i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' ||
            expression[i] == '{' ||
            expression[i] == '[') {
            push(&top, expression[i]);
        }
        else if (expression[i] == ')' ||
                 expression[i] == '}' ||
                 expression[i] == ']') {

            char open = pop(&top);

            if (open == '\0' || !isMatching(open, expression[i])) {
                while (top != NULL)
                    pop(&top);

                return 0;
            }
        }
    }

    if (top == NULL)
        return 1;

    while (top != NULL)
        pop(&top);

    return 0;
}

int main() {
    char expression[100];

    printf("Ifade: ");
    scanf(" %99[^\n]", expression);

    if (checkBalance(expression))
        printf("Sonuc: Parantezler dengede!\n");
    else
        printf("Sonuc: Parantezler dengede degil!\n");

    return 0;
}

