/*

  ����Ž�� �˰���� ����Ž�� �˰����� ���� ��
  ���� 2021247013
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>


#define len 100000000L


int LSearch(int list[], int n, int targetnum) {
	int i;
	
	for (i = 0; i < n; i++) {

		if (targetnum == list[i]) {
			return i;
		}
	}
	return -1;
}

int BSearch(int list[], int n, int targetnum) {
	int left = 0;
	int right = n - 1;
	int mid;
	
	while (left <= right) {
		
		mid = (left + right) / 2;
		if (targetnum == list[mid]) {
			return mid;
		}
		else {
			if (targetnum < list[mid]) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
	}
	return -1;
}


int main(void) {
	
	int target;
	int index;
	clock_t start, finish;
	float time_elapsed_LS, time_elapsed_BS;

	int list[len];
	for (int i = 0; i < len; i++) {
		list[i] = i;
	}
	
	// ã���� �ϴ� ���� �Է��Ѵ�. 
	printf("\nEnter a target number (try the worst case): ");
	scanf("%d", &target);

	printf("target = %d\n", target);

	// linear search (����Ž��) ���� 
	
	start = clock();
	index = LSearch(list, len, target);
	finish = clock();
	time_elapsed_LS = float(finish - start) / CLOCKS_PER_SEC;
	
	printf("\n����Ž��: target %d�� ��ġ �ε������� %d�̴�. �ҿ�ð��� %f���̴�", target, index, time_elapsed_LS);

	// binary search (����Ž��) ���� 
	
	start = clock();
	index = BSearch(list, len, target);
	finish = clock();
	time_elapsed_BS = float(finish - start)/CLOCKS_PER_SEC;
	
	printf("\n����Ž��: target %d�� ��ġ �ε������� %d�̴�. �ҿ�ð��� %f���̴�", target, index, time_elapsed_BS);

	return 0;
}



