#include <iostream>
#include <vector>

class Test {
private:
	int test = 13;
public:
	int getTest() {
		return test;
	}
};

std::vector<Test*> tests;

#define DLLEXPORT __declspec(dllexport)

extern "C" {
	DLLEXPORT void addThreeNumbers(float* numbers){
		std::cout << numbers[0] + numbers[1] + numbers[2] << std::endl;
	}

	DLLEXPORT Test* getTestObject() {
		return new Test();
	}

	DLLEXPORT int getTest(Test* test) {
		return test->getTest();
	}

	DLLEXPORT void printTests() {
		for (int i = 0; i < tests.size(); i++) {
			std::cout << (tests.at(i))->getTest() << "\n";
		}
	}

	DLLEXPORT void saveTests(Test** _tests, int count) {
		for (int i = 0; i < count; i++) {
			tests.push_back(_tests[i]);
		}
	}
}
