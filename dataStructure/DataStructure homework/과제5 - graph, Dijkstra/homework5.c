//디지털헬스케어학부 2021247013 이현


#pragma warning(disable:4996)
//#define _CRT_SECUER_NO_WARNINGS
#define MAX_VERTEX 140
#define INF 999999
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

int** malloc2D(int  h, int w) {
	int** mem;
	mem = (int**)malloc(h * sizeof(int*));
	for (int i = 0; i < h; i++)
		mem[i] = (int*)malloc(w * sizeof(int));

	// 초기화(Clear)
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			mem[i][k] = 0;
		}
	}

	return mem;
}


int find_neighbor_vertex(int v, int nverts, int** cost, int visited[]) {

	// 노드 v의 인접 노드 중에 아직 방문 안한 노드 찾기. 없으면 -1리턴. 

	int w, a;

	for (w = 0; w < nverts; w++) {

		if (visited[w])
			continue;
		else {
			a = cost[v][w];
			if (a > 0 && a != 10000) { // v랑 다르며 연결된 정점.
				return w;
			}
		}
	}

	return -1;  // 인접 정점이 없음. 있더라도 모두 방문함.
}


int checkDFS(int v, int nverts, int** cost) {

	// Depth First Search (DFS) 깊이 우선 탐색 알고리즘을 구현하시오.

	int is_G_connected = 0;

	Stack* S = createStack();

	int visited[MAX_VERTEX] = { 0 };
	int i, count = 0;
	
	visited[v] = 1; // 정점 v 방문 표시.
	push(S, v);
	
	// DFS 알고리즘 구현.  find_neighbor_vertex() 함수 활용하여 다음 노드 찾기.
	
	printf("\n\n정점 0부터 시작하는 DFS 순회 순서: ");
	printf("%d ", v);  //시작 정점을 표시
	while (!isEmpty(S)) {
		
		v = pop(S);
		i = find_neighbor_vertex(v, nverts, cost, visited);
		
		while (i != -1) { //인접정점이 존재하면
			
			if (visited[i] == 0) {  //i에 방문하지 않았으면
				push(S, v); 
				visited[i] = 1;   //push 먼저 해주고 방문함
				
				printf("%d ", i);   //방문한 경로를 출력
				v = i;
				i = find_neighbor_vertex(v, nverts, cost, visited);
				
			}
		}
	}
	for (i = 0; i < nverts; i++) {
			if (visited[i] == 1)   //방문된 경우에 count++ 시켜줌
				count++;
	};
	if (count == nverts) is_G_connected = 1;    //방문한 count가 nverts(최대)값에 도달하게 되면 모두 연결되었으므로 1 넣어줌
	                                            //true로 인식하고 그래프가 연결됨을 출력
	else is_G_connected = 0;    //false면 그래프가 연결되지 않음 출력
	
	return is_G_connected;
}



void disp_progress(int* dist, int* S, int nverts) {

	static int step = 1;
	printf("\n[ %2d ] Distance: ", step++);
	for (int i = 0; i < nverts; i++) {
		printf("%d ", dist[i]);
	}

}

int select_next(int* dist, int* S, int nverts) {

	// 가중치가 가장 낮은 노드 선택. 

	int i, min, min_index;

	min = 100000;
	min_index = -1;

	for (i = 0; i < nverts; i++) {
		if (dist[i] < min && !S[i]) {
			min = dist[i];
			min_index = i;
		}
	}

	return min_index;
}


