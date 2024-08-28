#include <vector>
#include "Layer.h"

class Weight :
    public std::vector<double>
{
public:
    Weight(int rows, int cols);
    ~Weight();

    double &at(int row, int col);
    const double &at(int row, int col) const;

    void reset();
    void print();


    Layer operator*(const Layer &other) const;

    Weight operator+(const double n) const;
    Weight operator-(const double n) const;
    Weight operator*(const double n) const;

private:
    int m_rows;
    int m_cols;
};