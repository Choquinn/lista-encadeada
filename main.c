#include <stdio.h>
#include <stdlib.h>

typedef struct Nodule {
    int value;
    struct Nodule *next; 
} Nodule;

Nodule* createNodule(int value) {
    Nodule *new = malloc(sizeof(Nodule));
    if (new == NULL) return NULL;
    new->value = value;
    new->next = NULL;

    return new;
}

int emptyList(Nodule *list) {
    return list == NULL;
}

void insertFirst(Nodule **list, int value) { 
    Nodule *new = createNodule(value);
    if (new == NULL) return;

    new->next = *list;
    *list = new;
}

void insertLast(Nodule **list, int value) {
    Nodule *new = createNodule(value);

    if (new == NULL) return;
    if (*list == NULL) {
        *list = new;
        return;
    } 

    Nodule *actual = *list;

    while (actual->next != NULL) {
        actual = actual->next;
    }

    actual->next = new;
}

void printList(Nodule *list) {
    Nodule *actual = list;
    while (actual != NULL) {
        printf("%d", actual->value);

        if (actual->next != NULL) printf(" -> ");
        actual = actual->next;
    }
    printf(" -> NULL\n");
}

int listSize(Nodule *list) {
    int count = 0;
    Nodule *actual = list;

    while (actual != NULL) {
        count++;
        actual = actual->next;
    }

    return count;
}

Nodule* search(Nodule *list, int value) {
    Nodule *actual = list;

    while (actual != NULL) {
        if (actual->value == value) return actual;
        actual = actual->next; 
    }

    return NULL;
}

void removeFirst(Nodule **list) {
    if (*list == NULL) return;
    Nodule *removed = *list;
    *list = removed->next;
    free(removed);
}

void removeLast(Nodule **list) {
    if (*list == NULL) return;
    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
        return;
    }

    Nodule *actual = *list;

    while (actual->next->next != NULL) actual = actual->next;

    free(actual->next);
    actual->next = NULL;
}

int removeValue(Nodule **list, int value) {
    if (*list == NULL) return 0;

    Nodule *actual = *list;
    if (actual->value == value) {
        *list = actual->next;
        free(actual);
        return 1;
    }

    while (actual->next != NULL && actual->next->value != value) actual = actual->next;
    
    if (actual->next == NULL) return 0;

    Nodule *removed = actual->next;
    actual->next = removed->next;
    free(removed);
    return 1;
}

void insertPos(Nodule **list, int value, int position) {
    if (position < 0) return;

    Nodule *new = createNodule(value);

    if (new == NULL) return;

    if (position == 0) {
        new->next = *list;
        *list = new;
        return;
    }

    Nodule *actual = *list;
    int i = 0;

    while (i < position - 1 && actual != NULL) {
        actual = actual->next;
        i++;
    }

    if (actual == NULL) {
        free(new);
        return;
    }

    new->next = actual->next;
    actual->next = new;
}

void cleanList(Nodule **list) {
    Nodule *actual = *list;

    while (actual != NULL) {
        Nodule *next = actual->next;
        free(actual);
        actual = next;
    }

    *list = NULL;
}

int main() {
    Nodule *list = NULL;
    Nodule *found = NULL;

    printf("1.Lista inicialmente vazia: %d\n", emptyList(list));
    list = createNodule(10);

    printf("\n2.Criar nó:\n");
    printList(list);
    insertFirst(&list, 5);

    printf("\n3.Inserir no início:\n");
    printList(list);
    insertLast(&list, 20);

    printf("\n4.Inserir no final:\n");
    printList(list);

    printf("\n5.Tamanho: %d\n", listSize(list));

    found = search(list, 10);
    if (found != NULL) printf("\n7.Valor encontrado: %d\n", found->value);
    else printf("\n7.Valor não encontrado");

    removeLast(&list);
    printf("\n9.Remover do final:\n");
    printList(list);

    insertLast(&list, 20);
    insertLast(&list, 30);
    insertLast(&list, 40);

    int hasRemoved = removeValue(&list, 30);

    printf("\n10.Remover valor 30: %d\n", hasRemoved);
    printList(list);

    insertPos(&list, 25, 1);
    printf("\n11.Inserir 25 na posição 1:\n");
    printList(list);

    cleanList(&list);
    printf("\n12.Lista limpa:\n");
    printList(list);

    return 0;
}