int shortest_path_D(int start_index, int end_index, int nverts, int** cost, char vert_city[MAX_VERTEX][100]) {
	/*
	* Dijkstra algorithm
	*/

	int minimum_cost = 100000;
	int path_count = 0;
	int* dist = (int*)malloc(nverts * sizeof(int));
	int* S = (int*)malloc(nverts * sizeof(int)); // 집합 S. 0은 정점이 S에 없음을 1은 있음을 나타냄.
	int* path_mincost = (int*)malloc(nverts * sizeof(int)); // 최단경로에 대해 시작정점부터 끝정점까지 방문한 정점들 저장.

	// 다익스트라 알고리즘 구현. select_next()함수 활용.
	for (int i = 0; i < nverts; i++) {
		S[i] = 0;
	}
	S[start_index] = 1;  // {1,0,0,0,0} 식으로 stack을 구현함
	for (int i = 0; i < nverts; i++) {
		dist[i] = cost[start_index][i];   //가중치 배열 : dist

		if (cost[start_index][i] != INF)
			path_mincost[i] = start_index;     //경로 가중치 배열에 시작 인덱스 저장(수정)
		else
			path_mincost[i] = NULL;     //무한대면 가중치 NULL
	}

	for (int i = 0; ; i++) {
		int u = select_next(dist, S, nverts);   //가중치가 가장 낮은 노드 선택
		if (u == -1)
			break;       //u가 방문할 곳 없으면 -1 나오고 break
		else
			S[u] = 1;    //방문하면 1

		for (int w = 0; w < nverts; w++) {
			if (S[w] != 1 && (dist[u] + cost[u][w] < dist[w])) {
				dist[w] = dist[u] + cost[u][w];       //방문할 곳 없거나 가중치가 더 작은 값이면 작은 값으로 가중치 수정
				path_mincost[w] = u;         //가중치가 가장 낮은 노드를 수정해서 입력        
			}

		}
	}
	int index = end_index;
	int arr[MAX_VERTEX] = {0};
	int m = 0;
	int i = 1;
		
	while (index != start_index) {

		index = path_mincost[index];
		m = MAX_VERTEX - i - 1;
		arr[m] = index;

		i++;
	}
	printf("경로: \n");

	int count = 1;
	for (int i = m; i < MAX_VERTEX - 1; i++) {
		printf("%d: %s\n", count++, vert_city[arr[i]]);
	}
	printf("%d: %s\n", count++, vert_city[end_index]);
	
	minimum_cost = dist[end_index];

	free(dist);
	free(S);
	free(path_mincost);

	return minimum_cost;
}



int main(int argc, char* argv[])
{
	FILE* fp1, * fp2;
	char buf[200];
	int i;
	int count;

	int nverts = 0; // number of vertices

	int ind_vert;
	char vert_city[MAX_VERTEX][100] = { "abc" };

	int weight = 0;

	int row, col;

	int** cost_matrix = NULL;
	int is_G_connected;
	int start_index, end_index;
	int minimum_cost;

	fp1 = fopen(argv[1], "r");  // 정점 파일 오픈
	ind_vert = 0;

	while ((fgets(buf, 200, fp1)) != NULL) {
		strcpy(vert_city[ind_vert], buf);
		ind_vert++;
	}

	nverts = ind_vert;
	fclose(fp1);

	for (i = 0; i < nverts; i++) {
		printf("정점: %2d\t 도시 이름: %s\n", i, vert_city[i]);
	}

	printf("정점 개수 = %d\n", nverts);

	fp2 = fopen(argv[2], "r");  // cost 파일 오픈

	cost_matrix = malloc2D(nverts, nverts); // 2차원 행렬을 만들고 초기화한다.

	count = 0;
	while ((fscanf(fp2, "%d", &weight)) != EOF) {
		row = count / nverts;
		col = count % nverts;
		cost_matrix[row][col] = weight; // 두 정점이 연결되지 않으면 weight를 10000으로 설정함.
		count++;
	}
	fclose(fp2);

	printf("\n정점 0을 기준으로 하는 cost: ");
	for (i = 0; i < nverts; i++) {
		printf("%d ", cost_matrix[0][i]);
	}


	// DFS 알고리즘을 작성하여 그래프가 연결되어 있는지 확인하기.
	
	
	is_G_connected = checkDFS(0, nverts, cost_matrix);
	
	if (is_G_connected) {
		printf("\t그래프는 연결됨");
	}
	else {
		printf("\t그래프는 연결 안 됨");
	}

	// 이 그래프에 대해 Dijkstra algorithm을 이용하여 두 정점 사이의 최소경로를 찾아준다. 

	printf("\n\n출발과 도착 정점 인덱스를 각각 입력하시오. 인덱스 범위(0 - %d): \n", nverts - 1);
	scanf("%d %d", &start_index, &end_index);
	
	
	//shortest_path_D(start_index, end_index, nverts, cost_matrix, vert_city);
	
	minimum_cost = shortest_path_D(start_index, end_index, nverts, cost_matrix, vert_city);

	printf("\n출발 : %s", vert_city[start_index]);
	printf("\n도착 : %s", vert_city[end_index]);
	printf("\n최단 경로 최소 비용: %d\n", minimum_cost);

	free(cost_matrix);

	return 0;
}