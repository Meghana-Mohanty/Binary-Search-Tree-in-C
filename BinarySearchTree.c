#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

struct node
{
  struct node *left;
  int data;
  int frequency;
  struct node *right;
};

struct queueNode
{
    struct node *qdata;
    struct queueNode *next;
};

//function delcarations
void preorder (struct node *root);
void postorder (struct node *root);
void inorder (struct node *root);
int insert (struct node **root, int key);
void create_node (struct node **fnewnode, int item);
int getHeight(struct node **froot);
struct node* dequeue(struct queueNode **ffront, struct queueNode **frear);
int enqueue(struct queueNode **ffront, struct queueNode **frear, struct node **fdata);
void levelWiseTraversal(struct node **froot);
bool search (struct node **froot, int key);
int smallestnode (struct node *root);
int largestnode (struct node *root);
void DeleteTree(struct node *root);
void deleteNode(struct node **froot, int key);



int main (void)
{
    int succ = -1;
    int choice = 0;
    int num = 0;
    bool found = false;
    struct node *root = NULL;
    struct node *temp = NULL;
    
    int a[5] = {10,5,15 };
    
    printf("\n\t---Welcome to Binary Search Tree Simulation---");
    do
    {
        printf("\nEnter 1 if you want to insert a node into the tree");
        printf("\nEnter 2 if you want to see the elements in preorder fashion");
        printf("\nEnter 3 if you want to see the elements in inorder fashion");
        printf("\nEnter 4 if you want to see the elements in postorder fashion");
        printf("\nEnter 5 if you want to get the height of the tree");
        printf("\nEnter 6 if you want to see the elements in level-wise fashion");
        printf("\nEnter 7 if you want to search for an element");
        printf("\nEnter 8 if you want to see the largest element in the tree");
        printf("\nEnter 9 if you want to see the smallest element in the tree");
        printf("\nEnter 10 if you want to delete a node in the tree");
        printf("\nEnter 0 to exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 0:
            DeleteTree(root);
            break;
            
            case 1:
            printf("\n\tEnter the value to be inserted in node:");
            scanf("%d", &num);
            succ = insert(&root, num);
            if(succ == 1)
            {
                printf("\n\tNode added.");
            }
            else
            {
                printf ("\n\tNode could not be created.");
            }
            break;
            
            case 2:
            preorder(root);
            break;
            
            case 3:
            inorder(root);
            break;
            
            case 4:
            postorder(root);
            break;
            
            case 5:
            num = getHeight(&root);
            printf("\n\tHeight of the tree is : %d", num);
            break;
            
            case 6:
            levelWiseTraversal(&root);
            break;
            
            case 7:
            printf("\n\tEnter the value to be searched:");
            scanf("%d", &num);
            found = search(&root, num);
            if(found == true)
            {
                printf("\n\tElement is present in tree.");
            }
            else
            {
                printf("\n\tElement is not present in tree. Sorry");
            }
            break;
            
            case 8:
            num = largestnode(root);
            printf("\n\tLargest node = %d", num);
            break;
            
            case 9:
            num = smallestnode(root);
            printf("\n\tSmallest node = %d", num);
            break;
            
            case 10:
            printf("\n\tEnter the value to be inserted in node:");
            scanf("%d", &num);
            found = search(&root, num);
            if(found == true)
            {
                deleteNode(&root, num);
            }
            else
            {
                printf("\n\tElement is not present in tree.Cannot delete it");
            }
            break;
            
            default:
            printf("\n\tInvalid Choice.");
        }
        
    }while(choice != 0);
    
    return 0;
}

int no_of_nodes(struct node* root)
{
    int count = 0;
    if(root != NULL)
    {
        no_of_nodes(root->left);
        count++;
        no_of_nodes(root->right);
    }
    return count;
}

int getHeight(struct node **froot) 
{
    int depth = 0;
    struct node *root = NULL;
    root = *froot;
    if (root == NULL)
    {
        depth = 0;
    }
    else 
    {
        /* compute the depth of each subtree */
        int lDepth = getHeight(&(root->left));
        int rDepth = getHeight(&(root->right));
 
        /* use the larger one */
        if (lDepth > rDepth)
        {    
            depth = (lDepth + 1);
        }
        else
        {
            depth = (rDepth + 1);
        }
        return depth;
    }
    
}


void create_node(struct node **fnewnode, int item)
{
    struct node *temp = NULL;
    temp = *fnewnode;
    temp = (struct node *) calloc (1, sizeof (struct node));
    if(temp != NULL)
    {
        temp->data = item;
        temp->frequency = 1;
    }
    *fnewnode = temp;
    
}

void preorder (struct node *root)
{
    int i = 0;
    int n = 0;
    if (root != NULL)
    {
        n = root->frequency;
        for(i = 1; i <= n; i++)
        {
           printf ("\n%d ", root->data); 
        }
        preorder (root->left);
        preorder (root->right);
    }
}

void inorder (struct node *root)
{
    int i = 0;
    int n = 0;
    if (root != NULL)
    {
        n = root->frequency;
        inorder (root->left);
        for (i = 0; i < n; i++)
        {
           printf ("\n%d ", root->data); 
        }
        inorder (root->right);
    }
}

void postorder (struct node *root)
{
    int i = 0;
    int n = 0;
    if (root != NULL)
    {
        n = root->frequency;
        postorder (root->left);
        postorder (root->right);
        for (i = 0; i < n; i++)
        {
            printf ("\n%d ", root->data);
        }
    }
}

