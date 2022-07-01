#include<stdio.h>
#include<stdlib.h>

int search1(const int a[], int n, int key) {       //무한 루프를 이용한 while문으로 구현한 선형 검색법
	int i = 0;
	while (1) {
		if (i == n) {
			return -1;
		}
		if (a[i] == key) {
			return i;
		}
		i++;
	}
}

int search2(const int a[], int n, int key) {      //for문으로 구현한 선형 검색법
	for(int i = 0; i < n; i++){
		if (a[i] == key) {
			return i;
		}
		return -1;
	}
}

int search3(int a[], int n, int key) {                 //보초법을 추가한 while문 선형 검색법
	int i = 0;
	a[n] = key;       //마지막 자리에 보초를 추가
	while (1) {
		if (a[i] == key) {
			break;
		}
		i++;
	}
	return i == n ? -1 : i;
}

int main() {
	int i, nx, ky, idx;
	int* x;
	puts("선형 검색");
	printf("요소 개수 : ");
	scanf_s("%d", &nx);
	x = calloc(nx, sizeof(int));
	for (i = 0; i < nx; i++) {
		printf("x[%d] : ", i);
		scanf_s("%d", &x[i]);
	}
	printf("검색값 : ");
	scanf_s("%d", &ky);
	idx = search1(x, nx, ky);
	idx = search2(x, nx, ky);
	if (idx == -1) {
		puts("검색에 실패했습니다.");
	}
	else {
		printf("%d(은)는 x[%d]에 있습니다.\n", ky, idx);
	}
	free(x);

	return 0;
}