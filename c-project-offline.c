#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct ListNode {
    int value;
    int frequency;
    struct ListNode* next;
} ListNode;

//this function creates a ListNode and adds that node to the end of the list.
void addListNode(ListNode** head, int value , int frequency);
//This function prints the current state of the list
void printList(ListNode* head);
//This function sorts the list in respect to frequency values
void sortLinkedList(ListNode** head);
//This function counts how many nodes are present in the list, this value is required for preOrder function.
int countListNodes (ListNode* head);
//This function prints the binary search tree using pre order traversal
void preOrder(TreeNode* r, int numberOfNodes);
//This function inserts the given treeNodes to binary search tree
TreeNode* insertValue (TreeNode* rootP, int value);
//This function creates the binary tree
void constructTree(ListNode**head, TreeNode** root);
//This function creates a new tree node
TreeNode* createTreeNode(int value);

int main (int argc, char *argv[])
{
    if (argc != 2) {
        printf("The input file was not passed, program terminated.");
        return 1; 
    }

    FILE *file = fopen(argv[1], "r");
    ListNode* head = NULL;
    TreeNode* root = NULL;

    if(file == 0)
    {
        printf("Error occured while opening file");
        return 1;
    }

    //maximum integer is 2147483647. Which has a total of 10 characters. 2 characters ara reserved for space and ',' characters. Frequency is assumed to be less than 1000. Therefore we used a array sized 15.
    char buffer[15];

    while(fgets(buffer,15,file)!=NULL)
    {
        //This loop extracts the value part from the input file
        int i = 0;
        char intValueBuffer[15];
        while(buffer[i] != ',')
        {
            intValueBuffer[i] = buffer[i];
            i++;
        }
        intValueBuffer[i] = '\0';
        int value = atoi(intValueBuffer);
        

        i = i + 2;
        int j = 0;
        char intFrequencyBuffer[15];
        //This loop extracts the frequency part from the input file
        while(buffer[i] >= '0' && buffer[i]<='9' && buffer[i] != '\0')
        {
            intFrequencyBuffer[j] = buffer[i];
            j++;
            i++;
        }
        intFrequencyBuffer[j] = '\0';
        
        int frequency = atoi(intFrequencyBuffer);
        //printf("Buffer : %s\n", buffer);
        //printf("%d  %d\n",value,frequency);
        addListNode(&head, value , frequency);   
    }  
    fclose(file);
    //printList(head);
    sortLinkedList(&head);
    //printf("-------------------\n");
    //printList(head);
    //printf("--------------\n");
    //printList(head);
    constructTree(&head,&root);
    //printf("Root : %d\n" , root->value);
    //printf("Root sağ : %d\n" , root->right->value);
    //printf("Root sol: %d\n" , root->left->value);
    printf(">Pre-order traversal of constructed tree : ");
    preOrder(root, countListNodes(head));
    return 1;
}

//Linked list operations for reading and sorting the values and frequencies
void addListNode(ListNode**head, int value , int frequency)
{
    if(*head == NULL)
    {
        (*head) = malloc(sizeof(ListNode));
        (*head) -> value = value;
        (*head) ->frequency = frequency;
        (*head) ->next=NULL;
        return;
    }

    //creates new Node
    ListNode* node = malloc(sizeof(ListNode));
    node -> value = value;
    node ->frequency = frequency;
    node ->next=NULL;
    //adds the new node to the end of the list

    ListNode* temp = *head;

    while(temp->next != NULL)
    {       
        temp = temp ->next;
    }
    temp ->next = node;   
}
void printList(ListNode* head)
{
    ListNode* temp = head;
    while(temp != NULL)
    {
        printf("%d  %d\n", temp->value, temp->frequency);
        temp = temp -> next;
    }
}
void sortLinkedList(ListNode** head)
{
    int operations = 1;
    while(operations != 0)
    {
        ListNode* iter1 = (*head);
        ListNode* iter2 = (*head)->next;
        int tempVal;
        int tempFreq;
        operations = 0;
        while(iter1 != NULL && iter2 !=NULL)
        {                     
            if(iter2->frequency >= iter1->frequency)
            {
            tempVal = iter1->value;
            tempFreq = iter1->frequency;

            iter1 ->frequency = iter2 ->frequency;
            iter1 ->value = iter2->value;

            iter2 ->frequency = tempFreq;
            iter2 ->value = tempVal;
            operations++;
            }        
            iter1 = iter1->next;
            iter2 = iter2->next;
        }
    }
}
int countListNodes (ListNode* head)
{
    int numberOfNodes = 0;
    ListNode* temp = head;
    while(temp != NULL)
    {
        temp = temp->next;
        numberOfNodes++;
    }
    return numberOfNodes;
}

TreeNode* createTreeNode(int value)
{
    TreeNode* result = malloc(sizeof(TreeNode));
    if(result != NULL)
    {
        result->left = NULL;
        result ->right=NULL;
        result ->value = value;
    }
    return result;
}


TreeNode* insertValue (TreeNode* root, int value)
{
    if(root == NULL)
    {
        root = createTreeNode(value);
    }
    else if(value <= root->value)
    {
        root ->left = insertValue(root->left,value);
    }
    else
    {
        root ->right = insertValue(root->right,value);
    }
    return root;
}

void constructTree(ListNode**head, TreeNode** root)
{
    ListNode* temp = (*head);
    while(temp != NULL)
    {
        *root = insertValue(*root,temp->value);
        temp = temp -> next;
    }
}



void preOrder(TreeNode* r, int numberOfNodes)
{
    static int a = 0;
	if(r!= NULL)
	{   
        a++;
        if(a != numberOfNodes)   
		    printf("%d, ",r->value);
        else
            printf("%d",r->value);
		preOrder(r->left,numberOfNodes);
		preOrder(r->right,numberOfNodes);
	}
    if(a == numberOfNodes)
        a = 0;
}


	

