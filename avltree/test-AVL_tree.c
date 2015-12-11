/*************************************************************************
	> File Name: test-AVL_tree.c
	> Author: CCTV-1
	> Created Time: 2015年05月10日 星期日 20时31分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "AVL_tree.h"

int main ( void )
{
    Avl_position T = NULL;
    srand( ( unsigned int )time( NULL ) );
    for( int i = 0 ; i < 10 ; i++ )
        T = InsertTree(  rand()%50 , T );
    PrintTree( T );
    printf( "\n" );
    return EXIT_SUCCESS;
}

