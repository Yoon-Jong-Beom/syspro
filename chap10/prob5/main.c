#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node definition
struct node {
    int data;
    struct node *next;
};

// Enqueue (add to the queue)
void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*tail == NULL) {
        // Empty queue
        *head = *tail = newNode;
    } else {
        // Non-empty queue
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

// Dequeue (delete from the queue)
int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *head;
    int data = temp->data;

    if (*head == *tail) {
        // Last element in the queue
        *head = *tail = NULL;
    } else {
        // More than one element in the queue
        *head = temp->next;
    }

    free(temp);
    return data;
}

// Print the queue
void printQueue(struct node *head) {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }

    while (head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int input;

    while (1) {
        printf("Enter a number: ");
        if (scanf("%d", &input) == 1) {
            // If a number is entered
            addq(&head, &tail, input);
        } else {
            // If a value other than a number is entered
            printf("print queue\n");
            printQueue(head);
            break;
        }
    }

    // Clean up the remaining elements in the queue
    while (head != NULL) {
        delete(&head, &tail);
    }

    return 0;
}

