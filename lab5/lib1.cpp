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
		result += (x2 - x1) * (sin(x1) + sin(x2)) / 2;
	}
	return result;
}

int* Sort(int* array) {
	int n = array[0];
	int* result = new int[n + 1];
	for (int i = 0; i <= n; i++)
		result[i] = array[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < n; j++)
			if (result[j] > result[j + 1]) {
				int temporary = result[j];
				result[j] = result[j + 1];
				result[j + 1] = temporary;
			}
	return result;
}