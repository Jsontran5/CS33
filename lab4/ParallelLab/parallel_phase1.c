#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

// This code is buggy! Find the bug and speed it up.
void parallel_avg_pixel(long img[DIM_ROW][DIM_COL][DIM_RGB], long *avgs)
{
    int row, col;
    long count;
    long r, g, b;
    r = 0;
    g = 0;
    b = 0;
    count = 0;

#pragma omp parallel for collapse(2) reduction(+ : r, g, b)
    for (row = 0; row < DIM_ROW; row++)
    {
        for (col = 0; col < DIM_COL; col++)
        {
            r += img[row][col][0];
            g += img[row][col][1];
            b += img[row][col][2];
        }
    }

    count = DIM_ROW * DIM_COL;

    avgs[0] = r / count;
    avgs[1] = g / count;
    avgs[2] = b / count;
}