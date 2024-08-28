#include "Weight.h"
#include <stdio.h>
#include <iostream>



Weight::Weight(int rows, int cols) :
    std::vector<double>(rows*cols), m_rows(rows), m_cols(cols)
{
}

Weight::~Weight()
{
}

double &Weight::at(int row, int col)
{
    return std::vector<double>::at(row*m_cols + col);
}

const double & Weight::at(int row, int col) const
{
    return std::vector<double>::at(row*m_cols + col);
}

void Weight::reset()
{
    for (size_t i = 0; i < size(); i++)
    {
        std::vector<double>::at(i) = 0;
    }
}

void Weight::print()
{
    using namespace std;

    cout << "\nMatrix: \n";

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            cout << " " << at(i, j);
        }
        cout << "\n";
    }

    cout << "\n";
}


Layer Weight::operator*(const Layer & other) const
{
    Layer result(m_rows);

    if (static_cast<int>(other.size()) == m_cols)
    {
        for (int i = 0; i < m_rows; i++)
        {
            for (int j = 0; j < m_cols; j++)
            {
                result.at(i) += at(i, j) * other.at(j);
            }
        }
    }
    else
    {
        std::cout << "\n\nERROR. Weight::operator*(Layer &other). The object and other's dimensions musst agree!\n\n";
    }

    return result;
}

Weight Weight::operator+(const double n) const
{
    Weight result(m_rows, m_cols);

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            result.at(i, j) = at(i, j) + n;
        }
    }

    return result;
}

Weight Weight::operator-(const double n) const
{
    Weight result(m_rows, m_cols);

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            result.at(i, j) = at(i, j) - n;
        }
    }

    return result;
}

Weight Weight::operator*(const double n) const
{
    Weight result(m_rows, m_cols);

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            result.at(i, j) = at(i, j) * n;
        }
    }

    return result;
}
