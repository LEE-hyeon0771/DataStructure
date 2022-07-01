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
	printf("ERROR : 찾는 키가 없습니다\n");
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
		printf("ERROR: 이미 같은 키가 있습니다.\n");
		return node;
	}
	return node;
}

void deleteBST(BinTree* bt, int x) {
	BinTree* p = NULL;
	BinTree* parent = NULL;
	BinTree* q = NULL;

	// 삭제할 노드와 부모노드 찾기.
	p = searchBST(bt, x);
	parent = root;
	while (parent != NULL) {
		if (parent->right == p || parent->left == p) {
			break;
			if (x < parent->key) parent = parent->left;
			else parent = parent->right;
		}
	}
	
	// 삭제할 노드가 없는 경우
	if (p == NULL) {
		return;
	}

	// CASE 1 : 삭제할 노드의 차수가 0인 경우
	if (p->left == NULL && p->right == NULL) {
		if (parent->left == p) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
	}

	// CASE 2 : 삭제할 노드의 차수가 1인 경우
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
	// CASE 3 : 삭제할 노드의 차수가 2인 경우
	else if (p->left != NULL && p->right != NULL) {
		q = p->left;
		while (q->right != NULL) {
			q = q->right;
		}
		p->key = q->key;
		deleteBST(p->left, q->key);
	}
}

void displayInorder(BinTree* bt) {	// 이진 탐색 트리를 중위 순회하면서 출력하는 연산
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
	
	printf("tree는?\n");
	displayInorder(root);

	printf("삭제할 숫자는?");
	scanf_s("%d", &key);
	deleteBST(root, key);
	displayInorder(root);
	return;
}