int insert (struct node **froot, int key)
{
    struct node *root = NULL;
    struct node *new = NULL;
    root = *froot;
    int succ = -1;

    if (root == NULL)
    {
        create_node(&new, key);
        root = new;
        succ = 1;
    }
    else
    {
        if (key == root->data)
        {
            root->frequency++;
            succ = 1;
            
        }
        else if (key < root->data)
        {
            if (root->left == NULL)
            {
                //new = create_node (key);
                create_node(&new, key);
                if(new == NULL)
                {
                    
                    succ = 0;
                }
                else
                {
                    root->left = new;
                    succ = 1;
                }
                
	        }
	        else
	        {
	            succ = insert(&(root->left), key);
	        }
        }
        else 
        {
            if(root->right == NULL)
            {
                //new = create_node (key);
                create_node(&new, key);
                if(new == NULL)
                {
                    printf ("Node could not be created.");
                    succ = 0;
                }
                else
                {
                root->right = new;
                succ = 1;
                }
            }
            else
            {
                succ = insert(&(root->right), key);
            }
        }
	}
  *froot = root;
  return succ;
}

int smallestnode (struct node *root)
{
    if (root->left == NULL)
    {
        return root->data;
    }
    return smallestnode (root->left);
}

int largestnode (struct node *root)
{
    if (root->right == NULL)
    {
        return root->data;
    }
    return largestnode (root->right);
}

bool search (struct node **froot, int key)
{
    static bool found = false;
    struct node *root = NULL;
    root = *froot;
    
    if (key == root->data)
    {
        found = true;
    }
    else if (key < root->data)
    {
        found = search (&root->left, key);
    }
    else if (key > root->data)
    {
        found = search (&root->right, key);
    }
    else if (root == NULL)
    {
        found = false;
    }
    *froot = root;
    return found;
    
}

void levelWiseTraversal(struct node **froot)
{
    int n = 0;
    int i = 0;
    struct queueNode *front = NULL;
    struct queueNode *rear = NULL;
    struct node *root = NULL;
    struct node *temp = NULL;
    
    root = *froot;
    temp = root;
    printf("\n-----Tree Data Level Wise-----");
    /*if(temp != NULL)
    {
        enqueue(&front, &rear, &temp);
        printf("\n\tEnqueing %d", temp->data);
        temp = dequeue(&front, &rear);
        printf("\n\tDequeuing data %d", temp->data);
    }*/
    while(temp != NULL)
    {
        n = temp->frequency;
        for (i = 0; i < n; i++)
        {
            printf ("\n\tData is %d ", temp->data);
        }
        
        if(temp->left != NULL)
        {
            //printf("\n\tEnqueing %d", temp->left->data);
            enqueue(&front, &rear, &(temp->left));
        }
        if(temp->right != NULL)
        {
            //printf("\n\tEnqueing %d", temp->right->data);
            enqueue(&front, &rear, &(temp->right));
        }
        temp = dequeue(&front, &rear);
        //printf("\n\tDequeuing data %d", temp->data);
        
    }
}

int enqueue(struct queueNode **ffront, struct queueNode **frear, struct node **fdata)
{
    //inserting at end and deletion from front. ALWAYS.
    int success = 0;
    struct queueNode *front = NULL;
    struct queueNode *rear = NULL;
    struct queueNode *newnode = NULL;
    front = *ffront;
    rear = *frear;
    
    newnode = (struct queueNode *)calloc(1, sizeof(struct queueNode));
    if(newnode == NULL)
    {
        success = -1;
    }
    else
    {
        newnode->qdata = *fdata;
        if(front == NULL && rear == NULL)
        {
            front = newnode;
            rear = newnode;
        }
        else
        {
            rear->next = newnode;
            rear = newnode;
        }
        success = 1;
    }
    
    *ffront = front;
    *frear = rear;
    //printf("\n\tRear data = %d", rear->qdata->data);
    return success;
}

struct node* dequeue(struct queueNode **ffront, struct queueNode **frear)
{
    //inserting at end and deletion from front. ALWAYS.
    struct node *d = NULL;
    struct queueNode *front = NULL;
    struct queueNode *rear = NULL;
    struct queueNode *dnode = NULL;
    front = *ffront;
    rear = *frear;
    
    if(front == NULL)
    {
        d = NULL;
    }
    else
    {
        dnode = front;
        front = front->next;
        dnode->next = NULL;
        d = dnode->qdata;
        free(dnode);
        dnode = NULL;
    }
    *ffront = front;
    *frear = rear;
    //printf("\n\t d data = %d", d->data);
    return d;
}

void deleteNode(struct node **froot, int key)
{
    int num = 0;
    struct node *root = NULL;
    struct node* temp = NULL;
    root = *froot;
    

    if(root != NULL)
    {
        if (key < root->data)
        {
            // If the key to be deleted is smaller than the root's
            // key, then it lies in left subtree
            deleteNode(&(root->left), key);
        }
        else if (key > root->data)
        {
            // If the key to be deleted is greater than the root's
            // key, then it lies in right subtree
            deleteNode(&(root->right), key);
        }
     
        // if key is same as root's key,
        // then This is the node
        // to be deleted
        else 
        {
            // node with only one child or no child
            if (root->left == NULL) 
            {
                temp = root->right;
                free(root);
                root = temp;
            }
            else if (root->right == NULL) 
            {
                struct node* temp = root->left;
                free(root);
                root =  temp;
            }
     
            // node with two children:
            // Get the inorder successor
            // (smallest in the right subtree)
            num = smallestnode(root->right);
     
            // Copy the inorder
            // successor's content to this node
            root->data = num;
     
            // Delete the inorder successor
            deleteNode(&(root->right), temp->data);
        }
    }
    
    *froot = root;
    
}

void DeleteTree(struct node *root)
{
    while(root)
    {
        deleteNode(&root, root->data);
    }
}
