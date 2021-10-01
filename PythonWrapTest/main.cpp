#include <iostream>

extern "C" {
	__declspec(dllexport) void addThreeNumbers(float* numbers){
		std::cout << numbers[0] + numbers[1] + numbers[2] << std::endl;
	}
}