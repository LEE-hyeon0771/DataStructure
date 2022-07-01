//�������ｺ�ɾ��к� 2021247013 ����


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

	// �ʱ�ȭ(Clear)
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			mem[i][k] = 0;
		}
	}

	return mem;
}


int find_neighbor_vertex(int v, int nverts, int** cost, int visited[]) {

	// ��� v�� ���� ��� �߿� ���� �湮 ���� ��� ã��. ������ -1����. 

	int w, a;

	for (w = 0; w < nverts; w++) {

		if (visited[w])
			continue;
		else {
			a = cost[v][w];
			if (a > 0 && a != 10000) { // v�� �ٸ��� ����� ����.
				return w;
			}
		}
	}

	return -1;  // ���� ������ ����. �ִ��� ��� �湮��.
}


int checkDFS(int v, int nverts, int** cost) {

	// Depth First Search (DFS) ���� �켱 Ž�� �˰����� �����Ͻÿ�.

	int is_G_connected = 0;

	Stack* S = createStack();

	int visited[MAX_VERTEX] = { 0 };
	int i, count = 0;
	
	visited[v] = 1; // ���� v �湮 ǥ��.
	push(S, v);
	
	// DFS �˰��� ����.  find_neighbor_vertex() �Լ� Ȱ���Ͽ� ���� ��� ã��.
	
	printf("\n\n���� 0���� �����ϴ� DFS ��ȸ ����: ");
	printf("%d ", v);  //���� ������ ǥ��
	while (!isEmpty(S)) {
		
		v = pop(S);
		i = find_neighbor_vertex(v, nverts, cost, visited);
		
		while (i != -1) { //���������� �����ϸ�
			
			if (visited[i] == 0) {  //i�� �湮���� �ʾ�����
				push(S, v); 
				visited[i] = 1;   //push ���� ���ְ� �湮��
				
				printf("%d ", i);   //�湮�� ��θ� ���
				v = i;
				i = find_neighbor_vertex(v, nverts, cost, visited);
				
			}
		}
	}
	for (i = 0; i < nverts; i++) {
			if (visited[i] == 1)   //�湮�� ��쿡 count++ ������
				count++;
	};
	if (count == nverts) is_G_connected = 1;    //�湮�� count�� nverts(�ִ�)���� �����ϰ� �Ǹ� ��� ����Ǿ����Ƿ� 1 �־���
	                                            //true�� �ν��ϰ� �׷����� ������� ���
	else is_G_connected = 0;    //false�� �׷����� ������� ���� ���
	
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

	// ����ġ�� ���� ���� ��� ����. 

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
	int* S = (int*)malloc(nverts * sizeof(int)); // ���� S. 0�� ������ S�� ������ 1�� ������ ��Ÿ��.
	int* path_mincost = (int*)malloc(nverts * sizeof(int)); // �ִܰ�ο� ���� ������������ ���������� �湮�� ������ ����.

	// ���ͽ�Ʈ�� �˰��� ����. select_next()�Լ� Ȱ��.
	for (int i = 0; i < nverts; i++) {
		S[i] = 0;
	}
	S[start_index] = 1;  // {1,0,0,0,0} ������ stack�� ������
	for (int i = 0; i < nverts; i++) {
		dist[i] = cost[start_index][i];   //����ġ �迭 : dist

		if (cost[start_index][i] != INF)
			path_mincost[i] = start_index;     //��� ����ġ �迭�� ���� �ε��� ����(����)
		else
			path_mincost[i] = NULL;     //���Ѵ�� ����ġ NULL
	}

	for (int i = 0; ; i++) {
		int u = select_next(dist, S, nverts);   //����ġ�� ���� ���� ��� ����
		if (u == -1)
			break;       //u�� �湮�� �� ������ -1 ������ break
		else
			S[u] = 1;    //�湮�ϸ� 1

		for (int w = 0; w < nverts; w++) {
			if (S[w] != 1 && (dist[u] + cost[u][w] < dist[w])) {
				dist[w] = dist[u] + cost[u][w];       //�湮�� �� ���ų� ����ġ�� �� ���� ���̸� ���� ������ ����ġ ����
				path_mincost[w] = u;         //����ġ�� ���� ���� ��带 �����ؼ� �Է�        
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
	printf("���: \n");

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

	fp1 = fopen(argv[1], "r");  // ���� ���� ����
	ind_vert = 0;

	while ((fgets(buf, 200, fp1)) != NULL) {
		strcpy(vert_city[ind_vert], buf);
		ind_vert++;
	}

	nverts = ind_vert;
	fclose(fp1);

	for (i = 0; i < nverts; i++) {
		printf("����: %2d\t ���� �̸�: %s\n", i, vert_city[i]);
	}

	printf("���� ���� = %d\n", nverts);

	fp2 = fopen(argv[2], "r");  // cost ���� ����

	cost_matrix = malloc2D(nverts, nverts); // 2���� ����� ����� �ʱ�ȭ�Ѵ�.

	count = 0;
	while ((fscanf(fp2, "%d", &weight)) != EOF) {
		row = count / nverts;
		col = count % nverts;
		cost_matrix[row][col] = weight; // �� ������ ������� ������ weight�� 10000���� ������.
		count++;
	}
	fclose(fp2);

	printf("\n���� 0�� �������� �ϴ� cost: ");
	for (i = 0; i < nverts; i++) {
		printf("%d ", cost_matrix[0][i]);
	}


	// DFS �˰����� �ۼ��Ͽ� �׷����� ����Ǿ� �ִ��� Ȯ���ϱ�.
	
	
	is_G_connected = checkDFS(0, nverts, cost_matrix);
	
	if (is_G_connected) {
		printf("\t�׷����� �����");
	}
	else {
		printf("\t�׷����� ���� �� ��");
	}

	// �� �׷����� ���� Dijkstra algorithm�� �̿��Ͽ� �� ���� ������ �ּҰ�θ� ã���ش�. 

	printf("\n\n��߰� ���� ���� �ε����� ���� �Է��Ͻÿ�. �ε��� ����(0 - %d): \n", nverts - 1);
	scanf("%d %d", &start_index, &end_index);
	
	
	//shortest_path_D(start_index, end_index, nverts, cost_matrix, vert_city);
	
	minimum_cost = shortest_path_D(start_index, end_index, nverts, cost_matrix, vert_city);

	printf("\n��� : %s", vert_city[start_index]);
	printf("\n���� : %s", vert_city[end_index]);
	printf("\n�ִ� ��� �ּ� ���: %d\n", minimum_cost);

	free(cost_matrix);

	return 0;
}