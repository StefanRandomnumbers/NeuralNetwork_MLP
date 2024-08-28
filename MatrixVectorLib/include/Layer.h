#pragma once
#include <stdio.h>
#include <vector>

class Layer :
    public std::vector<double>
{
public:
    Layer(int size);
    Layer(size_t size);
    ~Layer();

    void pow(int toPowOf);
    double sum();
    void reset();

    void print();

    Layer operator+(const Layer &other) const;
    Layer operator-(const Layer &other) const;
    Layer operator*(const Layer &other) const;

    Layer operator+(const double n) const;
    Layer operator-(const double n) const;
    Layer operator*(const double n) const;
};