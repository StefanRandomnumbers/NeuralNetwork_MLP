#include "Weight.h"
#include "Layer.h"
#include <iostream>
#include <stdio.h>


int main(int argc, char *argv[])
{
    Weight w1(3, 2);
    int count = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            w1.at(i, j) = count;
            count++;
        }
    }

    Layer v1(2);
    v1.at(0) = 1;
    v1.at(1) = 2;

    v1.print();
    w1.print();

    (w1 * v1).print();

    (w1 + 1).print();
    (w1 - 1).print();

    return 0;
}