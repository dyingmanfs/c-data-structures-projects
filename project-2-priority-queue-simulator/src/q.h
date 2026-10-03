//
// Created by Furkan on 12/10/2023.
//

#ifndef UNTITLED73_Q_H
#define UNTITLED73_Q_H
struct Node
{
    char task;
    int priority;
    int service_time;
    int arrival_time;
    int Start_service_time;
    struct Node* next;
};
struct QueueRecord
{
    struct Node *front;   /* pointer to front of queue */
    struct Node *rear;    /* pointer to rear of queue */
    int size;             /* number of items in queue */
};

typedef struct QueueRecord * Queue;
void DeleteWithPriority(Queue,int);
void InsertWithPriority(Queue,struct Node*);
Queue CreateQueue();
void MakeEmptyQueue(Queue);
int QueueSize(Queue);
int FrontOfQueue(Queue);
int RearOfQueue(Queue);
void Dequeue(Queue);
int IsEmptyQueue(Queue);
void DisplayQueue(Queue);
#endif //UNTITLED73_Q_H
