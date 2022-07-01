#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct Node {

	char name[50];
	int age;
	float bmi;
	
	struct Node* link;

}Node;



typedef struct linkedList{

	Node* head;
	int length;
	
}linkedList;


linkedList* initList() {

	linkedList* L;
	L = (linkedList*)malloc(sizeof(linkedList));

	L->head = NULL;
	L->length = 0;
	
	return L;
}


void displayList(linkedList* L) {

	Node* p;
	p = L->head;

	if (p == NULL) {
		printf("The list is empty. Quit!\n");
	}
	else {
		printf("\nname    age   BMI\n");

		while (p != NULL) {

			printf("%s  %3d  %.1f\n", p->name, p->age, p->bmi);
			p = p->link;
		}
	}
}


/* 함수 형식은 아래와 같은 식으로 구현 가능함 */


void insertFirst(linkedList* L, Node* N) {
	N->link = L->head;
	L->head = N;
	L->length++;
}

void insertLastNode(linkedList* L, Node* N) {
	Node* temp;
	
	if (L->head == NULL) {
		L->head = N;
	}
	else {
		temp = L->head;
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = N;
	}
	L->length++;
}


Node* deleteNode(linkedList* L, Node* p) {
	Node* pre;
	if (L->head == NULL) return FALSE;
	if (p == NULL) return FALSE;
	pre = L->head;
	while (pre->link != p) {
		pre = pre->link;
		if (pre == NULL) return FALSE;
	}
	pre->link = p->link;
	free(p);
	L->length--;
	return TRUE;

}


void insert(linkedList* L, Node* pre, Node* N) {
	
	if (L->head == NULL) {
		N->link = NULL;
		L->head = N;
	}
	
	else {
		pre = L->head;
		while (pre->link != NULL)
			if ((N->age) >= (pre->link->age)) {
				pre = pre->link;
			}
			else {
				N->link = pre->link; 
				
				break;
			}
		
		
		pre->link = N;
	}
	L->length++;
}





int main(void)
{
	
	Node* crnt;
	FILE* fp;
	char buf[40];

	fp = fopen("patientdata.txt", "r");





	/*
		Q1: 리스트에 있는 각 노드의 데이터를 출력하기
	*/

	// list1 초기화
	linkedList* list1 = initList();

	// 파일을 읽어들여 순차적으로 노드 생성
	int i;
	for (i = 0; i < 3; i++) {
		fscanf(fp, "%s", buf); // skip the first line in the text file.
	}

	while ((fscanf(fp, "%s", buf)) != EOF) {

		Node* newNode;
		newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 생성

		// 새로운 노드에 데이터 저장
		strcpy(newNode->name, buf);
		fscanf(fp, "%d", &newNode->age);
		fscanf(fp, "%f", &newNode->bmi);

		// insertFirst 함수를 이 자리에 넣기.
		insertFirst(list1, newNode);
	}



	printf("\n1. 리스트에 있는 각 노드의 데이터를 출력하기 \n");

	displayList(list1);
	printf("\nlist1의 길이 = % d\n", list1->length);


	/*
		Q2: 먼저번 출력과 반대로 순서를 거꾸로 출력하기.
	*/

	printf("\n\n2. 리스트 순서를 거꾸로 출력하기 \n");

	// list2 초기화
	linkedList* list2 = initList();

	rewind(fp);

	for (i = 0; i < 3; i++) {
		fscanf(fp, "%s", buf); // skip the first line in the text file.
	}

	while ((fscanf(fp, "%s", buf)) != EOF) {

		Node* newNode;
		newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 생성

		// 새로운 노드에 데이터 저장
		strcpy(newNode->name, buf);
		fscanf(fp, "%d", &newNode->age);
		fscanf(fp, "%f", &newNode->bmi);
		newNode->link = NULL;
		// insertLastNode 함수를 이 자리에 넣기
		insertLastNode(list2, newNode);
	}

	displayList(list2);
	printf("\nlist2의 길이 = % d\n", list2->length);


	/*
		Q3: list1데이터에서 BMI가 25미만인 환자는 삭제한 후 리스트 각 노드 데이터 출력하기.
	*/

	printf("\n\n3. list1데이터에서 BMI가 25미만인 환자는 삭제한 후 리스트 각 노드 데이터 출력하기. \n");


	printf("\n 삭제 전 list1\n");
	displayList(list1);


	// 리스트에서 BMI가 25미만이 환자 삭제하도록 코딩하기. 
	Node* newNode;
	newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 생성

	// 새로운 노드에 데이터 저장
	strcpy(newNode->name, buf);
	fscanf(fp, "%d", &newNode->age);
	fscanf(fp, "%f", &newNode->bmi);
	
	for (crnt = list1->head; crnt != NULL;) {
		if (crnt->bmi < 25) {
			deleteNode(list1, crnt);
			crnt = list1->head;
		}
		else {
			crnt = crnt->link;
		}
	}


	printf("\n 삭제 후 list1\n");
	displayList(list1);
	printf("\n삭제 후 list1의 길이 = % d\n", list1->length);


	/*
		Q4: Age 오름차순으로 정렬한 리스트 출력하기.
	*/

	printf("\n\n4. Age 오름차순으로 정렬한 리스트 출력하기. \n");

	// list4 초기화
	linkedList* list4 = initList();

	rewind(fp);

	for (i = 0; i < 3; i++) {
		fscanf(fp, "%s", buf); // skip the first line in the text file.
	}

	while ((fscanf(fp, "%s", buf)) != EOF) {

		Node* newNode;
		
		newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 생성

		// 새로운 노드에 데이터 저장
		strcpy(newNode->name, buf);
		fscanf(fp, "%d", &newNode->age);
		fscanf(fp, "%f", &newNode->bmi);

		
		
		
		// Age 오름차순으로 정렬하도록 코딩하기.
		newNode->link = NULL;
		insert(list4, crnt, newNode);
			
			
		
		
		


		displayList(list4);

	}




	fclose(fp);



}

