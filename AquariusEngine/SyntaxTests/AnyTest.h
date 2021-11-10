#pragma once
#include <any>
#include <vector>
#include <iostream>

inline std::vector<std::any> anys;

class D {
protected:
	int a;
	D(int a) {
		this->a = a;
	}
};

class E : public D {
private:
	int b;
public:
	E(int b) : D(b) {
		this->b = b;
	}
	void printE() {
		std::cout << b << "\n";
	}
};

class F : public E {
private:
	int c;
public:
	F(int c) : E(c) {
		this->c = c;
	}
	void printF() {
		std::cout << c << "\n";
	}
};