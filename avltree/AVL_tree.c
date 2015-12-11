/*************************************************************************
	> File Name: AVL_tree.c
	> Author: CCTV-1
	> Created Time: 2015年05月07日 星期四 19时15分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "AVL_tree.h"

#define MAX( MAX_X , MAX_Y ) ( ( MAX_X ) > ( MAX_Y ) ? ( MAX_X ) : ( MAX_Y ) )

static int Height ( Avl_position T );

static Avl_position SingleRotateWithleft ( Avl_position K2 );

static Avl_position SingleRotateWithright ( Avl_position K1 );

static Avl_position DoubleRotateWithleft ( Avl_position K3 );

static Avl_position DoubleRotateWithright ( Avl_position K1 );

Avl_position CreateTree ( void )
{
    Avl_position T;
    if ( ( T = malloc( sizeof( struct AvlNode ) ) ) == NULL )
    {
        perror( "CreateTree:" );
        return T;
    }
    T -> left = NULL;
    T -> right = NULL;
    T -> height = 0;
    return T;
}

Avl_position MakeEmpty ( Avl_position T )
{
    if ( T != NULL )
    {
        MakeEmpty( T -> left );
        MakeEmpty( T -> right );
        free( T );
    }
    return T;
}

Avl_position Find ( ElementType x , Avl_position T )
{
    if ( T == NULL )
        return NULL;
    if ( T -> Element == x )
        return T;
    if ( T -> Element > x )
        return Find( x , T -> left );
    if ( T -> Element < x )
        return Find( x , T -> right );
    return T;
}

Avl_position FindMax ( Avl_position T )
{
    if ( T != NULL )
        while( T -> right != NULL )
            T = T -> right;
    return T;
}

Avl_position FindMin ( Avl_position T )
{
    if ( T != NULL )
        while( T -> left != NULL )
            T = T -> left;
    return T;
}

Avl_position InsertTree ( ElementType x , Avl_position T )
{
    if ( T == NULL )
    {
        //获得和返回一个树结点
        if ( ( T = malloc( sizeof( struct AvlNode ) ) ) == NULL )
        {
            perror( "CreateTree :" );
            return NULL;
        }
        else
        {
            T -> Element = x;
            T -> left = T -> right = NULL;
        }
    }
    //x在当前结点的左边
    else if ( T -> Element > x )
    {
        T -> left = InsertTree ( x , T -> left );
        if ( Height( T -> left ) - Height( T -> right ) == 2 )
        {
            //在左儿子的左子树插入，进行左单旋转
            if ( T -> left -> Element > x )
                T = SingleRotateWithleft( T );
            //在左儿子的右子树插入，进行左双旋转
            else
                T = DoubleRotateWithleft( T );
        }
    }
    //x在当前结点的右边
    else if ( T -> Element < x )
    {
        T -> right = InsertTree ( x , T -> right );
        if ( Height( T -> right ) - Height( T -> left ) == 2 )
        {
            //在右儿子的左子树插入，进行右单旋转
            if ( T -> right -> Element < x )
                T = SingleRotateWithright( T );
            //在右儿子的右子树插入,进行右双旋转
            else
                T = DoubleRotateWithright( T );
        }
    }
    //若x在树中已经存在，则向标准错误流写入一条警告信息
    else if ( T -> Element == x )
    {
        fprintf( stderr , "\033[31mwarning:Duplicate node :%d\033[0m\n" , x );
    }
        T -> height = MAX( Height( T -> left ) , Height( T -> right ) ) + 1;
    return T;
}

Avl_position DeleteTree ( ElementType X , Avl_position T )
{
    if( T == NULL )
        return NULL;//没有找到要删除的值,do nothing
    if( X < T -> Element )
    {
        T -> left = DeleteTree( X , T -> left );
        if( Height( T -> right ) - Height( T -> left ) == 2 )
        {
            //右子树比左子树高2,那么在删除操作之前右子树比左子树高1,
            //也就是说T的右子树必然不为空,甚至必然有非空子树(高度至少为1).
            Avl_position s = T -> right;
            if( Height( s -> left ) > Height( s -> right ) )
                T = DoubleRotateWithright(T);//右双旋转
            else
                T = SingleRotateWithright(T);//右单旋转
        }
        else
            //不需要调整就满足平衡条件的话,只需要重新计算其高度就好
            T -> height = MAX( Height( T -> left ) , Height( T -> right ) ) + 1;
    }
    else if( X > T -> Element )
    {

        T -> right = DeleteTree( X , T -> right );
        if ( Height( T -> left ) - Height( T -> right ) == 2 )
        {
            Avl_position s = T -> left;
            if( Height( s -> right ) > Height( s -> left ) )
                T = DoubleRotateWithleft( T );//左双旋转
            else
                T = SingleRotateWithleft( T );//左单旋转
        }
        else
            T -> height = MAX( Height( T -> left ) , Height ( T -> right ) ) + 1;
    }
    else
    {
        if( T -> left && T -> right )
            //T的左右子树都非空,把DeleteTree操作转移到只有一个非空子树的结点或者叶子结点上去
        {
            if( Height( T -> left ) > Height( T -> right ) )
                //把DeleteTree操作往更高的那颗子树上转移
            {
                //左子树中的最大值
                T -> Element = FindMax( T -> left ) -> Element;
                T -> left = DeleteTree( T -> Element , T -> left );
            }
            else
            {
                //右子树中的最小值
                T -> Element = FindMin( T -> right ) -> Element;
                T -> right = DeleteTree( T -> Element , T -> right );
            }
        }
        else
        {
            Avl_position oldnode = T;
            T = ( T -> left ) ? ( T -> left ) : ( T -> right );
            free( oldnode );
        }
    }
    return T;
}

void PrintTree ( Avl_position T )
{
    if ( T != NULL )
    {
        PrintTree( T -> left );
        printf( "%d " , T -> Element );
        PrintTree( T -> right );
    }
}

ElementType Retrieve ( Avl_position T )
{
    return T -> Element;
}

static int Height ( Avl_position T )
{
    if ( T == NULL )
        return -1;
    else
        return ( T -> height );
}

static Avl_position SingleRotateWithleft ( Avl_position K2 )
{
    Avl_position K1;

    K1 = K2 -> left;
    K2 -> left = K1 -> right;
    K1 -> right = K2;

    K2 -> height = MAX( Height( K2 -> left ) , Height( K2 -> right ) ) + 1;

    K1 -> height = MAX( Height( K1 -> left ) , Height( K1 -> right ) ) + 1;

    return K1;
}

static Avl_position SingleRotateWithright ( Avl_position K1 )
{
    Avl_position K2;

    K2 = K1 -> right;
    K1 -> right = K2 -> left;
    K2 -> left = K1;

    K1 -> height = MAX( Height( K1 -> left ) , Height( K1 -> right ) ) + 1;
    K2 -> height = MAX( Height( K2 -> left ) , Height( K2 -> right ) ) + 1;

    return K2;
}

static Avl_position DoubleRotateWithleft ( Avl_position K3 )
{
    K3 -> left = SingleRotateWithright( K3 -> left );
    return SingleRotateWithleft( K3 );
}

static Avl_position DoubleRotateWithright ( Avl_position K1 )
{
    K1 -> right = SingleRotateWithleft( K1 -> right );
    return SingleRotateWithright( K1 );
}

