#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char data;
    struct node *left,*right;
} node;
node*newnode(char key)
{
    node *n=malloc(sizeof(node));
    n->data=key;
    return n;
}
node* insert(node*root,char key)
{
    if(root==NULL)
        root=newnode(key);
    else if(key<root->data)
        root->left=insert(root->left,key);
    else if(key>root->data)
        root->right=insert(root->right,key);
    return root;
}
void inorder(node*root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%c",root->data);
        inorder(root->right);
    }
}
int main()
{
    node*n=newnode('c');
    insert(n,'f');
    printf("%c",n->data);
    inorder(n);
    return 0;
}
