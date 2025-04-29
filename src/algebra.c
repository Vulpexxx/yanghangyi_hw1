/*
 * @Author: vulpex 2267339737@qq.com
 * @Date: 2025-04-28 18:24:02
 * @LastEditors: vulpex 2267339737@qq.com
 * @LastEditTime: 2025-04-29 21:15:57
 * @FilePath: \yanghangyi_hw1\src\algebra.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }

    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }

    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.cols != b.rows)
    {
        printf("Error: The cols of Matrix a and the rows of Matrix b must be equal.\n");
        return create_matrix(0, 0);
    }

    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < b.cols; j++)
        {
            result.data[i][j] = 0;
            for (int k = 0; k < a.cols; k++)
            {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    // ToDo
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    return result;
}

Matrix transpose_matrix(Matrix a)
{
    // ToDo
    Matrix result = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[j][i] = a.data[i][j];
        }
    }
    return result;
}

double det_matrix(Matrix a)
{
    // ToDo
    if (a.rows != a.cols)
    {
        printf("Error: Matrix must have the same rows and cols.\n");
        return 0;
    }

    if (a.rows == 1)
    {
        return a.data[0][0];
    }
    else if (a.rows == 2)
    {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    else
    {
        double result = 0;
        int temp = 1;
        for (int i = 0; i < a.rows; i++)
        {
            Matrix temp_matrix = create_matrix(a.rows - 1, a.cols - 1);
            for (int j = 0; j < a.rows - 1; j++)
            {
                for (int k = 0; k < a.cols - 1; k++)
                {
                    if (k < i)
                    {
                        temp_matrix.data[j][k] = a.data[j + 1][k];
                    }
                    else
                    {
                        temp_matrix.data[j][k] = a.data[j + 1][k + 1];
                    }
                }
            }
            result += temp * a.data[0][i] * det_matrix(temp_matrix);
            temp = -temp;
        }

        return result;
    }
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    if (a.rows != a.cols)
    {
        printf("Error: Matrix must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    if (det_matrix(a) == 0)
    {
        printf("Error: The determinant of the Matrix equails 0.\n");
        return create_matrix(0, 0);
    }
    if (a.rows == 1)
    {
        Matrix result = create_matrix(1, 1);
        result.data[0][0] = 1.0 / a.data[0][0];
        return result;
    }

    Matrix company_matrix = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            Matrix temp_matrix = create_matrix(a.rows - 1, a.cols - 1);
            for (int k = 0; k < a.rows - 1; k++)
            {
                for (int l = 0; l < a.cols - 1; l++)
                {
                    if (k < i)
                    {
                        temp_matrix.data[k][l] = a.data[k][l + (l >= j)];
                    }
                    else
                    {
                        temp_matrix.data[k][l] = a.data[k + 1][l + (l >= j)];
                    }
                }
            }
            company_matrix.data[i][j] = pow(-1, i + j) * det_matrix(temp_matrix);
        }
    }
    return scale_matrix(transpose_matrix(company_matrix), 1.0 / det_matrix(a));
}

int rank_matrix(Matrix a)
{
    int rank = a.cols > a.rows ? a.rows : a.cols;
    Matrix temp_matrix = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            temp_matrix.data[i][j] = a.data[i][j];
        }
    }
    for (int i = 0; i < rank; i++)
    {
        if (temp_matrix.data[i][i] != 0)
        {
            for (int j = i + 1; j < a.rows; j++)
            {
                double factor = temp_matrix.data[j][i] / temp_matrix.data[i][i];
                for (int k = i; k < a.cols; k++)
                {
                    temp_matrix.data[j][k] -= factor * temp_matrix.data[i][k];
                }
            }
        }
        else
        {
            int swap_row = i + 1;
            while (swap_row < a.rows && temp_matrix.data[swap_row][i] == 0)
            {
                swap_row++;
            }
            if (swap_row == a.rows)
            {
                rank--;
                for (int k = 0; k < a.cols; k++)
                {
                    temp_matrix.data[i][k] = temp_matrix.data[a.rows - 1][k];
                }
                continue;
            }
            for (int k = 0; k < a.cols; k++)
            {
                double temp = temp_matrix.data[i][k];
                temp_matrix.data[i][k] = temp_matrix.data[swap_row][k];
                temp_matrix.data[swap_row][k] = temp;
            }
            i--;
        }
    }
    return rank;
}

double trace_matrix(Matrix a)
{
    // ToDo
    if (a.rows != a.cols)
    {
        printf("Error: Matrix must have the same rows and cols.\n");
        return;
    }

    double result = 0;
    for (int i = 0; i < a.cols; i++)
    {
        result += a.data[i][i];
    }

    return result;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}