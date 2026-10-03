//
// Created by Furkan on 12/10/2023.
//
#include<stdio.h>
#include<stdlib.h>
#include "q.h"


typedef struct QueueRecord *Queue;
Queue CreateQueue()
{
    Queue q;

    q = (struct QueueRecord *) malloc(sizeof(struct QueueRecord));
    if (q == NULL)
        printf("Out of memory space\n");
    else
        MakeEmptyQueue(q);
    return q;
}

/*This function sets the queue size to 0, and creates a dummy element
and sets the front and rear point to this dummy element*/
void MakeEmptyQueue(Queue q)
{
    q->size = 0;
    q->front = (struct Node *) malloc(sizeof(struct Node));
    if (q->front == NULL)
        printf("Out of memory space\n");
    else{
        q->front->next = NULL;
        q->rear = q->front;
    }
}

/*Shows if the queue is empty*/
int IsEmptyQueue(Queue q)
{
    return (q->size == 0);
}


/*Returns the queue size*/
int QueueSize(Queue q)
{
    return (q->size);
}

/*Returns the value stored in the front of the queue*/
int FrontOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->front->next->task;
    else
    {
        printf("The queue is empty\n");
        return -1;
    }
}

/*Returns the value stored in the rear of the queue*/
int RearOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->rear->task;
    else
    {
        printf("The queue is empty\n");
        return -1;
    }
}
void InsertWithPriority(Queue q, struct Node* t) {
    struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
    tmp->priority = t->priority;
    tmp->task = t->task;
    tmp->arrival_time = t->arrival_time;
    tmp->service_time = t->service_time;
    tmp->next = NULL;

    struct Node *search = q->front;

    while (search->next != NULL && search->next->priority > tmp->priority) {
        search = search->next;
    }
    if(search->next==NULL){
        q->rear=tmp;
    }

    tmp->next = search->next;
    search->next = tmp;
    q->size++;
}
void Dequeue(Queue q)
{
    struct node *temp = q->front->next;
    q->front->next=q->front->next->next;
    if(q->front==NULL){
        q->rear==NULL;
    }
    free(temp);
}
void DeleteWithPriority(Queue q,int pri){
    struct Node* tail = q->front->next;
    while (tail->next!=NULL){
        struct Node* tmp = (struct Node*)malloc(sizeof (struct Node*));
        if(tail->next->priority==pri){
            tmp = tail->next;
            tail->next=tail->next->next;
            free(tmp);
            q->size--;
        }
        else{
            tail=tail->next;}
    }
}
/*Displays the content of the queue*/
void DisplayQueue(Queue q)
{
    struct Node *pos;

    pos=q->front->next;
    printf("Queue content:\n");

    printf("-->Priority   Value\n");
    while (pos != NULL)
    {
        printf("--> task = %c\t   priorty = %d\t service time = %d\t arival time=%d\n",pos->task, pos->priority, pos->service_time, pos->arrival_time);
        pos = pos->next;
    }
}