#include <iostream>

class Test {
private:
	int test = 13;
public:
	int getTest() {
		return test;
	}
};

extern "C" {
	__declspec(dllexport) void addThreeNumbers(float* numbers){
		std::cout << numbers[0] + numbers[1] + numbers[2] << std::endl;
	}

	__declspec(dllexport) Test* getTestObject() {
		return new Test();
	}

	__declspec(dllexport) int getTest(Test* test) {
		return test->getTest();
	}
}
