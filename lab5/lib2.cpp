#include <cmath>

extern "C" float SinIntegral(float A, float B, float e);
extern "C" int* Sort(int* array);

float SinIntegral(float A, float B, float e) {
	float result = 0;
	float x1 = 0;
	float x2 = 0;
	for (float step = A; step + e < B; step += e) {
		x1 = step;
		if (step + e < B)
			x2 = step + e;
		else
			x2 = B;
		result += (x2 - x1) * sin(x1) + (x2 - x1) * (sin(x2) - sin(x1)) / 2;
	}
	return result;
}

void quicksort(int* array, int first, int last) {
	int middle = array[(first + last) / 2];
	int temporary;
	int i = first;
	int j = last;
	while (i <= j) {
		while (array[i] < middle) i++;
		while (array[j] > middle) j--;
		if (i <= j) {
			if (array[i] > array[j]) {
				int temporary = array[i];
				array[i] = array[j];
				array[j] = temporary;
			}
			i++;
			j--;
		}
	}
	if (i < last)
		quicksort(array, i, last);
	if (first < j)
		quicksort(array, first, j);
}

int* Sort(int* array) {
	int n = array[0];
	int* result = new int[n + 1];
	for (int i = 0; i <= n; i++)
		result[i] = array[i];
	quicksort(result, 1, n);
	return result;
}