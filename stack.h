#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int position;
    int previous;
    struct node *next; 
} *stack_t;

stack_t init_stack(){
    stack_t stack = NULL;
    return stack;
}

stack_t stack_pop(stack_t stack){
    if (stack == NULL){
        printf("Stos pusty\n");
        return NULL;
    }
    stack_t temp_node = stack;
    stack = stack->next;
    free(temp_node);
    return stack;
}
void free_stack(stack_t stack) {
    stack_t current = stack;
    stack_t next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int stack_head(stack_t stack){
    if (stack == NULL){
        return -1;
    }
    return stack->position;
}

stack_t put_on_back(int value, int previous, stack_t stack){
    stack_t new = malloc(sizeof(struct node));
    if (new == NULL) {
        printf("Błąd alokacji pamięci.\n");
        exit(1);
    }
    new->position = value;
    new->next = NULL;
    new->previous = previous;

    if (stack == NULL) {
        return new;
    }

    stack_t current = stack;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;
    return stack;
}
