#include "Layer.h"
#include <math.h>
#include <iostream>



Layer::Layer(int size) :
    std::vector<double>(size)
{

}

Layer::Layer(size_t size) :
    std::vector<double>(size)
{
}

Layer::~Layer()
{
}

void Layer::pow(int toPowOf)
{
    for (size_t i = 0; i < size(); i++)
    {
        at(i) = std::pow(at(i), toPowOf);
    }
}

double Layer::sum()
{
    double sum = 0;
    for (size_t i = 0; i < size(); i++)
    {
        sum += at(i);
    }

    return sum;
}

void Layer::reset()
{
    for (size_t i = 0; i < size(); i++)
    {
        at(i) = 0;
    }
}

void Layer::print()
{
    using namespace std;

    cout << "\nvector: \n";

    for (size_t i = 0; i < size(); i++)
    {
        cout << " " << at(i);
    }

    cout << "\n";
}

Layer Layer::operator+(const Layer & other) const
{
    Layer result(other.size());

    if (size() == other.size())
    {
        for (size_t i = 0; i < size(); i++)
        {
            result.at(i) = at(i) + other.at(i);
        }
    }
    else
    {
        std::cout << "\n\nERROR. Layer::operator+(Layer &other). The object and other musst have the same size!\n\n";
    }

    return result;
}

Layer Layer::operator-(const Layer & other) const
{
    Layer result(other.size());

    if (size() == other.size())
    {
        for (size_t i = 0; i < size(); i++)
        {
            result.at(i) = at(i) - other.at(i);
        }
    }
    else
    {
        std::cout << "\n\nERROR. Layer::operator-(Layer &other). The object and other musst have the same size!\n\n";
    }

    return result;
}

Layer Layer::operator*(const Layer & other) const
{
    Layer result(other.size());

    if (size() == other.size())
    {
        for (size_t i = 0; i < size(); i++)
        {
            result.at(i) = at(i) * other.at(i);
        }
    }
    else
    {
        std::cout << "\n\nERROR. Layer::operator*(Layer &other). The object and other musst have the same size!\n\n";
    }

    return result;
}

Layer Layer::operator+(const double n) const
{
    Layer result(size());

    for (size_t i = 0; i < size(); i++)
    {
        result.at(i) = at(i) + n;
    }

    return result;
}

Layer Layer::operator-(const double n) const
{
    Layer result(size());

    for (size_t i = 0; i < size(); i++)
    {
        result.at(i) = at(i) - n;
    }

    return result;
}

Layer Layer::operator*(const double n) const
{
    Layer result(size());

    for (size_t i = 0; i < size(); i++)
    {
        result.at(i) = at(i) * n;
    }

    return result;
}
