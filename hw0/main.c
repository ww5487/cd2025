#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    char data;
    int count;
    struct Node *next;
} Node;


void insertOrUpdate(Node **head, char ch) {
    Node *temp = *head;
    while (temp) {
        if (temp->data == ch) {
            temp->count++;
            return;
        }
        temp = temp->next;
    }
    
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = ch;
    newNode->count = 1;
    newNode->next = *head;
    *head = newNode;
}

void freeList(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    FILE *file = fopen(__FILE__, "r");
    if (!file) return 1;
    
    Node *head = NULL;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            insertOrUpdate(&head, ch);
        }
    }
    fclose(file);
    
    for (Node *temp = head; temp; temp = temp->next) {
        printf("%c : %d\n", temp->data, temp->count);
    }
    
    freeList(head);
    return 0;
}
