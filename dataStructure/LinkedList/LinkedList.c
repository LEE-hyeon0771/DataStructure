#include<stdio.h>
#include<stdlib.h>
#include "Member.h"
#include "LinkedList.h"

static Node* AllocNode(void) {
	return calloc(1, sizeof(Node));
}
static void SetNode(Node* n, const Member* x, const Node* next) {
	n->data = *x;
	n->next = next;
}
void Initialize(List* list) {
	list->head = NULL;
	list->crnt = NULL;
}
Node* search(List* list, const Member* x, int compare(const Member* x, const Member* y)) {
	Node* ptr = list->head;
	while (ptr != NULL) {
		if (compare(&ptr->data, x) == 0) {      //키 값이 같은 경우
			list->crnt = ptr;
			return ptr;    //검색성공
		}
		ptr = ptr->next;  //다음 노드 선택
	}
	return NULL;   //검색실패
}
void InsertFront(List* list, const Member* x) {
	Node* ptr = list->head;
	list->head = list->crnt = AllocNode();
	SetNode(list->head, x, ptr);
}
void InsertRear(List* list, const Member* x) {
	if (list->head == NULL) {
		InsertFront(list, x);
	}
	else {
		Node* ptr = list->head;
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = list->crnt = AllocNode();
		SetNode(ptr->next,x, NULL);
	}
}
void RemoveFront(List* list) {
	if (list->head != NULL) {
		Node* ptr = list->head->next;    //두 번째 노드로 현재 ptr을 설정
		free(list->head);                //head 삭제
		list->head = list->crnt = ptr;   //새로운 머리 노드 만들어서 head에 넣어줌
	}
}
void RemoveRear(List* list) {
	if (list->head != NULL) {
		if ((list->head)->next == NULL) {      //노드가 1개만 있음
			RemoveFront(list);                 //머리 노드 삭제 
		}
		else {
			Node* ptr = list->head;
			Node* pre;
			while (ptr->next != NULL) {
				pre = ptr;                 //ptr : 꼬리 노드, pre : 꼬리 노드로 부터 두번째 노드
				ptr = ptr->next;
			}
			pre->next = NULL;
			free(ptr);
			list->crnt = pre;
		}
	}
}
void RemoveCurrent(List* list) {
	if (list->head != NULL) {
		if (list->crnt == list->head) {
			RemoveFront(list);
		}
		else {
			Node* ptr = list->head;
			while (ptr->next != list->crnt) {
				ptr = ptr->next;
			}
			ptr->next = list->crnt->next;
			free(list->crnt);
			list->crnt = ptr;
		}
	}
}
void Clear(List* list) {
	while (list->head != NULL) {
		RemoveFront(list);
	}
	list->crnt = NULL;
}
void PrintCurrent(const List* list) {
	if (list->crnt == NULL) {
		printf("선택한 노드가 없습니다.");
	}
	else {
		PrintMemeber(&list->crnt->data);
	}
}
void PrintLnCurrent(const List* list) {
	PrintCurrent(list);
	putchar('\n');
}
void Print(const List* list) {
	if (list->head == NULL) {
		puts("노드가 없습니다.");
	}
	else {
		Node* ptr = list->head;
		puts("[모두보기]");
		while (ptr != NULL) {
			PrintLnMemeber(&ptr->data);
			ptr = ptr->next;
		}
	}
}
void Terminate(List* list) {
	Clear(list);
}