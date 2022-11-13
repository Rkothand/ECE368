#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hbt.h"
int Is_empty(Tnode *bt_ptr)
{
    return (bt_ptr == NULL);
}
Tnode *Create(int data,
              Tnode *left_ptr, Tnode *right_ptr)
{
    Tnode *new_node = malloc(sizeof(*new_node));
    if (new_node != NULL)
    {
        new_node->key = data;
        new_node->left = left_ptr;
        new_node->right = right_ptr;
    }
    return new_node;
}
int Data(Tnode *bt_ptr) // bt_ptr not NULL
{
    return (bt_ptr->key);
}

Tnode *Left_Child(Tnode *bt_ptr) // bt_ptr not NULL
{
    return bt_ptr->left;
}
Tnode *Right_Child(Tnode *bt_ptr) // bt_ptr not NULL
{
    return bt_ptr->right;
}
void BT_Delete(Tnode *bt_ptr)
{
    if (bt_ptr != NULL)
    {
        BT_Delete(bt_ptr->left);
        BT_Delete(bt_ptr->right);
        free(bt_ptr);
    }
}
