#include <iostream>
#include <dlfcn.h>

int main() {
	std::cout << "Enter library number: ";
	int library_number = 0;
	std::cin >> library_number;
	if ((library_number != 1) && (library_number != 2)) {
		std::cout << "This library does not exist" << std::endl;
		exit(1);
	}
	--library_number;
	const char* libraries[] = { "./libd1.so","./libd2.so" };
	void* library_handle = dlopen(libraries[library_number], RTLD_LAZY);
	if (!library_handle) {
		std::cout << dlerror() << std::endl;
		exit(1);
	}
	
	float (*SinIntegral)(float A, float B, float e);
	int* (*Sort)(int* array);
	SinIntegral = (float(*)(float, float, float))dlsym(library_handle, "SinIntegral");
	Sort = (int* (*)(int*))dlsym(library_handle, "Sort");

	int command = 0;
	float A = 0, B = 0, e = 0;
	int size = 0;
	while (true) {
		std::cout << std::endl;
		std::cout << "Commands:\n" << "0\n" << "1. Ñalculation of the integral \n" << "2. Sorting an array \n" << "3. Exit" << std::endl;
		std::cout << "Enter command: ";
		std::cin >> command;
		if (command == 0) {
			dlclose(library_handle);
			library_number = (library_number + 1) % 2;
			library_handle = dlopen(libraries[library_number], RTLD_LAZY);
			if (!library_handle) {
				std::cout << dlerror() << std::endl;
				exit(1);
			}
			SinIntegral = (float(*)(float, float, float))dlsym(library_handle, "SinIntegral");
			Sort = (int* (*)(int*))dlsym(library_handle, "Sort");
			std::cout << "Changed successfully" << std::endl;
		}
		else if (command == 1) {
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
		else if (command == 3) {
			dlclose(library_handle);
			break;
		}
	}
}