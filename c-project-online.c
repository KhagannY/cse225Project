#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct TreeNode {
    int value;
    int frequency;
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
TreeNode* insertValue (TreeNode* root, int value, int frequency);
//This function creates the binary tree
void constructTree(ListNode**head, TreeNode** root);
//This function creates a new treenode with the given value and frequency
TreeNode* createTreeNode(int value, int frequency);
//This function returns the searched node that has the given value if it is present in the binary search tree and increments the frequency if found
TreeNode* searchValue (TreeNode* root, int value);
//These functions rotates the nodes to create the desired topology in respect to their frequency values
TreeNode* rightRotate(TreeNode* root);
TreeNode* leftRotate(TreeNode* root);
TreeNode* rotate(TreeNode* root);
int main(int argc, char *argv[])
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
        int i = 0;
        char intValueBuffer[15];
        while(buffer[i] <= '9' && buffer[i] >= '0')
        {
            intValueBuffer[i] = buffer[i];
            i++;
        }
        intValueBuffer[i] = '\0';
        int value = atoi(intValueBuffer);
        addListNode(&head, value , 0);   
    } 
    
    fclose(file); 
    sortLinkedList(&head);  
    constructTree(&head,&root);
    preOrder(root, countListNodes(head));
    
    int a;

    //The program terminates, when the program gets invalid input from user (ex: string)
   printf("Enter a value to search: ");
   while (scanf("%d", &a)==1) 
   {       
        searchValue(root, a);      
        int i;
        for(i = 0; i < countListNodes(head);i++){
            root = rotate(root);
        }
        preOrder(root, countListNodes(head));
    }
    printf("Program is terminated\n");
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
            if(iter2->frequency > iter1->frequency)
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

TreeNode* createTreeNode(int value, int frequency)
{
    TreeNode* result = malloc(sizeof(TreeNode));
    if(result != NULL)
    {
        result->left = NULL;
        result ->right=NULL;
        result ->value = value;
        result ->frequency = frequency;
    }
    return result;
}


TreeNode* insertValue (TreeNode* root, int value, int frequency)
{
    if(root == NULL)
    {
        root = createTreeNode(value,frequency);
    }
    else if(value <= root->value)
    {
        root ->left = insertValue(root->left,value,frequency);
    }
    else
    {
        root ->right = insertValue(root->right,value,frequency);
    }
    return root;
}

TreeNode* searchValue (TreeNode* root, int value)
{
    if (root == NULL) {        
        return NULL;
    }
    if(root->value == value)
    {
        root->frequency++; 
        return root;
    }
    else if(value < root->value)
    {
        return(searchValue((root->left),value));
    }
    else
    {
        return(searchValue((root->right),value));
    }
    return root;
}



void copyTreeToList(TreeNode* root, ListNode** head1) 
{

    if (root == NULL) {
        return;
    }
    addListNode(head1, root->value, root->frequency);
    copyTreeToList(root->left, head1);
    copyTreeToList(root->right, head1);
}
void constructTree(ListNode**head, TreeNode** root)
{
    ListNode* temp = (*head);
    while(temp != NULL)
    {
        *root = insertValue(*root,temp->value, temp->frequency);
        temp = temp -> next;
    }
}

void preOrder(TreeNode* r, int numberOfNodes)
{
    static int a = 0;
    static int b = 0;
    if(b==0 && r!= NULL)
    {
        printf(">Pre-order traversal of constructed tree : ");
        b++;
    }     
	if(r!= NULL)
	{   
        a++;
        if(a != numberOfNodes && r!= NULL)   
        {
            printf("(%d, %d), ",r->value, r->frequency);       
        }
        else if (a == numberOfNodes &&(r != NULL))
        {
            printf("(%d, %d)",r->value, r->frequency); 
            printf("\n");
        }
            
		preOrder(r->left,numberOfNodes);
		preOrder(r->right,numberOfNodes);
	}
    if(a == numberOfNodes)
    {
        a = 0;
        b = 0;
    }   
}
TreeNode* rightRotate(TreeNode* root){
    TreeNode* temp = NULL;
    temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}
TreeNode* leftRotate(TreeNode* root){
     TreeNode* temp = NULL;
     temp = root->right;
     root->right = temp->left;
     temp->left = root;
     return temp;
}

//This function should be used in a for loop with countListNodes function to guarantee the worst case scenario is satisfied.
TreeNode* rotate(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left != NULL && root->frequency < root->left->frequency) {
        root = rightRotate(root);
        
    }
    if(root->left != NULL){
        root->left = rotate(root->left);
    }

    if (root->right != NULL && root->frequency < root->right->frequency) {
        root = leftRotate(root);
        
    }
    if(root->right != NULL){
        root->right = rotate(root->right);
    }

    return root;
}