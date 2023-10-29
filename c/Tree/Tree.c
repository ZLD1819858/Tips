#include "stdio.h"

#define NULL    ((void *)0)

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/* 创建节点、插入节点、遍历 */
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
TreeNode* insertNode(TreeNode* root, int data) {
    if (NULL == root) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}
void preorderTraversal(TreeNode* root) {
    if (NULL == root) {
        return;
    }

    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(TreeNode* root) {
    if (NULL == root) {
        return;
    }

    preorderTraversal(root->left);
    printf("%d ", root->data);
    preorderTraversal(root->right);
}
void postorderTraversal(TreeNode* root) {
    if (NULL == root) {
        return;
    }

    preorderTraversal(root->left);
    preorderTraversal(root->right);
    printf("%d ", root->data);
}
int main() {
    TreeNode* root = createNode(3);

    insertNode(root, 2);
    insertNode(root, 1);
    insertNode(root, 1);
    insertNode(root, 5);
    insertNode(root, 10);
    insertNode(root, 20);
    insertNode(root, 50);
    insertNode(root, 100);
    insertNode(root, 200);
    insertNode(root, 500);
    insertNode(root, 1000);

    printf("先序遍历: ");
    preorderTraversal(root);
    printf("\n");
    printf("中序遍历: ");
    inorderTraversal(root);
    printf("\n");
    printf("后序遍历: ");
    postorderTraversal(root);
    printf("\n");


    return 0;
}