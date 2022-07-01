#ifndef ___IntQueue
#define ___IntQueue

typedef struct {
	int max;      //큐의 최대 용량
	int num;      //현재의 요소 개수
	int front;    //프런트(맨 앞)
	int rear;     //리어(맨 뒤)
	int* que;     //큐 배열의 맨 앞 요소에 대한 포인터
}IntQueue;

int Initialize(IntQueue* q, int max);
int Enque(IntQueue* q, int x);
int Deque(IntQueue* q, int* x);
int Peek(const IntQueue* q, int* x);
void Clear(IntQueue* q);
int Capacity(const IntQueue* q);
int Size(const IntQueue* q);
int IsEmpty(const IntQueue* q);
int IsFull(const IntQueue* q);
int Search(const IntQueue* q, int x);
void Print(const IntQueue* q);
void Terminate(IntQueue* q);
#endif