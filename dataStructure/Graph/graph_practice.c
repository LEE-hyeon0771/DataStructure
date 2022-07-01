#pragma warning(disable:4996)
//#define _CRT_SECUER_NO_WARNINGS
#define MAX_VERTEX 7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int stack[MAX_VERTEX];
	int top;
} Stack;

Stack* createStack() {

	Stack* S = (Stack*)malloc(sizeof(Stack));

	S->top = -1;

	return S;
}

int isEmpty(Stack* S) {

	return S->top == -1;
}

void push(Stack* S, int x) {

	S->top += 1;
	S->stack[S->top] = x;
}

int pop(Stack* S) {

	int e = S->stack[S->top];
	S->top -= 1;
	return e;
}

int find_neighbor_vertex(int v, int nverts, int matrix[][MAX_VERTEX], int visited[]) {

	// ��� v�� ���� ��� �߿� ���� �湮 ���� ��� ã��. ������ -1����. 

	int w, a;

	for (w = 0; w < nverts; w++) {

		if (visited[w])
			continue;
		else {
			a = matrix[v][w];
			if (a == 1) { // v�� �ٸ��� ����� ����.
				return w;
			}
		}
	}

	return -1;  // ���� ������ ����. �ִ��� ��� �湮��.
}


int DFS(int v, int nverts, int matrix[][MAX_VERTEX], char* vert_city) {

	// Depth First Search (DFS) ���� �켱 Ž�� �˰����� �����Ͻÿ�.

	Stack* S = createStack();

	int visited[MAX_VERTEX] = { 0 };
	int w = 0;

	visited[v] = 1; // ���� v �湮 ǥ��.
	push(S, v);
	printf("%c\n", vert_city[v]);

	// DFS �˰��� ����.  find_neighbor_vertex() �Լ� Ȱ���Ͽ� ���� ��� ã��.
	while (!isEmpty(S)) {
		v = pop(S);
		w = find_neighbor_vertex(v, MAX_VERTEX, matrix, visited);
			while (w != -1) { //w=-1�̸� ���������� ���� ��
				if (visited[w] == 0) {
					push(S, v);
					visited[w] = 1;
					printf("%c\n", vert_city[w]);
					v = w;
					w = find_neighbor_vertex(v, MAX_VERTEX, matrix, visited);
				}
			}
	}
	return 0;
}


int main(int argc, char* argv[])
{
	char vert_city[MAX_VERTEX] = {'A','B','C','D','E','F','G'};
	int matrix[MAX_VERTEX][MAX_VERTEX] = {
	  { 0,1,1,0,0,0,0},
	  { 1,0,0,0,1,0,0},
	  { 1,0,0,0,0,1,0},
	  { 0,0,0,0,1,0,0},
	  { 0,1,0,1,0,0,1},
	  { 0,0,1,0,0,0,0},
	  { 0,0,0,0,1,0,0}
	};

	DFS(2, MAX_VERTEX, matrix, vert_city);

	return 0;
}