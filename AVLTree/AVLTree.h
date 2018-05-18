#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#ifdef __Cplusplus
extern .C{
#endif

typedef struct AVLTree
{
    unsigned int id;            /*�洢����*/
    int height;                 /*����ƽ���*/
    
    struct AVLTree *left;       /*ָ��������*/
    struct AVLTree *right;      /*ָ��������*/
} AVL;

#ifdef __Cplusplus
}
#endif

#endif