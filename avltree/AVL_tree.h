/*************************************************************************
	> File Name: AVL_tree.h
	> Author: CCTV-1
	> Created Time: 2015年05月07日 星期四 19时17分44秒
 ************************************************************************/

#ifndef _AVL_TREE_H
#define _AVL_TREE_H

typedef int ElementType;
typedef struct AvlNode * Avl_position;

struct AvlNode
{
    ElementType Element;
    int height;
    Avl_position left;
    Avl_position right;
};

Avl_position CreateTree ( void );

Avl_position MakeEmpty ( Avl_position T );

Avl_position Find ( ElementType x , Avl_position T );

Avl_position FindMax ( Avl_position T );

Avl_position FindMin ( Avl_position T );

Avl_position InsertTree ( ElementType x , Avl_position T );

Avl_position DeleteTree ( ElementType X , Avl_position T );

void PrintTree ( Avl_position T );

ElementType Retrieve ( Avl_position T );

#endif
