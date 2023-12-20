#include <iostream>

using T = double;
class Vector {
private:
	//size_t помещает максимальный возможный размер на данной архитектуре, не переполняясь
	size_t size;
	T* coordinate;
public:
	Vector() {
		size = 0;
		coordinate[0] = 0;
	}

	Vector(size_t n, T value) {
		size = n;
		coordinate = new T[size];
		for (size_t i = 0; i < size; ++i)
			coordinate[i] = value;
	}

	~Vector() {
		delete[] coordinate;
	}
	void print() const {
		std::cout << "{ ";
		for (size_t i = 0; i < size - 1; ++i)
			std::cout << coordinate[i] << "; ";
		std::cout << coordinate[size - 1] << " ";
		std::cout << "}";
		std::cout << std::endl;
	}
};
int main() {
	Vector A(2, 1);
	A.print();
	return 0;
}