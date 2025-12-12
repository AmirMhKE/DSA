#include <stdio.h>
#include <stdlib.h>
#include <linked_list.hpp>


Node *create(double data) {
    Node *new_node = (Node*) malloc(sizeof(Node));

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}


void print(Node *node) {
    if (node != NULL) {
        printf("%f ", node->data);
        print(node->next);
    }
}


void append(Node *node, double data) {
    Node *new_node = create(data);

    Node *temp = node;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
}
