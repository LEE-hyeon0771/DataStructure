#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeNode {
	int key;
	struct BinaryTreeNode* left, * right;
}BinTree;

BinTree* root = NULL;

BinTree* createBT(int num) {
	BinTree* root = (BinTree*)malloc(sizeof(BinTree));
	root->key = num;
	root->left = NULL;
	root->right = NULL;
	return root;
}

BinTree* searchBST(BinTree* bt, int x) {
	BinTree* p = bt;
	while (p != NULL) {
		if (x == p->key)
			return p;
		if (x < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	printf("ERROR : ã�� Ű�� �����ϴ�\n");
	return NULL;
}

BinTree* insertBST(BinTree* node, int x) {
	if (node == NULL) {
		BinTree* newNode = (BinTree*)malloc(sizeof(BinTree));
		newNode->key = x;
		newNode->left = NULL;
		newNode->right = NULL;

		return newNode;
	}

	if (x < node->key)
		node->left = insertBST(node->left, x);
	else if (x > node->key)
		node->right = insertBST(node->right, x);
	else {
		printf("ERROR: �̹� ���� Ű�� �ֽ��ϴ�.\n");
		return node;
	}
	return node;
}

void deleteBST(BinTree* bt, int x) {
	BinTree* p = NULL;
	BinTree* parent = NULL;
	BinTree* q = NULL;

	// ������ ���� �θ��� ã��.
	p = searchBST(bt, x);
	parent = root;
	while (parent != NULL) {
		if (parent->right == p || parent->left == p) {
			break;
			if (x < parent->key) parent = parent->left;
			else parent = parent->right;
		}
	}
	
	// ������ ��尡 ���� ���
	if (p == NULL) {
		return;
	}

	// CASE 1 : ������ ����� ������ 0�� ���
	if (p->left == NULL && p->right == NULL) {
		if (parent->left == p) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
	}

	// CASE 2 : ������ ����� ������ 1�� ���
	else if (p->left == NULL || p->right == NULL) {
		if (p->left != NULL) {
			if (parent->left == p) {
				parent->left = p->left;
			}
			else {
				parent->right = p->left;
			}
		}
		else {
			if (parent->left == p) {
				parent->left = p->right;
			}
			else {
				parent->right = p->right;
			}
		}
	}
	// CASE 3 : ������ ����� ������ 2�� ���
	else if (p->left != NULL && p->right != NULL) {
		q = p->left;
		while (q->right != NULL) {
			q = q->right;
		}
		p->key = q->key;
		deleteBST(p->left, q->key);
	}
}

void displayInorder(BinTree* bt) {	// ���� Ž�� Ʈ���� ���� ��ȸ�ϸ鼭 ����ϴ� ����
	if (bt != NULL) {
		
		displayInorder(bt->left);
		printf(" %d,", bt->key);
		displayInorder(bt->right);
	}
}
void main()
{
	//BinTree *root = NULL;
	int key;
	root = insertBST(root, 5);
	insertBST(root, 3);
	insertBST(root, 7);
	insertBST(root, 2);
	insertBST(root, 6);
	insertBST(root, 9);
	
	printf("tree��?\n");
	displayInorder(root);

	printf("������ ���ڴ�?");
	scanf_s("%d", &key);
	deleteBST(root, key);
	displayInorder(root);
	return;
}