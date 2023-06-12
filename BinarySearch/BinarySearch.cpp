
/*
    Бинарный поиск элементов в векторе. Функция поиска элемента вернет нам самый первый элемент с нужным значением.
    Причем поиск всегда будет бинарным: (с погрешностью в одну итерацию) O(log(N)) и в худшем случае O(log(N) + 1).
    В отличие от обычного бинарного поиска элемента и последовательному итерированию влево до самого первого такого элемента,
    мы не знаем количество таких итераций.
    Эта реализация эффективнее, если повторяемых значений может быть много, но менее эффективна, если все элементы уникальны,
    т.к. мы обязательно должны пройти весь массив бинарным способом исключив вероятность случйного нахождения нужного нам значения
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


// Значение по которому мы сортируем и bool переменная (true, если предыдущие элементы не повторялись)
struct Pair
{
    int first;
    bool second;

    bool operator> (const Pair &p) const
    {
        return this->first > p.first;
    }
    bool operator< (const Pair &p) const
    {
        return this->first < p.first;
    }
    bool operator==(const Pair &p) const
    {
        return this->first == p.first;
    }
    void operator= (const Pair &p)
    {
        this->first = p.first;
        this->second = p.second;
    }

    explicit Pair(int vl = 0): first(vl), second(false) {}
};
std::ostream& operator<< (std::ostream &out, const Pair &p)
{
    out << p.first << ' ' << p.second << ' ';
    if (p.second)
        out << "<- Is min index!";

    return out;
}


template <typename T>
const T& binarySearch(std::vector<T> &vec, T  &&vl)
{
    std::sort(vec.begin(), vec.end());

    size_t left(0), right(vec.size() - 1);
    size_t mid(right / 2);

    if (vec[left] == vl) return vec[left];

    while (left < right)                        
    {
        if (vl > vec[mid])
            left = mid + 1;
        else                                    
            right = mid - 1;

        mid = (left + right) / 2;
    }
   
    if (vec[right] == vl)
        return vec[right];

    else if (vec[++right] == vl && right < vec.size())
        return vec[right];

    else throw 1;
    //else return T();
}



int main()
{
    // Test:


    std::cout << "Set lenght:\t";
    int lenght;
    std::cin >> lenght;


    std::vector<Pair> vec(lenght);
    for (int i = 0; i < vec.size(); ++i)
        vec[i] = Pair(rand() % 9 + 1);

    std::sort(vec.begin(), vec.end());


    vec[0].second = true;
    int buff = vec[0].first;
    for (int i = 1; i < vec.size(); ++i)
    {
        if (vec[i].first == buff)
            vec[i].second = false;
        else
            vec[i].second = true;

        buff = vec[i].first;
    }


    std::cout << "\nMy array:\n";
    for (int i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << '\n';

    std::cout << "\nFound value with min index:\t";
    std::cin >> lenght;

    Pair pair = binarySearch(vec, Pair(lenght));

    std::cout << "\nMy first value:\t" << pair << std::endl;
}
