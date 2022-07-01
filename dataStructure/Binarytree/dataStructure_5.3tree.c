#include<stdio.h>
#include<stdlib.h>

typedef int BTData;
typedef struct BinaryTreeNode {
	BTData data;
	struct BinaryTreeNode* left, *right;
}BinTree;

BinTree* createBT(int num) {
	BinTree* root = (BinTree*)malloc(sizeof(BinTree));
	root->data = num;
	root->left = NULL;
	root->right = NULL;
	return root;
}
void inorderTraverse(BinTree* BT) {
	if (BT != NULL) {
		inorderTraverse(BT->left);
		printf("%d\n", BT->data);
		inorderTraverse(BT->right);
	}
	return;
}

void postorderTraverse(BinTree* BT) {
	if (BT != NULL) {
		postorderTraverse(BT->left);
		postorderTraverse(BT->right);
		printf("%d\n", BT->data);
	}
}

void preorderTraverse(BinTree* BT) {
	if (BT != NULL) {
		printf("%d\n", BT->data);
		preorderTraverse(BT->left);
		preorderTraverse(BT->right);
	}
}

int main() {

	BinTree* root;

	root = createBT(1);
	root->left = createBT(2);
	root->right = createBT(3);

	printf("전위 순회\n");
	preorderTraverse(root);
	printf("\n");

	printf("중위 순회\n");
	inorderTraverse(root);
	printf("\n");

	printf("후위 순회\n");
	postorderTraverse(root);
	printf("\n");
	return 0;
}