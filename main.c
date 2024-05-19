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
int main()
{
    node*dict=newnode("start");
    FILE *f=fopen("Dictionary.txt","r");
    if (f==NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    char x[100];
    while(!feof(f))
    {
        fscanf(f,"%s",&x);
        insert(dict, x);
    }
    inorder(dict);
    fclose(f);
    return 0;
}
