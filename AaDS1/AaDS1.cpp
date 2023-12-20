#include <iostream>
#include <random>
#include <clocale>

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
	int random(int low, int high)
	{
		std::random_device rd;
		std::mt19937 generator(rd());
		std::uniform_int_distribution<> distribution(low, high);
		return  distribution(generator);
	}

public:
	//конструктор по умолчанию
	Vector() {
		size = 1;
		coordinate = new T[size];
		coordinate[0] = 0;
	}

	Vector(size_t n, T start, T end)
	{
		size = n;
		coordinate = new T[size];
		for (size_t i = 0; i < size; ++i)
			coordinate[i] = random(start, end);//2 предупреждения
	}
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
	//сложение векторов
	void sum(const Vector& other)
	{
		if (size = other.size)
		{
			for (size_t i = 0; i < size; ++i)
			{
				coordinate[i] += other.coordinate[i];
			}
		}
		throw  std::string{ "The sizes are not equal!" };
	}

	//вычитание векторов
	void diff(const Vector& other)
	{
		if (size != other.size)
		{
			throw std::string{ "The sizes are not equal!" };
		}

		for (size_t i = 0; i < size; ++i)
		{
			coordinate[i]  -= other.coordinate[i];
		}
	}
	//произведение
	void mult(const Vector& other)
	{
		if (size != other.size)
		{
			throw std::string{ "The sizes are not equal!" };
		}

		for (size_t i = 0; i < size; ++i)
		{
			coordinate[i] = coordinate[i] * other.coordinate[i];
		}
	}

	//умножения на число
	void mult(T n)
	{
		for (size_t i = 0; i < size; ++i)
		{
			coordinate[i] *= n;
		}
	}

	//деление на число
	void div(T n)
	{
		if (n)
		{
			for (size_t i = 0; i < size; ++i)
			{
				coordinate[i] = coordinate[i] / n;
			}
		}
	}
	T get_coord(int i) const
	{
		return coordinate[i];
	}

	T get_coord(int i)//для изменения
	{
		return coordinate[i];
	}
};


int main() {
	setlocale(LC_ALL, "RUS");
	{
		Vector v1(5, 2.1);
		v1.print();

		Vector v2(v1);
		Vector v3 = v1;

		Vector v4(3, 5, 10);
		Vector v5(2, 5, 10);
		Vector v6(2, 1, 5);
		Vector v7(2, 1, 10);

		std::cout << "v4: ";
		v4.print();
		std::cout << "index 2:" << v4.get_coord(2) << std::endl;
		std::cout << std::endl;
		std::cout << "v5:" << std::endl;
		v5.print();
		std::cout << "v7:" << std::endl;
		v7.print();
		std::cout << "v6:" << std::endl;
		v6.print();

		try
		{

			v5.diff(v6);
			//v7.sum(v6);
			v7.mult(v6);

			v4.mult(v6);//бросит исключение
		}
		catch (std::string error_message)
		{
			std::cout << error_message << std::endl;
		}
		std::cout << "same v4:" << std::endl;
		v4.print();
		std::cout << "v5-v6=";
		v5.print();
		std::cout << "v7*v6=";
		v7.print();
	}

	return 0;
}