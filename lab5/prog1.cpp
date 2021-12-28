#include <iostream>

extern "C" float SinIntegral(float A, float B, float e);
extern "C" int* Sort(int* array);

int main() {
	int command = 0;
	float A = 0, B = 0, e = 0;
	int size = 0;
	while (true) {
		std::cout << "Commands:\n" << "1. Ñalculation of the integral \n" << "2. Sorting an array \n" << "3. Exit" << std::endl;
		std::cout << "Enter command: ";
		std::cin >> command;
		if (command == 1) {
			std::cout << "Enter A, B, e" << std::endl;
			std::cin >> A >> B >> e;
			std::cout << "Integral value: " << SinIntegral(A, B, e) << std::endl;
		}
		else if (command == 2) {
			std::cout << "Enter array size" << std::endl;
			std::cin >> size;
			int* array = new int[size + 1];
			array[0] = size;
			std::cout << "Enter value" << std::endl;
			for (int i = 1; i <= size; i++)
				std::cin >> array[i];
			int* result = new int[size + 1];
			result = Sort(array);
			std::cout << "Sorting result: ";
			for (int i = 1; i <= size; i++)
				std::cout << result[i] << "\t";
			std::cout << std::endl;
			free(result);
			free(array);
		}
		else if (command == 3)
			break;
	}
}