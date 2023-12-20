#include <iostream>
#include <random>
#include <clocale>


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


using T = double;
class Vector {
    private:
    //size_t - помещает максимально возможный размер массива на данной архитектуре (и при этом не переполняется как int)
    size_t size;
    T* coordinate;

    void copy(const Vector& other) {
        this->size = other.size;
        this->coordinate = new T[size];
        for (size_t i = 0; i < size; ++i) {
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
        std::uniform_int_distribution<int> distribution(low, high);
        return distribution(generator);
    }

public:
    //конструктор по умолчанию
    Vector() {
        size = 1;
        coordinate = new T[size];
        coordinate[0] = 0;
    }

    //Конструктор случайных чисел
    Vector(size_t n, int start, int end)
    {
        if (n == 0)
        {
            throw  std::string{ "The size cannot be zero!" };
        }
        size = n;
        coordinate = new T[size];
        for (size_t i = 0; i < size; ++i)
            coordinate[i] = random(start, end);
    }

    //конструктор с параметрами
    Vector(size_t n, T value) {
        if (n == 0)
        {
            throw  std::string{ "The size cannot be zero!" };
        }
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

    //сложение
    Vector& operator+=(const Vector& other)
    {
        //TODO !!!
        if (size != other.size)
        {
            throw std::string{ "The sizes are not equal!" };
        }

        for (size_t i = 0; i < size; ++i)
        {
            coordinate[i] += other.coordinate[i];
        }

        return *this;
    }

    //сложение
    Vector operator+(const Vector& other) const
    {
        Vector res = *this;
        res += other;
        return res;
    }

    //вычитание векторов
    Vector& operator-=(const Vector& other)
    {
        if (size != other.size)
        {
            throw std::string{ "The sizes are not equal!" };
        }

        for (size_t i = 0; i < size; ++i)
        {
            coordinate[i] = coordinate[i] - other.coordinate[i];
        }
        return *this;

    }

    //вычитание векторов
    Vector operator-(const Vector& other) const
    {
        Vector res = *this;
        res -= other;
        return res;
    }

    //произведение
    Vector& operator*=(const Vector& other)
    {
        if (size != other.size)
        {
            throw std::string{ "The sizes are not equal!" };
        }

        for (size_t i = 0; i < size; ++i)
        {
            coordinate[i] = coordinate[i] * other.coordinate[i];
        }
        return *this;

    }

    //произведение
    Vector operator*(const Vector& other) const
    {
        Vector res = *this;
        res *= other;
        return res;
    }

    //умножения на число
    Vector& operator*=(T n)
    {
        for (size_t i = 0; i < size; ++i)
        {
            coordinate[i] = coordinate[i] * n;
        }
        return *this;
    }

    //умножения на число
    Vector operator*(T n) const
    {
        Vector res = *this;
        res *= n;
        return res;
    }

    //деление на число
    Vector& operator/=(T n)
    {
        if (n == 0)
        {
            throw  std::string{ "The divisor cannot be zero!" };
        }
        for (size_t i = 0; i < size; ++i)
        {
            coordinate[i] = coordinate[i] / n;
        }
        return *this;

    }

    //деление на число
    Vector operator/(T n) const
    {
        Vector res = *this;
        res /= n;
        return res;
    }

    //сравнение на равенство
    bool operator==(const Vector& other)
    {

        if (size != other.size)
        {
            return false;
        }
        else
        {
            for (size_t i = 0; i < size; ++i)
            {
                if (coordinate[i] != other.coordinate[i])
                    return false;

            }
            return true;
        }
    }

    //сравнение на неравенство
    bool operator!=(const Vector& other)
    {

        if (size != other.size)
        {
            return true;
        }
        else

        {
            for (size_t i = 0; i < size; ++i)
            {
                if (coordinate[i] != other.coordinate[i])
                {
                    return true;

                }

            }
            return false;
        }
    }

    T get_coord(size_t i) const
    {
        if (i > size - 1)
        {
            throw std::string{ "Index out of range!" };
        }
        return coordinate[i];
    }

    T& get_coord(size_t i)//для изменения
    {
        if (i > size - 1)
        {
            throw std::string{ "Index out of range!" };
        }
        return coordinate[i];
    }
};

//произведение
Vector operator*(T n, const Vector& v)
{
    return v * n;
    //коммутативность
}


int main() {
    setlocale(LC_ALL, "RUS");
    {
       
        Vector v1(5, 2.1);
        v1.print();

        Vector v2(v1);  //конструктор копирования (явный вызов)
        Vector v3 = v1;  //конструктор копирования (неявный вызов)

        Vector v4(3, 5, 10);
        Vector v5(2, 5, 10);
        Vector v6(2, 1, 5);
        Vector v7(2, 10);
        Vector v8(2, 10);
        Vector v9(1, 10);
        Vector v10(3, 2, 10);

        std::cout << "v4: ";
        v4.print();
        std::cout << "index 2:" << v4.get_coord(2) << std::endl;
        std::cout << std::endl;
        std::cout << "v5:" << std::endl;
        v5.print();
        std::cout << "v6:" << std::endl;
        v6.print();
        std::cout << "v7:" << std::endl;
        v7.print();
        std::cout << "v8:" << std::endl;
        v8.print();
        std::cout << "v9:" << std::endl;
        v9.print();
        std::cout << "v10:" << std::endl;
        v10.print();

        if (v7 != v8)
            std::cout << "v7!=v8" << std::endl;
        else
            std::cout << "v7==v8" << std::endl;

        if (v7 != v9)
            std::cout << "v7!=v9" << std::endl;
        else
            std::cout << "v7==v9" << std::endl;
        if (v7 != v10)
            std::cout << "v7!=v10" << std::endl;
        else
            std::cout << "v7==v10" << std::endl;

        try
        {
            //v7.sum(v6);

            (v7 + v6).print();

            v7 * 3;
            v7.operator*(3);

            3 * v7;
            operator*(3, v7);

            v5 -= v6;

            v7 *= v6;
            v6 /= 2;
            v7 *= 3;
            v4 += v6;//выводит ошибку 
        }
        catch (std::string error_message)
        {
            std::cout << error_message << std::endl;
        }
        std::cout << "same v4:" << std::endl;
        v4.print();
        std::cout << "v5-v6=";
        v5.print();
        std::cout << "v7*v6*3=";
        v7.print();
    }

    return 0;
}