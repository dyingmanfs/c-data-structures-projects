//
// Created by Furkan on 1/1/2024.
//
#include <stdio.h>
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
int Max(int x,int y){
    if(x>=y){
        return x;
    }
    else{
        return y;
    }
}
int Height(struct avl *root){
    if(root==NULL){
        return -1;
    }
    else{
        return root->height;
    }

}
struct avl *SingleRotateWithLeft(struct avl * k1)
{
    struct avl * k2;
    k2=k1->right;
    k1->right=k2->left;
    k2->left=k1;
    k1->height = Max(Height(k1->left), Height(k1->right))+1;
    k2->height = Max(Height(k2->right), k1->height) + 1;
    return k2;
}
struct avl * SingleRotateWithRight(struct avl * k2)
{

    struct avl * k1;
    k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    k2->height = Max(Height(k2->left), Height(k2->right))+1;
    k1->height = Max(Height(k1->left), k2->height)+1;
    return k2;
}
struct avl * DoubleRotateWithRight(struct avl * k3)
{

    k3->left = SingleRotateWithLeft(k3->left);

    return SingleRotateWithRight(k3);
}
struct avl *  DoubleRotateWithLeft(struct avl *  k3)
{
    k3->right = SingleRotateWithRight(k3->right);
    return SingleRotateWithLeft(k3);
}