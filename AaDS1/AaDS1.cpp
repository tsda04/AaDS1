#include <iostream>
#include <random>
#include <clocale>
#include <stdexcept>
#include <cmath>

template<typename T>
class Vector {
private:
    //size_t - помещает максимально возможный размер массива на данной архитектуре (и при этом не переполняется как int)
    size_t size;
    T* coordinate;

    void copy(const Vector& other)
    {
        size = other.size;
        coordinate = new T[size];
        for (size_t i = 0; i < size; ++i) {
            coordinate[i] = other.coordinate[i];
        }
    }

    void clear()
    {
        delete[] coordinate;
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
    Vector() 
    {
        size = 1;
        coordinate = new T[size];
        coordinate[0] = 0;
    }

    //Конструктор случайных чисел
    Vector(size_t n, int start, int end)
    {
        if (n == 0)
        {
            throw std::length_error("The size cannot be zero!");
        }

        size = n;
        coordinate = new T[size];
        for (size_t i = 0; i < size; ++i)
            coordinate[i] = random(start, end);
    }
    //конструктор с параметром размера
    Vector(size_t n)
    {
        if (n == 0)
        {
            throw std::length_error("The size cannot be zero!");
        }

        size = n;
        coordinate = new T[size];
        for (size_t i = 0; i < size; ++i)
            coordinate[i] = T();
    }

    //конструктор с параметрами
    Vector(size_t n, T value) 
    {
        if (n == 0)
        {
            throw std::length_error("The size cannot be zero!");
        }
        size = n;
        coordinate = new T[size];
        for (size_t i = 0; i < size; ++i)
            coordinate[i] = value;
    }

    //конструктор копирования
    Vector(const Vector& other)
    {
        copy(other);
    }

    //оператор присваивания
    Vector& operator=(const Vector& other) 
    {
        if (this != &other) 
        {
            clear();
            copy(other);
        }
        return *this;
    }

    //деструктор
    ~Vector() 
    {
        clear();
    }

    
    //сложение
    Vector& operator+=(const Vector& other)
    {
        if (size != other.size)
		{
			throw std::invalid_argument("The sizes are not equal!");
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
            throw std::invalid_argument("The sizes are not equal!");
        }
        for (size_t i = 0; i < size; ++i)
        {
            coordinate[i] -= other.coordinate[i];
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
    T operator*=(const Vector& other) const
    {
        if (size != other.size)
        {
            throw std::invalid_argument("The sizes are not equal!");
        }
        T res = T();
        for (size_t i = 0; i < size; ++i)
        {
            res += coordinate[i] * other.coordinate[i];
        }

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
            throw std::logic_error("The divisor cannot be zero!");
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

    //сравнение на неравенство
    bool operator!=(const Vector& other) const
    {
        return !(*this == other);
    }

    //получение доступа
    T operator[](size_t i) const
    {
        if (i > size - 1)
        {
            throw std::out_of_range("Index out of range!");
        }

        return coordinate[i];
    }

    //получение доступа для изменения
    T& operator[](size_t i)
    {
        if (i > size - 1)
        {
            throw std::out_of_range("Index out of range!");
        }

        return coordinate[i];
    }
    //сравнение на равенство
    template<typename U>
    friend bool operator==(const Vector<U>& a, const Vector<U>& b);

    //сравнение на равенство float
    friend bool operator==(const Vector<float>& a, const Vector<float>& b);
    //сравнение на равенство double
    friend bool operator==(const Vector<double>& a, const Vector<double>& b);
    //точность:
    static const long double EPS;
    
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& output, const Vector<U>& v);
};

//инициализация статической константы:
template<typename T>
const long double Vector<T>::EPS = 1e-5;

//сравнение на равенство в общем случае
template<typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b)
{

    if (a.size != b.size)
    {
        return false;
    }

    for (size_t i = 0; i < a.size; ++i)
    {
        if (a.coordinate[i] != b.coordinate[i])
            return false;
    }

    return true;
}

//"специализация" функции, т.е. перегрузка функции сравнение на равенство с float
bool operator==(const Vector<float>& a, const Vector<float>& b)
{
    //std::cout << "FLOAT" << std::endl;
    if (a.size != b.size)
    {
        return false;
    }

    for (size_t i = 0; i < a.size; ++i)
    {
        if (fabs(a.coordinate[i] - b.coordinate[i]) > Vector<float>::EPS)

            return false;
    }

    return true;
}

//"специализация" функции, т.е. перегрузка функции сравнение на равенство с double
bool operator==(const Vector<double>& a, const Vector<double>& b)
{
    //std::cout << "DOUBLE" << std::endl;
    if (a.size != b.size)
    {
        return false;
    }

    for (size_t i = 0; i < a.size; ++i)
    {
        if (fabs(a.coordinate[i] - b.coordinate[i]) > Vector<double>::EPS)
            return false;
    }

    return true;
}

//произведение
template<typename T>
Vector<T> operator*(T n, const Vector<T>& v)
{
    return v * n;
    //коммутативность
}

//вывод в поток
template<typename T>
std::ostream& operator<<(std::ostream& output, const Vector<T>& v)
{
    output << "{ ";

    for (size_t i = 0; i < v.size - 1; ++i)
        output << v.coordinate[i] << "; ";
    output << v.coordinate[v.size - 1] << " ";

    output << "}";
    output << std::endl;

    return output;
}
int main() {
    setlocale(LC_ALL, "RUS");
    {

        Vector<double> v1(5, 2.1);
        std::cout << v1 << std::endl;

        Vector<double> v2(v1);	//конструктор копирования (явный вызов)
        Vector<double> v3 = v1;	//конструктор копирования (неявный вызов)

        Vector<int> v4(3, 5, 10);
        Vector<short> v5(2, 5, 10);
        Vector<double> v6(2, 1, 5);
        Vector<double> v7(2, 10);
        Vector<double> v8(2, 10);
        Vector<double> v9(1, 10);
        Vector<double> v10(3, 2, 10);

        Vector<double> const v11 = v10;

        std::cout << "v4: ";
        std::cout << v4 << std::endl;
        std::cout << "index 2:" << v4[2] << std::endl;
        std::cout << std::endl;
        std::cout << "v5:" << std::endl;
        std::cout << v5 << std::endl;
        std::cout << "v6:" << std::endl;
        std::cout << v6 << std::endl;
        std::cout << "v7:" << std::endl;
        std::cout << v7 << std::endl;
        std::cout << "v8:" << std::endl;
        std::cout << v8 << std::endl;
        std::cout << "v9:" << std::endl;
        std::cout << v9 << std::endl;
        std::cout << "v10:" << std::endl;
        std::cout << v10 << std::endl;

        (std::cout << v1) << v2 << v3;

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
            v7 / 0;
            //v7.sum(v6);
            v7[100] = 5;
            std::cout << (v7 + v6) << std::endl;

            v7 * 3;
            v7.operator*(3);

            3.0 * v7;
 

            std::cout << v7;
            operator<<(std::cout, v7);

            v7.operator+(v6);
            v6 /= 2;
            v7 *= 3;
        }
        catch (const std::out_of_range& error)
        {
            std::cout << "OUT OF RANGE: " << "Индекс находится вне допустимых пределов!" << std::endl;
        }
        catch (const std::length_error& error)
        {
            std::cout << "LENGTH ERROR: " << "Размер не может быть равен нулю!" << std::endl;
        }
        catch (const std::invalid_argument& error)
        {
            std::cout << "INVALID ARGUMENT: " << "Размеры не совпадают!" << std::endl;
        }
        catch (const std::exception& error)
        {
            std::cout << "EXCEPTION: " << error.what() << std::endl;
        }
       
    }

    return 0;
}