#include <iostream>

class Vector {
private:
	int size;
	int* coordinate;
public:
	Vector() {
		size = 0;
		coordinate[0] = 0;
	}

	Vector(int n, int value) {
		size = n;
		coordinate = new int[size];
		for (int i = 0; i < size; ++i)
			coordinate[i] = value;
	}

	~Vector() {
		delete[] coordinate;
	}
	void print() const {
		for (int i = 0; i < size; ++i)
			std::cout << coordinate[i] << " ";
	}
};
int main() {
	Vector A(2, 1);
	A.print();
	return 0;
}