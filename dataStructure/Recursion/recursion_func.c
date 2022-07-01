#include<stdio.h>

int Fibo(int n) {
	if (n == 1) {
		return 0;
	}
	else if (n == 2) {
		return 1;
	}
	else {
		return Fibo(n - 1) + Fibo(n - 2);
	}
}

int BSearchRecursive(int arr[], int first, int last, int target) {
	int mid;
	if (first > last) {
		return -1;
	}
	mid = (first + last) / 2;
	if (arr[mid] == target) {
		return mid;
	}
	else if (arr[mid] > target) {
		return BSearchRecursive(arr, first, mid - 1, target);
	}
	else {
		return BSearchRecursive(arr, mid + 1, last, target);
	}
}

void HanoiTower(int n, char from, char tmp, char to) {
	if (n == 1) {
		printf("Disk1: %c -> %c\n", from, to);
	}
	else {
		HanoiTower(n - 1, from, to, tmp); //from : A, to : C, tmp : B
		printf("Disk%d: %c -> %c\n", n, from, to);
		HanoiTower(n - 1, tmp, from, to);
	}
}