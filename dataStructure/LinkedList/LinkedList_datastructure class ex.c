#include<stdio.h>

//��� ����ü
typedef int element;
typedef struct ListNode {
	element data;            //����Ʈ ����� ������ �ʵ�
	struct ListNode* link;   //����Ʈ ����� Link �ʵ�
}listNode;

//head ����ü
typedef struct LinkedList {
	listNode* head;          //����Ʈ�� ù ��° �׸�(head �Ӹ� �κ�)
	int length;              //����Ʈ�� �׸� ����
}linkedList;

//���鸮��Ʈ ����
linkedList* initList(linkedList* L) {
	L = (linkedList*)malloc(sizeof(linkedList));
	L->head = NULL;
	L->length = 0;
	return L;
}

int getLength(linkedList* L) {
	return L->length;
}

//�˻�
listNode* search(linkedList* L, element x) {
	listNode* temp = L->head;
	while (temp != NULL) {        //head�� ������� ������
		if (temp->data == x) {      //�˻����� ã����
			return temp;            //�� �� ��ȯ
		}
		else {
			temp = temp->link;      //�ƴϸ� ���� ��ũ�� temp�̵�
		}
	}
	return temp;                //head�� ��������� �״�� ��� 
}


//����
void insert(linkedList* L,listNode* pre, element x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;

	if (L->head == NULL) {           //head�� Null�̸�
		newNode->link = NULL;        //�� ��� ��ũ�� Null�ϰŰ�
		L->head = newNode;           //Null�� head�� �� ��带 �־���  -> ���� ����Ʈ�� ��� ���
	}
	else if (pre == NULL) {          //��尡 Null�̸�
		newNode->link = L->head;     //�� ��� ��ũ�� head�� ���ְ�
		L->head = newNode;           //head���ٰ� �� ��带 ����ش�.  -> �� �� ���� ������ ���
	}
	else {
		newNode->link = pre->link;   //�� ��� ��ũ�� ���� ��ũ�� ���ְ�
		pre->link = newNode;         //�� ���� ��ũ�� �� �� ��� ��ũ�� ���� �� ��带 ����ش�. -> ����Ʈ �߰��� ������ ���
	}
	L->length++;  //���̸� �÷������ ���� ���� �̾����� LinkedList�� ��� �� �� ����
}

//�� �� ���� ������ ��츸�� �Լ�
void insertFirst(linkedList* L, element x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;
	newNode->link = L->head;
	L->head = newNode;
	L->length++;
}

//�������� ������ ��츸�� �Լ�
void insertLastNode(linkedList* L, element x) {
	listNode* newNode, *temp;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;
	newNode->link = NULL;

	if (L->head == NULL) {
		L->head = newNode;        //���鸮��Ʈ�� ���� -> head�� �� ��� ����ش�.
	}
	else {
		temp = L->head;
		while (temp->link != NULL) {           //��ũ�� NULL�� �ƴ϶�°� �տ� ���� ������ �ִٴ� ��
			temp = temp->link;                 //NULL�� �ƴҶ� link�� ��� �־��ְ� �Ǹ� �ᱹ �� ������ ��� �κб��� �ݺ��Ǽ� ������
		}
		temp->link = newNode;          //�� ������ ��ũ �κп� �� ��带 ����
	}
	L->length++;
}

//����
int deleteNode(linkedList* L, listNode* p) {      //p�� ������ ���
	listNode* pre;      //pre�� ������ ����� �� ���

	if (L->head == NULL)          //���鸮��Ʈ�� ���
		return 0;                 //false
	if (p == NULL)                //listNode�� ��尡 ���� ���
		return 0;                 //false
	pre = L->head;
	while (pre->link != p) {         //pre�� ��� link�� p�� ��� ��ũ�� �ٸ���
		pre = pre->link;             //pre�� pre�� ��� ��ũ�� �־���  ->  ������ ���� ��� ã��
		if (pre == NULL) {           //���࿡ pre�� ������ ������ ��尡 ���� ���̹Ƿ� false
			return 0;
		}
	}
	pre->link = p->link;             //pre��ũ�� p��ũ�� �־��� -> �ճ���� ��ũ �ʵ忡 ������ ����� ��ũ �ʵ尪�� ����
	free(p);                         //������ ��� p�� �޸� ���� ����  ->  ����

	L->length--;    //�߿�!!!  ������ ���� �ö󰡸鼭 �о�����, ������ ������ �Ʒ��� �������鼭 �ϳ��� �ٿ�����.
	return 1;
}


//������ ���
void displayList(linkedList* L) {
	listNode* p;
	printf("L=(");
	p = L->head;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->link;
		if (p != NULL) {
			printf(",");
		}
	}
	printf(")\n");
}