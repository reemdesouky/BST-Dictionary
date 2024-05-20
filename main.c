#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char data[100];
    struct node *left;
    struct node *right;
} node;
node *newnode(char *key)
{
    node *n = malloc(sizeof(node));
    strcpy(n->data, key);
    n->left = NULL;
    n->right = NULL;
    return n;
}
node *insert(node *root, char *key)
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
void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s\n", root->data);
        inorder(root->right);
    }
}
int countSize(node *root)
{
    if (!root)
        return 0;
    else
        return 1 + countSize(root->left) + countSize(root->right);
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int height(node *root)
{
    if (root == NULL)
        return -1;
    else

        return 1 + max(height(root->left), height(root->right));
}
node *suc(node *root, node *n)
{
    if (n->right != NULL)
    {
        node *temp = n->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    node *successor = NULL;
    node *ancestor = root;
    while (ancestor != n)
    {
        if (strcasecmp(n->data, ancestor->data) < 0)
        {
            successor = ancestor;
            ancestor = ancestor->left;
        }
        else
        {
            ancestor = ancestor->right;
        }
    }
    return successor;
}

node *pred(node *root, node *n)
{
    if (n->left != NULL)
    {
        node *temp = n->left;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp;
    }

    node *predecessor = NULL;
    node *ancestor = root;
    while (ancestor != n)
    {
        if (strcasecmp(n->data, ancestor->data) > 0)
        {
            predecessor = ancestor;
            ancestor = ancestor->right;
        }
        else
        {
            ancestor = ancestor->left;
        }
    }
    return predecessor;
}
node *searchIterative(node *root, char *value)
{
    if (root == NULL)
    {
        return NULL;
    }
    node *temp = root;
    node *current;
    while (temp)
    {
        if (strcasecmp(value, temp->data) == 0)
            return temp;
        current = temp;
        if (strcasecmp(value, temp->data) < 0)
        {
            temp = temp->left;
        }
        else if (strcasecmp(value, temp->data) > 0)
        {
            temp = temp->right;
        }
    }
    node *successor = suc(root, current);
    node *predecessor = pred(root, current);
    printf("suggestions: %s, %s, %s\n", current->data, successor->data, predecessor->data);
}
node *searchRecursive(node *root, char *value)
{
    if (root == NULL)
    {
        return NULL;
    }
    int cmp = strcasecmp(value, root->data);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return searchRecursive(root->left, value);
    else
        return searchRecursive(root->right, value);
}
void check(node *dict, char *sentence)
{
    char *tok = strtok(sentence, " ");
    while (tok)
    {
        if (searchRecursive(dict, tok) != NULL)
        {
            printf("%s - Correct\n", tok);
        }
        else
        {
            printf("%s - Incorrect,", tok);
            searchIterative(dict, tok);
        }
        tok = strtok(NULL, " ");
    }
}

int main()
{
    FILE *f = fopen("Dictionary.txt", "r");
    if (f == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    char x[100];
    fscanf(f, "%s", &x);
    node *dict = newnode(x);
    while (!feof(f))
    {
        fscanf(f, "%s", &x);
        insert(dict, x);
    }
    /// inorder(dict);
    printf("Dictionary Loaded Successfully...!\n");
    printf("..................................\n");
    printf("Size = %d\n", countSize(dict));
    printf("..................................\n");
    printf("Height = %d\n", height(dict));
    printf("..................................\n");

    printf("Enter a sentence:\n");
    char sentence[100];
    gets(sentence);

    check(dict, sentence);

    fclose(f);
    return 0;
}
