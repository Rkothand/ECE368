#include "shell_list.h"
#include "shell_array.h"
#include "list_of_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
Node *List_Load_From_File(char *filename)
{

    FILE *fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {

        return NULL;
    }
    else
    {
                
        Node *node;
        Node *head;
        Node *prev = NULL;
        node = (Node *)malloc(sizeof(Node));
        while (fread(node, sizeof(Node), 1, fptr))
        {
            if (prev != NULL)
            {
                prev->next = node;
                node->next = NULL;
            }
            else
            {
                head = node;
                node->next = NULL;
            }
            prev = node;
            node = (Node *)malloc(sizeof(Node));
        }
        fclose(fptr);
        return head;
    }
}

int List_Save_To_File(char *filename, Node *list)
{
    
    FILE *fptr = fopen(filename, "wb");
    int saveCount = 0;
    if (fptr == NULL  || list == NULL)
    {
        fclose(fptr);
        return saveCount;
    }
    else
    {
        Node * node=list;
        
        while(node!=NULL){            
            fwrite(node,sizeof(Node),1,fptr);
            node=node->next;
            saveCount++;
        }
        
    }
    fclose(fptr);
    return saveCount;
}

Node *List_Shellsort(Node *list, long *n_comp)
{
    return NULL;
}