#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

//la cual retorna el puntero del tipo de dato `List` con sus valores inicializados en NULL.
List * createList() {
    List* nueva=(List*) malloc (sizeof(List));
    nueva->head=NULL;
    nueva->tail=NULL;
    nueva->current=NULL;

     return nueva;
}

void * firstList(List * list) {
    if(list->head==NULL){
        return NULL;
    }
    else{
        list->current=list->head;
    }
    return list->head->data;
}

void * nextList(List * list) {
    if(list->current==NULL){
        return NULL;
    }
    if (list->current->next ==NULL)
    {
        return NULL;
    }
    else{

        list->current=list->current->next;

    }
    return list->current->data;
}


void * lastList(List * list) {
    if(list->tail !=NULL || list->head !=NULL){
        list->current= list->tail;
        
    }
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current!=NULL && list->current->prev != NULL )
    {
        list->current=list->current->prev;
        return list->current->data;
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node* nodo;
    nodo=createNode(data);
    if (list == NULL || list->head == NULL)

    {
        list->head=nodo;
        list->tail=nodo;
    }
    else
    {
       nodo->next=list->head;
       list->head->prev=nodo;
       list->head= nodo;
        list->head->prev = NULL;
    }
    
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * nodo = createNode(data);

   if(list->head != NULL && list->current != NULL && list->current != list->tail)
    {
        nodo->next=list->current->next;
        list->current->next->prev=nodo;
        list->current->next=nodo;
        nodo->prev=list->current;
        
    }
    else{
        list->current->next=nodo;
        nodo->prev=list->current;
        nodo->next=NULL;
        list->tail=nodo;
    }
}
void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node *aux;
    //aux = createNode(NULL);
    if(list == NULL) return NULL;
    if(list->head == NULL) return NULL;
    if(list->current == NULL) return NULL;
    if(list->current != list->tail && list->current != list->head)
    {
        aux=list->current;
        list->current->prev->next=list->current->next;
        list->current->next->prev=list->current->prev;
        free(list->current);
        return aux->data;
       
    }
    else{
        if(list->head != list->tail && list->current->next == NULL )
        {

            aux=list->current;
            list->tail=list->current->prev;
            list->current->prev->next=NULL;
            free(list->current);
            return aux->data;

        }
        else{
            if(list->current==list->head && list->current->next != NULL)
            {
                aux=list->current;
                list->head=list->current->next;
                list->head->prev=NULL;
                
                free(list->current);
                return aux->data;
            }
            else{
                list=NULL;
                return NULL;
            }
        }

    }
   return NULL;
}
    
    

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}