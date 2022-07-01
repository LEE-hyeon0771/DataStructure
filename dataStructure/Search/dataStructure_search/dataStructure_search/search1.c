#include<stdio.h>
#include<stdlib.h>

int search1(const int a[], int n, int key) {       //���� ������ �̿��� while������ ������ ���� �˻���
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

int search2(const int a[], int n, int key) {      //for������ ������ ���� �˻���
	for(int i = 0; i < n; i++){
		if (a[i] == key) {
			return i;
		}
		return -1;
	}
}

int search3(int a[], int n, int key) {                 //���ʹ��� �߰��� while�� ���� �˻���
	int i = 0;
	a[n] = key;       //������ �ڸ��� ���ʸ� �߰�
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
	puts("���� �˻�");
	printf("��� ���� : ");
	scanf_s("%d", &nx);
	x = calloc(nx, sizeof(int));
	for (i = 0; i < nx; i++) {
		printf("x[%d] : ", i);
		scanf_s("%d", &x[i]);
	}
	printf("�˻��� : ");
	scanf_s("%d", &ky);
	idx = search1(x, nx, ky);
	idx = search2(x, nx, ky);
	if (idx == -1) {
		puts("�˻��� �����߽��ϴ�.");
	}
	else {
		printf("%d(��)�� x[%d]�� �ֽ��ϴ�.\n", ky, idx);
	}
	free(x);

	return 0;
}