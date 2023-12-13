#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node definition
struct node {
    int data;
    struct node *next;
};

// Add element to the stack
void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// Remove and return element from the stack
int pop(struct node **top) {
    if (*top == NULL) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *top;
    int data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

// Print the stack
void printStack(struct node *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
}

int main() {
    struct node *top = NULL;
    int input;

    while (1) {
        printf("Enter a number: ");
        if (scanf("%d", &input) == 1) {
            // If a number is entered
            push(&top, input);
        } else {
            // If a value other than a number is entered
            printf("print stack\n");
            printStack(top);
            break;
        }
    }

    // Clean up the remaining elements in the stack
    while (top != NULL) {
        pop(&top);
    }

    return 0;
}

