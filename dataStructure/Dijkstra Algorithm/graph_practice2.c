#pragma warning(disable:4996)
//#define _CRT_SECUER_NO_WARNINGS
#define MAX_VERTEX 5
#define INF 999999
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int shortest_path_D(int start_index, int end_index, int nverts, int cost[][MAX_VERTEX], char vert_city[MAX_VERTEX][100]) {
	/*
	* Dijkstra algorithm
	*/

	int minimum_cost = 100000;
	int path_count = 0;
	int dist[MAX_VERTEX];
	int S[MAX_VERTEX];				// 집합 S. 0은 정점이 S에 없음을 1은 있음을 나타냄.
	int path_mincost[MAX_VERTEX];	// 최단경로에 대해 시작정점부터 끝정점까지 방문한 정점들 저장.

	// 다익스트라 알고리즘 구현. select_next()함수 활용.
	// =============== init. ===============
	for (int i = 0; i < nverts; i++)
		S[i] = 0;

	S[start_index] = 1;

	for (int i = 0; i < nverts; i++)
	{
		dist[i] = cost[start_index][i];

		if (cost[start_index][i] != INF)
			path_mincost[i] = start_index;
		else
			path_mincost[i] = NULL;
	}

	// =============== re. ===============
	for (int i = 0; ; i = i + 1)
	{
		int u = select_next(dist, S, nverts);
		if (u == -1)
			break;    //u가 방문할 곳이 없으면 -1을 뱉음
		else
			S[u] = 1;  //방문하면 1

		for (int w = 0; w < nverts; w++)
		{
			if (S[w] != 1 && (dist[u] + cost[u][w] < dist[w])) {
				dist[w] = dist[u] + cost[u][w];
				path_mincost[w] = u;
			}
		}
	}

	minimum_cost = dist[end_index];
	return minimum_cost;
}



void main(int argc, char* argv[])
{
	char vert_city[MAX_VERTEX] = { 'A', 'B', 'C', 'D', 'E' };
	int cost_matrix[MAX_VERTEX][MAX_VERTEX] = {
	  {0, 10, 5, INF, INF},
	  {INF, 0, 2, 1, INF},
	  {INF, 3, 0, 9, 2},
	  {INF, INF, INF, 0, 4},
	  {7, INF, INF, 6, 0}
		
	};
	int cost = shortest_path_D(0, 3, MAX_VERTEX, cost_matrix, vert_city);
	printf("%c to %c cost : %d\n", vert_city[0], vert_city[3], cost);

	return;
}