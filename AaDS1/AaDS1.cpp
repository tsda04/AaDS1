#include <iostream>

using T = double;
class Vector {
private:
	//size_t помещает максимально возможный размер массива на данной архитектуре, не переполняясь
	size_t size;
	T* coordinate;
	void copy(const Vector& other) {
		this->size = other.size;
		this->coordinate = new T[size];
		for (int i = 0; i < size; ++i) {
			this->coordinate[i] = other.coordinate[i];
		}
	}
	void clear() {
		delete[] this->coordinate;
	}

public:
	//конструктор по умолчанию
	Vector() {
		size = 1;
		coordinate = new T[size];
		coordinate[0] = 0;
	}

	/*Vector(параметры)
	{
		//TODO Конструктор случайных чисел

	}*/

	//конструктор с параметрами
	Vector(size_t n, T value) {
		//+ проверка на n = 0
		size = n;
		coordinate = new T[size];
		for (size_t i = 0; i < size; ++i)
			coordinate[i] = value;
	}

	//конструктор копирования
	Vector(const Vector& other) {
		this->copy(other);
	}

	//оператор присваивания
	Vector& operator=(const Vector& other) {
		if (this != &other) {
			this->clear();
			this->copy(other);
		}
		return *this;
	}

	//деструктор
	~Vector() {
		clear();
	}

	//метод печати
	void print() const {
		std::cout << "{ ";

		for (size_t i = 0; i < size - 1; ++i)
			std::cout << coordinate[i] << "; ";
		std::cout << coordinate[size - 1] << " ";

		std::cout << "}";
		std::cout << std::endl;
	}
	void sum(const Vector& other)
	{
		//if (разный размер)
		//TODO сложение векторов (сразу в this)
	}

	void diff(const Vector& other)
	{
		//if (разный размер)
		//TODO вычитание векторов (сразу в this)
	}

	void mult(const Vector& other)
	{
		//TODO произведение
	}

	void mult(/*число*/)
	{
		//TODO умножения на число
	}

	void div(/*число*/)
	{
		//TODO деление на число
	}
};


int main() {

	{
		Vector A(2, 1);
		A.print();
		Vector B(2, 2);
		B.print();
		B = A;
		B.print();
	}
	return 0;
}