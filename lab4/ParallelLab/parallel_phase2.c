#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

//This code is buggy! Find the bug and speed it up.
void parallel_to_grayscale(long img[DIM_ROW][DIM_COL][DIM_RGB], long ***grayscale_img, long *min_max_gray)
{

        long min_gray = 256;
        long max_gray = -1;

#pragma omp parallel
        {
            long temp_min_gray = 256;
            long temp_max_gray = -1;

#pragma omp for collapse(2)
            for (int row = 0; row < DIM_ROW; row++)
            {
                for (int col = 0; col < DIM_COL; col++)
                {
                    long gray_pixel = (img[row][col][0] + img[row][col][1] + img[row][col][2]) / 3;
                    grayscale_img[row][col][0] = gray_pixel;
                    grayscale_img[row][col][1] = gray_pixel;
                    grayscale_img[row][col][2] = gray_pixel;

                    if (gray_pixel < temp_min_gray)
                    {
                        temp_min_gray = gray_pixel;
                    }
                    if (gray_pixel > temp_max_gray)
                    {
                        temp_max_gray = gray_pixel;
                    }
                }
            }

#pragma omp critical
            {
                if (temp_min_gray < min_gray)
                {
                    min_max_gray[0] = temp_min_gray;
                    min_gray = temp_min_gray;
                }
                if (temp_max_gray > max_gray)
                {
                    min_max_gray[1] = temp_max_gray;
                    max_gray = temp_max_gray;
                }
            }
        }
    }
    
    
