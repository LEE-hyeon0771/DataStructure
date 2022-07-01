//LinearList  -> Array���
//���԰� ���� �� ������� �׸��� ������ ����, �޸� �Ҹ� Ŀ�� ����, �������� ��ȿ����

#include<stdio.h>
#define MAX_SIZE 1000

typedef int element;
typedef struct {                //List�� ����ü�� ����
	int list[MAX_SIZE];
	int length;
}ArrayListType;

void init(ArrayListType* L) {          //����Ʈ �ʱ�ȭ
	L->length = 0;
}

int isEmpty(ArrayListType* L) {        //����Ʈ�� ������� ��
	return L->length == 0;
}

int isFull(ArrayListType* L) {         //����Ʈ�� ������ ���� ��
	return L->length == MAX_SIZE; 
}

//���� �Լ� ����
void insert(ArrayListType* L, int pos, element item) {
	int i;
	if (isFull(L)) {
		error("List is Full!");
	}
	else if ((pos < 0) || (pos > L->length)) {
		error("Index Error");
	}
	else {
		for (i = (L->length - 1); i >= pos; i--) {   //ū �ε��� ���� ���� �ε����� �������鼭 ���ڸ��� �������
 			L->list[i + 1] = L->list[i];             //���� �ε����� ���� �ε��� ���� �����鼭 �߰��� ���ڸ� ����
		}
		L->list[pos] = item;    //pos�� ����ִ� �����ڸ� : item ���� �־���
		L->length++;            //���̴� �þ����
	}
}

//���� �Լ� ����
void delete(ArrayListType* L, int pos, element item) {
	int i;
	if (isEmpty(L)) {
		error("List is Empty!");
	}
	else if ((pos < 0) || (pos > L->length)) {
		error("Index Error");
	}
	else {
		item = L->list[pos];                         //���� ��ġ�� ��Ұ� ��ȯ�� ���� ����
		for (i = pos; i < (L->length - 1); i++) {    //pos���� length-1�ε��� �������� ������Ű�鼭 �����ؼ� ĭ�� �پ������
			L->list[i] = L->list[i + 1];
		}
		L->length--;                                 //���̴� �پ������
		return item;
	}
}