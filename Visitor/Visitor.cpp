
#include <iostream>


class A;
class B;
class C;


class Visitor
{
public:

    virtual void visit(A &ref) = 0;
    virtual void visit(B &ref) = 0;
    virtual void visit(C &ref) = 0;

    virtual ~Visitor() = default;
};

// ����� � ����������� ������� ����������
class UseVisitor: public Visitor
{
public:

    void visit(A &ref)
    {
        std::cout << "Working whith class A!\n";            // ��� ������� ������������ ������� ������
    }
    void visit(B &ref)
    {
        std::cout << "Working whith class B!\n";
    }
    void visit(C &ref)
    {
        std::cout << "Working whith class C!\n";
    }
};


// ������������ ����� � ������� ��� ������ ������ ���������� �������
class I_Letters
{
public:
    virtual void accept(Visitor &vis) = 0;
    virtual ~I_Letters() = default;
};



class A: public I_Letters
{
public:

    void accept(Visitor &vis) override
    {
        vis.visit(*this);                   // ����� ������ ������������� �������
    }
};

class B: public  I_Letters
{
public:

    void accept(Visitor &vis) override
    {
        vis.visit(*this);                   // ����� ������ ������������� �������
    }
};

class C: public  I_Letters
{
public:

    void accept(Visitor &vis) override
    {
        vis.visit(*this);                   // ����� ������ ������������� �������
    }
};




int main()
{
    I_Letters *arr[] = { new A, new B, new C };

    UseVisitor visitor;                             // ������ ��� ���������

    for (const auto &i : arr)
        i->accept(visitor);


    for (const auto &i : arr)
        delete i;

}


