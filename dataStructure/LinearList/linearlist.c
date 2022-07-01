//LinearList  -> Array사용
//삽입과 삭제 시 오버헤드 항목의 개수가 제한, 메모리 소모가 커서 삽입, 삭제에는 비효율적

#include<stdio.h>
#define MAX_SIZE 1000

typedef int element;
typedef struct {                //List를 구조체로 정의
	int list[MAX_SIZE];
	int length;
}ArrayListType;

void init(ArrayListType* L) {          //리스트 초기화
	L->length = 0;
}

int isEmpty(ArrayListType* L) {        //리스트가 비어있을 때
	return L->length == 0;
}

int isFull(ArrayListType* L) {         //리스트가 가득차 있을 때
	return L->length == MAX_SIZE; 
}

//삽입 함수 구현
void insert(ArrayListType* L, int pos, element item) {
	int i;
	if (isFull(L)) {
		error("List is Full!");
	}
	else if ((pos < 0) || (pos > L->length)) {
		error("Index Error");
	}
	else {
		for (i = (L->length - 1); i >= pos; i--) {   //큰 인덱스 부터 작은 인덱스로 내려가면서 빈자리를 만들어줌
 			L->list[i + 1] = L->list[i];             //다음 인덱스에 현재 인덱스 값을 넣으면서 중간에 빈자리 형성
		}
		L->list[pos] = item;    //pos는 비어있는 삽입자리 : item 값을 넣어줌
		L->length++;            //길이는 늘어나야함
	}
}

//삭제 함수 구현
void delete(ArrayListType* L, int pos, element item) {
	int i;
	if (isEmpty(L)) {
		error("List is Empty!");
	}
	else if ((pos < 0) || (pos > L->length)) {
		error("Index Error");
	}
	else {
		item = L->list[pos];                         //삭제 위치의 요소값 반환을 위해 저장
		for (i = pos; i < (L->length - 1); i++) {    //pos부터 length-1인덱스 직전까지 증가시키면서 조사해서 칸이 줄어들어야함
			L->list[i] = L->list[i + 1];
		}
		L->length--;                                 //길이는 줄어들어야함
		return item;
	}
}