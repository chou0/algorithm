#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#ifdef __Cplusplus
extern .C{
#endif

typedef struct AVLTree
{
    unsigned int id;            /*存储数据*/
    int height;                 /*树的平衡度*/
    
    struct AVLTree *left;       /*指向左子树*/
    struct AVLTree *right;      /*指向右子树*/
} AVL;

#ifdef __Cplusplus
}
#endif

#endif