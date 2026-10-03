//
// Created by Furkan on 1/1/2024.
//

#ifndef FISHDOMANALYSIS_C_AVLTREE_H
#define FISHDOMANALYSIS_C_AVLTREE_H
struct avl;

int Max(int, int);
int Height(struct avl *root);
struct avl *SingleRotateWithLeft(struct avl *k1);
struct avl *SingleRotateWithRight(struct avl *k2);
struct avl *DoubleRotateWithRight(struct avl *k3);
struct avl *DoubleRotateWithLeft(struct avl *k3);
#endif //FISHDOMANALYSIS_C_AVLTREE_H
