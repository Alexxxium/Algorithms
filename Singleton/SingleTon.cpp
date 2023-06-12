
#include <iostream>

// ���������� ��������� �� ����������� ���������� ������
// ������������ ��� ����� ���������� ������ �� ���������� ���������
template<class T>
class Singleton1
{
private:

    static Singleton1* p_instance;
    T data;

    Singleton1(const T &vl): data(vl) {}

    Singleton1(const Singleton1&) = delete;
    Singleton1& operator=(Singleton1&) = delete;
    // ����������� ����������� �� ���������� �� �������������

public:

    static Singleton1* getInstance(const T &vl)
    {
        if (!p_instance)
            p_instance = new Singleton1(vl);

        return p_instance;
    }

    const T& getValue()
    {
        return data;
    }
};

template<typename T>
Singleton1<T>* Singleton1<T>::p_instance = nullptr;



// ���������� ������ �� ����������� ���������� (������)
// ����������������� ����� ���������� ����������
template<class T>
class Singleton
{
private:

    T data;

    Singleton(const T &vl): data(vl) {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(Singleton&) = delete;

public:

    static Singleton& getInstance(const T &vl)
    {
        static Singleton instance(vl);
        return instance;
    }

    const T& getValue()
    {
        return data;
    }
};




int main()
{
    Singleton1<const char*> *s1 = Singleton1<const char*>::getInstance("sas");          // �������� ��������� �� ���������� ���������� ������
    Singleton1<const char*> *s2 = Singleton1<const char*>::getInstance("sys");

    Singleton<int> &s3 = Singleton<int>::getInstance(9);                                // �������� ������ �� ����������� ������
    Singleton<int> &s4 = Singleton<int>::getInstance(3);

    std::cout <<
        s1->getValue() << '\n' <<
        s2->getValue() << '\n' <<
        s3.getValue() << '\n' <<
        s4.getValue() << '\n';

    delete[] s1, s2;
}

