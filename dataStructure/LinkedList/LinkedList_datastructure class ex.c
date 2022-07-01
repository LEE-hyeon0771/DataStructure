#include<stdio.h>

//노드 구조체
typedef int element;
typedef struct ListNode {
	element data;            //리스트 노드의 데이터 필드
	struct ListNode* link;   //리스트 노드의 Link 필드
}listNode;

//head 구조체
typedef struct LinkedList {
	listNode* head;          //리스트의 첫 번째 항목(head 머리 부분)
	int length;              //리스트의 항목 개수
}linkedList;

//공백리스트 생성
linkedList* initList(linkedList* L) {
	L = (linkedList*)malloc(sizeof(linkedList));
	L->head = NULL;
	L->length = 0;
	return L;
}

int getLength(linkedList* L) {
	return L->length;
}

//검색
listNode* search(linkedList* L, element x) {
	listNode* temp = L->head;
	while (temp != NULL) {        //head가 비어있지 않으면
		if (temp->data == x) {      //검색값을 찾으면
			return temp;            //그 값 반환
		}
		else {
			temp = temp->link;      //아니면 다음 링크로 temp이동
		}
	}
	return temp;                //head가 비어있으면 그대로 출력 
}


//삽입
void insert(linkedList* L,listNode* pre, element x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;

	if (L->head == NULL) {           //head가 Null이면
		newNode->link = NULL;        //새 노드 링크가 Null일거고
		L->head = newNode;           //Null인 head에 새 노드를 넣어줌  -> 공백 리스트에 담는 경우
	}
	else if (pre == NULL) {          //노드가 Null이면
		newNode->link = L->head;     //새 노드 링크를 head로 해주고
		L->head = newNode;           //head에다가 새 노드를 담아준다.  -> 맨 앞 노드로 삽입할 경우
	}
	else {
		newNode->link = pre->link;   //새 노드 링크를 이전 링크로 해주고
		pre->link = newNode;         //그 이전 링크가 된 새 노드 링크에 다음 새 노드를 담아준다. -> 리스트 중간에 삽입할 경우
	}
	L->length++;  //길이를 늘려가줘야 다음 노드와 이어져서 LinkedList가 계속 갈 수 있음
}

//맨 앞 노드로 삽입할 경우만의 함수
void insertFirst(linkedList* L, element x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;
	newNode->link = L->head;
	L->head = newNode;
	L->length++;
}

//마지막에 삽입할 경우만의 함수
void insertLastNode(linkedList* L, element x) {
	listNode* newNode, *temp;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;
	newNode->link = NULL;

	if (L->head == NULL) {
		L->head = newNode;        //공백리스트에 삽입 -> head에 새 노드 담아준다.
	}
	else {
		temp = L->head;
		while (temp->link != NULL) {           //링크가 NULL이 아니라는건 앞에 값이 무조건 있다는 뜻
			temp = temp->link;                 //NULL이 아닐때 link를 계속 넣어주게 되면 결국 맨 마지막 노드 부분까지 반복되서 지나감
		}
		temp->link = newNode;          //맨 마지막 링크 부분에 새 노드를 넣음
	}
	L->length++;
}

//삭제
int deleteNode(linkedList* L, listNode* p) {      //p는 삭제할 노드
	listNode* pre;      //pre는 삭제할 노드의 앞 노드

	if (L->head == NULL)          //공백리스트인 경우
		return 0;                 //false
	if (p == NULL)                //listNode에 노드가 없는 경우
		return 0;                 //false
	pre = L->head;
	while (pre->link != p) {         //pre에 담긴 link가 p에 담긴 링크와 다르면
		pre = pre->link;             //pre에 pre에 담긴 링크를 넣어줌  ->  삭제할 이전 노드 찾기
		if (pre == NULL) {           //만약에 pre가 없으면 삭제할 노드가 없는 것이므로 false
			return 0;
		}
	}
	pre->link = p->link;             //pre링크에 p링크를 넣어줌 -> 앞노드의 링크 필드에 삭제할 노드의 링크 필드값을 저장
	free(p);                         //삭제할 노드 p의 메모리 값을 해제  ->  삭제

	L->length--;    //중요!!!  삽입은 위로 올라가면서 밀었지만, 삭제는 위에서 아래로 내려오면서 하나씩 줄여야함.
	return 1;
}


//데이터 출력
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