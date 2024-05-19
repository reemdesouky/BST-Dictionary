#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char data[100];
    struct node* left;
    struct node* right;
} node;
node* newnode(char* key)
{
    node* n = malloc(sizeof(node));
    strcpy(n->data, key);
    n->left = NULL;
    n->right = NULL;
    return n;
}
node* insert(node* root, char* key)
{
    if (root == NULL)
        return newnode(key);
    int cmp = strcasecmp(key, root->data);
    if (cmp < 0)
        root->left = insert(root->left, key);
    else if (cmp > 0)
        root->right = insert(root->right, key);
    return root;
}
void inorder(node*root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%s\n",root->data);
        inorder(root->right);
    }
}
int countSize(node*root)
{
    if(!root)
        return 0;
    else
        return 1+countSize(root->left)+ countSize(root->right);
}
node* searchRecursive(node*root, char* value)
{
    if (root==NULL)
    {
        return NULL;
    }
    int cmp=strcasecmp(value,root->data);
    if(cmp==0)
        return root;
    else if (cmp < 0)
        return searchRecursive(root->left, value);
    else
        return searchRecursive(root->right, value);
}
void check (node*dict,char *sentence)
{
    char*tok=strtok(sentence," ");
    while(tok)
    {
        if(searchRecursive(dict,tok)!=NULL)
        {
            printf("%s - Correct\n",tok);
        }
        else
            printf("%s - Incorrect\n",tok);
        tok=strtok(NULL," ");
    }
}

int main()
{
    FILE *f=fopen("Dictionary.txt","r");
    if (f==NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    char x[100];
    fscanf(f,"%s",&x);
    node*dict=newnode(x);
    while(!feof(f))
    {
        fscanf(f,"%s",&x);
        insert(dict, x);
    }
   /// inorder(dict);
   printf("Dictionary Loaded Successfully...!\n");
   printf("..................................\n");
   printf("Size = %d\n",countSize(dict));
   printf("..................................\n");


  printf("Enter a sentence:\n");
   char sentence[100];
   gets(sentence);

   check(dict,sentence);

    fclose(f);
    return 0;
}
