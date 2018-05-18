#include <stdio.h>
#include <stdlib.h>

#include "AVLTree.h"

static int Height(AVL *node)
{
    if (NULL == node)
    {
        return -1;
    }
    
    return node->height;
}

static int Max(int a, int b)
{
    return (a >= b)?a:b;
}

static AVL *LL(AVL *root)
{
    AVL *node = root->left;
    
    root->left = node->right; 
    root->height = Max(Height(root->left), Height(root->right)) + 1;
    
    node->right = root;
    node->height = Max(Height(node->left), Height(node->right)) + 1;
    
    return node;
}

static AVL *LR(AVL *root)
{
    AVL *node = root->left;
    
    root->left = node->right; 
    node->right = node->right->left;
    root->left->left = node;
    
    node->height = Max(Height(node->left), Height(node->right)) + 1;
    root->left->height = Max(Height(root->left->left), Height(root->left->right)) + 1;
    root->height = Max(Height(root->left), Height(root->right)) + 1;
    
    node = LL(root);
    return node;
}

static AVL *RR(AVL *root)
{
    AVL *node = root->right;
    
    root->right = node->left; 
    root->height = Max(Height(root->left), Height(root->right)) + 1;
    
    node->left = root;
    node->height = Max(Height(node->left), Height(node->right)) + 1;
    return node;
}

static AVL *RL(AVL *root)
{
    AVL *node = root->right;
    
    root->right = node->left; 
    node->left = node->left->right;
    root->right->right = node;
    
    node->height = Max(Height(node->left), Height(node->right)) + 1;
    root->left->height = Max(Height(root->left->left), Height(root->left->right)) + 1;
    root->height = Max(Height(root->left), Height(root->right)) + 1;
    
    node = RR(root); 
    return node;
}

AVL *Insert(AVL **root, int id, int *exist)
{
    AVL *item = NULL;
    int lh, rh;
        
    if (NULL == (*root))
    {
        *exist = 0;
        if (NULL == (item = malloc(sizeof(AVL))))
        {
            printf("malloc fail\n");
            return NULL;         
        }
        
        item->id = id;
        item->left = NULL;
        item->right = NULL;
        item->height = 0;
        
        *root = item;
    }
    else if (id == (*root)->id)
    {
        *exist = 1;  
        item = *root;  
    }
    else if (id > (*root)->id)
    {
        item = Insert(&((*root)->right), id, exist); 
        lh = Height((*root)->left);
        rh = Height((*root)->right);

        if ((rh - lh) >= 2)
        {
            lh = Height((*root)->right->left);
            rh = Height((*root)->right->right);    
            if (lh >= rh)
            {
                *root = RL(*root);    
            }
            else
            {
                *root = RR(*root); 
            }    
        }    
        
        (*root)->height = Max(Height((*root)->left), Height((*root)->right)) + 1; 
    }
    else if (id < (*root)->id)
    {
        item = Insert(&((*root)->left), id, exist);
        lh = Height((*root)->left);
        rh = Height((*root)->right);

        if ((lh - rh) >= 2)
        {
            lh = Height((*root)->left->left);
            rh = Height((*root)->left->right);    
            if (lh >= rh)
            {
                *root = LL(*root);    
            }
            else
            {
                *root = LR(*root); 
            }    
        }
        
        (*root)->height = Max(Height((*root)->left), Height((*root)->right)) + 1;
    }
    
    return item;   
}

int dump(AVL *root)
{
    if (root)
    {
        printf("id: %d\n", root->id);
        dump(root->left); 
        dump(root->right); 
    }
     
    return 0;
}

int main(int argc, char **args)
{
    AVL *root = NULL, *item;
    unsigned int a[] = {11, 23, 434, 54, 65, 44, 55, 63, 22, 43, 90, 2};
    int i, exist = 0;
    
    for (i = 0; i < sizeof(a)/sizeof(int); i++)
    {
        item = Insert(&root, a[i], &exist);
        printf("%d\n", item->id);
    }
    
    //printf("----------------\n");
    //dump(root);
    return 0;
}