#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    int id;
    char title[50];
    int freq;
    struct node *left, *right;
};
typedef struct node bnode;

bnode *root = NULL;
bnode *secRoot = NULL;

int totalAccessTime = 0;

int totalData = 0;
bnode *createBinarySearchTree(bnode *subRoot, bnode *Node);
void orderArray(bnode *pNode, int i);
bnode *createBinaryTree(bnode *pNode, bnode *node, int k, int n);
bnode *btArray;

void readLine()
{ //Read input.txt file line by line, in every line that construct bnode then send this node to insert function.
    static const char filename[] = "./input.txt";
    FILE *fp = fopen(filename, "r");
    bnode *node;
    bnode temp;

    if (!fp)
        perror("Error");
    else
    {
        char inputline[200];
        while (fgets(inputline, sizeof inputline, fp) != NULL)
        {
            node = (bnode *)malloc(sizeof(bnode));
            int counter = 0;
            char *token = strtok(inputline, ",");

            while (token != NULL)
            {
                if (counter == 0)
                {
                    node->id = atoi(token);
                    //printf("%d\n", node->id);
                }
                else if (counter == 1)
                {
                    for (int i = 0; token[i]; i++)
                    {
                        token[i] = tolower(token[i]);
                    }
                    strcpy(node->title, token);
                    //printf("%s\n", node->title);
                }
                else if (counter == 2)
                {
                    node->freq = atoi(token);
                    //printf("%d\n", node->freq);
                }

                token = strtok(NULL, ",");
                counter++;
            }
            node->right = NULL;
            node->left = NULL;
            memcpy(&temp, node, sizeof(bnode));
            btArray[node->id - 1] = temp;
            root = createBinarySearchTree(root, node);
        }
        fclose(fp);

    }
}

bnode *createBinarySearchTree(bnode *subRoot, bnode *Node)
{

    if (subRoot == NULL)
    {
        return Node;
    }
    if (strcmp(subRoot->title, Node->title) > 0)
    {
        subRoot->left = createBinarySearchTree(subRoot->left, Node);
    }
    else
    {
        subRoot->right = createBinarySearchTree(subRoot->right, Node);
    }
    return subRoot;
}

void printlnr(bnode *subRoot)
{
    if (subRoot != NULL)
    {
        printlnr(subRoot->left);
        printf("%s \n", subRoot->title);
        printlnr(subRoot->right);
    }
}

void getTotalAccessTime(bnode *node, int level)
{
    int total = (node->freq) * level;
    totalAccessTime += total;
}

int getLevel(bnode *node, int data, int level)
{

    if (node == NULL)
        return 0;

    if (node->id == data)
    {
        getTotalAccessTime(node, level);
        //btArray[data - 1] = *node;
        return level;
    }

    int sublevel = getLevel(node->left, data, level + 1);
    if (sublevel != 0)
        return sublevel;

    sublevel = getLevel(node->right, data, level + 1);
    return sublevel;
}

void orderArray(bnode pNode[], int size)
{
    int j;
    bnode temp;

    for (int i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (pNode[j].freq < pNode[j + 1].freq)
            {
                temp = pNode[j];
                pNode[j] = pNode[j + 1];
                pNode[j + 1] = temp;
            }
        }
    }
}
bnode *createBinaryTree(bnode *secroot, bnode node[], int k, int n)
{
    // Base case for recursion
    if (k < n)
    {
        bnode *temp = &node[k];
        secroot = temp;

        // insert left child
        secroot->left = createBinaryTree(secroot->left, node,
                                         2 * k + 1, n);

        // insert right child
        secroot->right = createBinaryTree(secroot->right, node,
                                          2 * k + 2, n);
    }
    return secroot;
}

int findLineNum(){
    static const char filename[] = "./input.txt";
    FILE *fp = fopen(filename, "r");

    if(!fp){
        perror("Error");
    }
    else{
        char inputline[200];
        while(fgets(inputline, sizeof inputline, fp) != NULL){
            totalData++;
        }
    }
    return totalData;
}

int main()
{
    int x;
    int dataNum = findLineNum();
    btArray = (bnode *)malloc(sizeof(bnode) * dataNum);

    readLine();
    printf("Total data: %d \n", totalData);
    printf("********* binary search tree with lnr traversal (a) ********\n\n");
    printlnr(root);

    for (x = 1; x <= dataNum; x++)
    {
        getLevel(root, x, 1);

    }

    printf("\nTotal access time of binary search tree (b): %d \n\n", totalAccessTime);

    printf("********* binary tree with lnr traversal (c) ********\n");

    orderArray(btArray, dataNum);
    secRoot = createBinaryTree(secRoot, btArray, 0, dataNum);
    printlnr(secRoot);


    totalAccessTime = 0;

    for (x = 1; x <= dataNum; x++)
    {
        getLevel(secRoot, x, 1);
    }

    printf("\nTotal access time of binary tree (d): %d \n", totalAccessTime);
    return 0;
}
