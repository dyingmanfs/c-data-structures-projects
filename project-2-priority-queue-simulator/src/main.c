#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include "q.h"
void parseInput(int *task, int *developers, int *max_arrival, int *max_service, char *argv[]) {

    *task = 0;
    *developers = 0;
    *max_arrival = 0;
    *max_service = 0;

    if (argv[1] != NULL)
        *task = atoi(argv[1]);
    if (argv[2] != NULL)
        *developers = atoi(argv[2]);
    if (argv[3] != NULL)
        *max_arrival = atoi(argv[3]);
    if (argv[4] != NULL)
        *max_service = atoi(argv[4]);
}

struct Node* createTasksList(int tasks, int developers, int max_arrival, int max_service) {
    srand(time(NULL));

    struct Node* head = NULL;
    struct Node* tail = NULL;

    for (int i = 1; i <= tasks; ++i) {
        struct Node* task = (struct Node*)malloc(sizeof(struct Node));
        if (task == NULL) {
            printf("Memory allocation failed.\n");
            return NULL;
        }

        int rand_task = 1 + rand() % 4;
        if (rand_task == 1) {
            task->task = 'N';
            task->priority = 1;
        } else if (rand_task == 2) {
            task->task = 'M';
            task->priority = 2;
        } else if (rand_task == 3) {
            task->task = 'H';
            task->priority = 3;
        } else if (rand_task == 4) {
            task->task = 'C';
            task->priority = 4;
        } else {
            printf("Error\n");
        }

        task->arrival_time = 1 + rand() % max_arrival;
        task->service_time = 1 + rand() % max_service;
        task->Start_service_time =0;
        task->next = NULL;

        printf("Task = %c, Arrival = %d, Service = %d Start=%d\n", task->task, task->arrival_time, task->service_time,task->Start_service_time);

        if (head == NULL) {
            head = task;
            tail = task;
        } else {
            tail->next = task;
            tail = task;
            tail->next=NULL;
        }
    }
    // I used insertion Sort
    struct Node* ordered = NULL;
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        if (ordered == NULL || ordered->arrival_time >= current->arrival_time) {
            current->next = ordered;
            ordered = current;
        } else {
            struct Node* tmp1 = ordered;
            while (tmp1->next != NULL && tmp1->next->arrival_time < current->arrival_time) {
                tmp1 = tmp1->next;
            }
            current->next = tmp1->next;
            tmp1->next = current;
        }
        current = next;
    }
    head = ordered;

    printf("\nPrinting the tasks in the linked list:\n");
    struct Node
            * tmp = head;
    while (tmp != NULL) {
        printf("Task = %c, Arrival = %d, Service = %d Start= %d\n", tmp->task, tmp->arrival_time, tmp->service_time,tmp->Start_service_time);
        tmp = tmp->next;
    }
    return head;
}

void newTask(struct Node* list, Queue q) {
    while (list != NULL) {
        InsertWithPriority(q, list);
        printf("Task added to the queue: %c\n", list->task);
        list = list->next; // Move to the next task in the list
    }
    DisplayQueue(q); // Display the queue after adding all tasks
}



void initialiseSimulator(Queue *q, int developers, int **dev) {
    *q = CreateQueue();
    *dev = (int *)malloc(sizeof(int) * developers);
    for (int i = 0; i < developers; ++i) {
        (*dev)[i] = 1;
    }
}
void accomplishTask(Queue q){
    Dequeue(q);

}
void reportStatistics(int time,int tasks, int developers, struct Node*first){
    int Critical,High,Medium,Normal;
    printf("\n****************Report*****************\n");
    printf("\n*The number of Developers is: %d\n",developers);
    printf("*The number of Tasks: %d\n",tasks);
    printf("Number of Tasks for each Label:\n");
    while (first!=NULL){
        if(first->priority==1){
            Normal++;
        }
        if(first->priority==2){
            Medium++;
        }
        if(first->priority==3){
            High++;
        }
        if(first->priority==4){
            Critical++;
        }
        first = first->next;
    }
    printf(" Critical: %d \n High priority: %d \n Medium: %d\n Normal: %d\n",Critical,High,Medium,Normal);
    float Average= time/tasks;
    printf("Average time spent in the queue: %f\n",Average);
    printf("Maximum waiting time: \n",time);
}
int main(int argc, char *argv[]) {
    int task = 0, developers = 0, max_arrival = 0, max_service = 0;

    if (argc < 5) {
        printf("Insufficient arguments. Please provide task, developers, max_arrival, and max_service.\n");
        return 1;
    }

    parseInput(&task, &developers, &max_arrival, &max_service, argv);
    struct Node *tasklist = createTasksList(task, developers, max_arrival, max_service);
    struct Node *copylist = tasklist;
    Queue Myqueue;
    int *dev;
    initialiseSimulator(&Myqueue,developers, &dev);
    struct Node *currentTask = tasklist;
    newTask(currentTask, Myqueue);
    DisplayQueue(Myqueue);
    int time = 0;
    reportStatistics(time,task, developers,copylist);

    return 0;
}
