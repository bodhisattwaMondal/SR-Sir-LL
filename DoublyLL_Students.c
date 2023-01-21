#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int element;
    struct Node *prevNode;
    struct Node *nxtNode;
};

// ---------------- Insertion ----------------
void insertNode(struct Node **head, int roll)
{
    // in the 1st run create ref node
    if (*head == NULL)
    {
        struct Node *ref = (struct Node *)malloc(sizeof(struct Node));
        ref->element = 0; // it will keep track of no. of nodes in the ll
        ref->prevNode = NULL;
        ref->nxtNode = NULL;
        *head = ref; // assigning ref as head
    }

    // Creating new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->element = roll;

    // linking newNode to the ll and updating ref
    if ((*head)->prevNode == NULL) // or (*head)->nxtNode == NULL
    {                              // if no node is present under ref (in 1st run)
        // ref->prev and ref->next both will point to the newNode
        newNode->prevNode = NULL;
        newNode->nxtNode = NULL;
        (*head)->prevNode = newNode;
        (*head)->nxtNode = newNode;
        (*head)->element++; // incrementing node count of ref
    }
    else
    { // newNode will be inserted in sorted order

        // inserting newNode at front
        // updating ref->prev to newNode
        if (roll <= (*head)->prevNode->element)
        {
            newNode->prevNode = NULL;
            newNode->nxtNode = (*head)->prevNode;
            ((*head)->prevNode)->prevNode = newNode;
            (*head)->prevNode = newNode;
            (*head)->element++; // incrementing node count of ref
        }

        // inserting newNode at end
        // updating ref->next to newNode
        else if (roll >= (*head)->nxtNode->element)
        {
            newNode->nxtNode = NULL;
            newNode->prevNode = (*head)->nxtNode;
            ((*head)->nxtNode)->nxtNode = newNode;
            (*head)->nxtNode = newNode;
            (*head)->element++; // incrementing node count of ref
        }
        else
        {
            // traverse the ll until the right pos found
            struct Node *tempNode = (*head)->prevNode;
            while (tempNode->nxtNode != NULL)
            {
                if (roll <= tempNode->nxtNode->element)
                {
                    newNode->prevNode = tempNode;
                    newNode->nxtNode = tempNode->nxtNode;
                    (tempNode->nxtNode)->prevNode = newNode;
                    tempNode->nxtNode = newNode;
                    (*head)->element++; // incrementing node count of ref
                    return;
                }
                tempNode = tempNode->nxtNode;
            }
        }
    }
}

// ---------------- Deletion ----------------
void dltNode(struct Node **head, int roll)
{
    if (*head == NULL)
    {
        printf("Can't Dlt - Empty List !!");
        return;
    }
    // if only one node is present under ref & it's roll matches
    // ref->prev and ref->next = NULL
    else if ((*head)->prevNode->element == roll && (*head)->nxtNode->element == roll)
    {
        free((*head)->prevNode);
        (*head)->prevNode = NULL;
        (*head)->nxtNode = NULL;
        (*head)->element = 0;
        return;
    }
    else
    {
        // if roll matches with the first node itself
        // updating ref->prev
        if ((*head)->prevNode->element == roll)
        {
            struct Node *temp = (*head)->prevNode;
            free((*head)->prevNode);
            temp->nxtNode->prevNode = NULL;
            (*head)->prevNode = temp->nxtNode;
            (*head)->element--; // decrementing node count of ref
            return;
        }

        // if roll matches with the last node
        // updating ref->next
        else if ((*head)->nxtNode->element == roll)
        {
            struct Node *temp = (*head)->nxtNode;
            (temp->prevNode)->nxtNode = NULL;
            free((*head)->nxtNode);
            (*head)->nxtNode = temp->prevNode;
            (*head)->element--; // decrementing node count of ref
            return;
        }

        else
        {
            // traverse the ll until the right node found
            struct Node *tempNode = (*head)->prevNode;
            while (tempNode->nxtNode != NULL)
            {
                if (roll == tempNode->element)
                {
                    struct Node *temp = tempNode->prevNode;
                    tempNode->nxtNode->prevNode = temp;
                    temp->nxtNode = tempNode->nxtNode;
                    free(tempNode);
                    (*head)->element--; // decrementing node count of ref
                    return;
                }
                tempNode = tempNode->nxtNode;
            }
        }
    }
    printf("\nCan't Dlt - No roll no. %d is found.\n", roll);
}

