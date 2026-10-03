#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avltree.h"
struct Node {
    char name[100];
    float length;
    char date[100];
    char city[100];
    struct Node* next;
};

struct avl {
    int weight;
    int height;
    struct Node* near;
    struct avl* left;
    struct avl* right;
};


struct avl*insertFish(int weight, char* name, char* date, char* city, float length, struct avl* root){
    int sameweight = 0;
    struct avl*search=root;
    while (search!=NULL){
        if(weight<search->weight){
            search =search->left;
        }
        else if(weight>search->weight){
            search= search->right;
        }
        else if(weight==search->weight){
            sameweight = 1;
            break;
        }
    }
    if(sameweight==1){
        struct Node* tmp2 = (struct Node*) malloc(sizeof (struct Node));
        if(tmp2==NULL){
            printf("Error");
            return NULL;
        }
        else{
            tmp2->length = length;
            strcpy(tmp2->name, name);
            strcpy(tmp2->date, date);
            strcpy(tmp2->city, city);
            tmp2->next = search->near;
            search->near = tmp2;

        }

    }

    if(sameweight==0){
        if(root==NULL){
            struct avl*tmp = (struct avl*) malloc(sizeof (struct avl));
            tmp->near=(struct Node*) malloc(sizeof (struct Node));
            if(tmp==NULL||tmp->near==NULL){
                printf("Error");
                return NULL;
            }
            else{
                tmp->weight=weight;
                tmp->near->length = length;
                strcpy(tmp->near->name, name);
                strcpy(tmp->near->date, date);
                strcpy(tmp->near->city, city);
                tmp->left = tmp->right = NULL;
                tmp->height = 0;
                root = tmp;
                tmp->near->next=NULL;
            }

        }
        else if(weight<root->weight){

            root->left = insertFish(weight, name, date, city, length, root->left);
            if(Height(root->left)- Height(root->right)==2){
                if(weight< root->left->weight){
                    root = SingleRotateWithRight(root);
                }
                else{
                    printf("\nc\n");
                    root = DoubleRotateWithRight(root);
                }
            }
        }
        else if(weight>root->weight){
            root->right = insertFish(weight, name, date, city, length, root->right);
            if(Height(root->right)- Height(root->left)==2){
                if(weight> root->right->weight){

                    root = SingleRotateWithLeft(root);
                }
                else{

                    root = DoubleRotateWithLeft(root);
                }
            }
        }
    }
    root->height = Max(Height(root->left), Height(root->right)) + 1;

    return root;
}
struct avl* readData(char* file){
    FILE* infile;
    infile = fopen(file,"r");
    if (infile == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    char  skip[100];
    char name[100], date[100], city[100];
    int weight;
    float length;
    struct avl* root = NULL;
    fscanf(infile, "%99s\n",  skip);// to skip first line
    while (fscanf(infile, "%99[^,],%d,%f,%99[^,],%99s\n", name, &weight, &length, date, city) != EOF) {
        root = insertFish(weight, name, date, city, length, root);
    }
    fclose(infile);
    return root;
}
void displayIndex(struct avl*root){
    if(root!=NULL) {
        displayIndex(root->left);

        struct Node* read = root->near;

        while (read!=NULL) {
            printf("\n%s, %d, %f, %s, %s\n", read->name,root->weight,read->length,read->date,read->city);
            read =read->next;
        }
        displayIndex(root->right);
    }
}
void heaviestFish(struct avl*root){

    if(root!=NULL){
        heaviestFish(root->right);
        if(root->right==NULL){
            struct Node* read = root->near;
            while (read!=NULL) {
                printf("\n%s, %d, %f, %s, %s\n", read->name,root->weight,read->length,read->date,read->city);
                read =read->next;
            }
        }
    }
//Because of the recursive function, it can control only one time nodes, so  complexity will be O(n)
}
void longestFish(struct avl* root) {



    if (root != NULL) {
        longestFish(root->right);
        longestFish(root->left);
        struct Node* read = root->near;
        struct avl* longest;
        struct Node* longest2 = NULL;
        while (read != NULL) {
            if (longest2 == NULL || longest2->length < read->length) {
                longest2 = read;
                longest = root;
            }
            read = read->next;

        }



        if(root->left==NULL&&root->right==NULL){
            printf("\n%s,%d, %f, %s, %s\n", longest2->name, longest->weight,longest2->length, longest2->date, longest2->city);
        }
    }


//we will check the right and left of all tree sides so complexity will be n^2. if will take avl based on the length we can take better complexity


}

int main(int argc,char *argv[]) {
    int choose,finsh=0;
    struct avl*mytree = readData(argv[1]);
    printf("********Welcome to Fishdom Analysis********\n");
    while (finsh==0){
        printf("*******************************************\n");
        printf("Menu\n1. Display the full index of fishdom\n2. Display the heaviest fishes\n3. Display the longest fishes\n4. Exit\n");
        printf("*******************************************\n");
        printf("Enter your option: ");
        scanf("%d",&choose);
        if(choose==1){
            printf("Enter your option: 1\n");
            displayIndex(mytree);
        }
        else if(choose==2){
            printf("Enter your option: 2\n");;
            heaviestFish(mytree);
        }
        else if(choose==3){
            printf("Enter your option: 3\n");
            longestFish(mytree);
        }
        else if(choose==4){
            printf("Enter your option: 4\nBye!");
            finsh=1;
        }
        else{
            printf("command not recognized\n");
        }
    }

    return 0;
}

