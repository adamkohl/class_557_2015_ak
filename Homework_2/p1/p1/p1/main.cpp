//
//  main.cpp
//  p1
//
//  Created by Adam Kohl on 9/15/15.
//  Copyright (c) 2015 Adam Kohl. All rights reserved.
//

#include <iostream>
using namespace std;

double getFibonacciNum(int n )
{
    unsigned int i = 0, j = 1, t, k;
    for (k=0; k <= n; ++k)
    {
        t = i + j;
        i = j;
        j = t;
    }
    return j;
}

int main(int argc , char *argv[])
{
    double p = getFibonacciNum(10);
    cout << p << endl;
}