// ---------------- Searching ----------------
void search(struct Node *head, int qroll)
{
    if (head->prevNode->element == qroll)
    {
        printf("Roll %d found at Head Node!!\n", qroll);
        return;
    }
    else if (head->nxtNode->element == qroll)
    {
        printf("Roll %d found at Last Node !!\n", qroll);
        return;
    }
    else
    {
        while (head->prevNode != NULL || head->nxtNode != NULL)
        {
            if (head->prevNode->element == qroll)
            {
                printf("Roll %d found at Intermediate Node !!\n", qroll);
                return;
            }
            else if (head->nxtNode->element == qroll)
            {
                printf("Roll %d found at Intermediate Node !!\n", qroll);
                return;
            }
            else
            {
                // increment backward
                head->nxtNode = head->nxtNode->prevNode;
                // increment forward
                head->prevNode = head->prevNode->nxtNode;
            }
        }
    }
    printf("%d not found !!", qroll);
}

// ---------------- Display ----------------
void display(struct Node *head)
{
    if (head->prevNode == NULL || head->nxtNode == NULL)
    {
        printf("Empty List !!\n");
        return;
    }

    struct Node *temp = head->prevNode;
    while (temp != NULL)
    {
        printf("<-%d->", temp->element);
        temp = temp->nxtNode;
    }
    printf("\nNode count = %d\n", head->element);
}

// ---------------- Driver Code ----------------
int main()
{
    struct Node *head = NULL;

    // Date: 23/1/15
    // insertNode(&head, 12);
    // insertNode(&head, 6);
    // insertNode(&head, 23);
    // insertNode(&head, 28);
    // insertNode(&head, 19);
    // insertNode(&head, 2);
    // insertNode(&head, 8);
    // display(head);

    // Date: 23/1/16
    // dltNode(&head, 2);
    // dltNode(&head, 28);
    // display(head);

    // * Test Case: Dlt the first node :
    // insertNode(&head, 19);
    // insertNode(&head, 2);
    // insertNode(&head, 8);
    // display(head);
    // dltNode(&head, 2);
    // display(head);

    // * Test Case: Dlt the last node :
    // insertNode(&head, 19);
    // insertNode(&head, 2);
    // insertNode(&head, 25);
    // insertNode(&head, 8);
    // display(head);
    // dltNode(&head, 25);
    // display(head);

    // * Test Case: Dlt intermediate node :
    // insertNode(&head, 19);
    // insertNode(&head, 2);
    // insertNode(&head, 25);
    // insertNode(&head, 8);
    // insertNode(&head, 16);
    // display(head);
    // dltNode(&head, 16);
    // display(head);

    // * Test Case: Only one node is present under ref & dlt that node :
    // insertNode(&head, 2);
    // display(head);
    // dltNode(&head, 2);
    // display(head);

    // * Test Case: No node with given roll found :
    // insertNode(&head, 12);
    // insertNode(&head, 6);
    // insertNode(&head, 23);
    // display(head);
    // dltNode(&head, 112);

    // Date: 23/1/18
    insertNode(&head, 2);
    insertNode(&head, 6);
    insertNode(&head, 12);
    insertNode(&head, 23);
    insertNode(&head, 28);
    display(head);

    // * Test Case: Node found at Head Node :
    // search(head,2);

    // * Test Case: Node found at Tail Node :
    // search(head,28);

    // * Test Case: Node found at intermediate Node :
    // search(head,12);
    search(head,23);

    // * Test Case: Node not found :
    // search(head, 145);

    return 0;
}

