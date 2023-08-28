#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    struct Node*left;
    struct Node*right;
    char data[50];
} Node;
Node* newNode(char* x)
{
    Node*n=malloc(sizeof(Node));
    strcpy(n->data,x);
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* search(Node* root, char* key)
{
    if(root==NULL)
        return NULL;
    else if(strcasecmp(root->data,key)==0)
        return root;
    else if(strcasecmp(key,root->data)<0)
        return search(root->left,key);
    else
        return search(root->right,key);
}
Node* insert(Node* root, char* x)
{
    if(root==NULL)
    {
        Node*n=newNode(x);
        root=n;
    }
    else if (strcasecmp(x,(root->data))<0)
        root->left=insert(root->left,x);
    else
        root->right=insert(root->right,x);
    return root;
}
int maxdepth(Node*root)
{
    if (root==NULL)
        return -1;
    else
    {
        int leftdepth=maxdepth(root->left);
        int rightdepth=maxdepth(root->right);
        if (leftdepth>rightdepth)
            return (leftdepth+1);
        else
            return (rightdepth+1);
    }
}
int size(Node*root)
{
    if (root==NULL)
        return 0;
    return 1+size(root->left)+size(root->right);
}
Node* search2(Node* root, char* key, Node* temp)
{
    if(root==NULL)
        return temp;
    else if(strcasecmp(key,root->data)<0)
    {
        temp=root;
        return search2(root->left,key,temp);
    }
    else
    {
        temp=root;
        return search2(root->right,key,temp);
    }
}
Node*findmin(Node*root)
{
    if (root==NULL)
        return NULL;
    else if (root->left!=NULL)
        return findmin(root->left);
    else
        return root;
}
Node*findmax(Node*root)
{
    if (root==NULL)
        return NULL;
    else if (root->right!=NULL)
        return findmax(root->right);
    else
        return root;
}
Node*successor(Node*root,char *s)
{
    Node*successive=NULL;
    Node*current=root;
    while(current && strcasecmp(current->data,s)!=0)
    {
        if (strcasecmp(current->data,s)>0)
        {
            successive=current;
            current=current->left;
        }
        else
            current=current->right;
    }
    if (!current)
        return NULL;
    if (current->right)
        successive=findmin(current->right);
    return successive;
}
Node*predecessor(Node*root,char*s)
{
    Node*pre=NULL;
    Node*current=root;
    while(current && strcasecmp(current->data,s)!=0)
    {
        if (strcasecmp(current->data,s)<0)
        {
            pre=current;
            current=current->right;
        }
        else
            current=current->left;
    }
    if (!current)
        return NULL;
    if (current->left)
        pre=findmax(current->left);
    return pre;
}
int main()
{
    FILE*f=fopen("input.txt","r");
    Node*root=NULL;
    if(f==NULL)
    {
        printf("ERROR");
        return 0;
    }
    else
        printf("Dictionary loaded successfully! \n");
    char str[50];
    while(!feof(f))
    {
        fscanf(f,"%s",str);
        root=insert(root,str);
    }
    fclose(f);

    printf("Size = %d\n", size(root));
    printf("Height = %d\n", maxdepth(root));

    char string[50];
    printf("Enter a sentence:");
    gets(string);
    char * token = strtok(string," ");
    while( token != NULL )
    {
        Node*k=search(root,token);
        if(k)
            printf("%s - Correct \n", k->data);
        else
        {
            printf("%s - Incorrect, Suggestions :",token);
            Node*temp=NULL;
            Node*a=search2(root,token,temp);
            printf("%s  ",a->data);
            Node*b=successor(root,a->data);
            printf("%s  ",b->data);
            Node*c=predecessor(root,a->data);
            printf("%s  ",c->data);
            printf("\n");
        }
        token = strtok(NULL," ");
    }
    return 0;
}
