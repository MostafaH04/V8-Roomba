#include "matmul.hpp"

void scalarMult3_3(float mat[3][3], float scalar, float out[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            out[i][j] = mat[i][j] * scalar;
        }
    }
}

void vecMultTranspose_3(float vector[3], float out[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            out[i][j] = vector[i] * vector[j];
        }
    }
}

void skewSymetric (float vector[3], float out[3][3])
{
    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 3; j++)
        {
            out[i][j] = 0;
        }
    }

    out[0][1] = - vector[2];
    out[0][2] = vector[1];
    out[1][0] = vector[2];
    out[1][2] = - vector[0];
    out[2][0] = - vector[1];
    out[2][1] = vector[0];
}

void addMat(float mat[3][3], float mat_2[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat[i][j] += mat_2[i][j];
        }
    }
}

void scalarMult4_4(float mat[4][4], float scalar, float out[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            out[i][j] = mat[i][j] * scalar;
        }
    }
}

void matVecMult_4(float mat[4][4], float vector[4], float out[4])
{
    for (int i = 0; i < 4; i++)
    {
        float currTerm = 0;
        for (int j = 0; j < 4; j++)
        {
            currTerm += mat[i][j] * vector[j];
        }
        out[i] = currTerm;
    }
}

void matVecMult_3(float mat[3][3], float vector[3], float out[3])
{
    for (int i = 0; i < 3; i++)
    {
        float currTerm = 0;
        for (int j = 0; j < 3; j++)
        {
            currTerm += mat[i][j] * vector[j];
        }
        out[i] = currTerm;
    }
}

void scalarMult6_6(float mat[6][6], float scalar, float out[6][6])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            out[i][j] = mat[i][j] * scalar;
        }
    }
}

void matMult9_9(float mat[9][9], float mat2[9][9], float out[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            float currTerm = 0;
            for (int k = 0; k < 9; k++)
            {
                currTerm += mat[i][k] * mat2[k][j];
            }
            out[i][j] = currTerm;
        }
    }
}

void transpose_9_9(float mat[9][9], float out[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            out[j][i] = mat[i][j];
        }
    }
}

void matMult9_6(float mat[9][6], float mat2[6][6], float out[9][6])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            float currTerm = 0;
            for (int k = 0; k < 6; k++)
            {
                currTerm += mat[i][k] * mat2[k][j];
            }
            out[i][j] = currTerm;
        }
    }
}

void matMult6_9(float mat[9][6], float mat2[6][9], float out[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            float currTerm = 0;
            for (int k = 0; k < 6; k++)
            {
                currTerm += mat[i][k] * mat2[k][j];
            }
            out[i][j] = currTerm;
        }
    }
}

void addMat_9_9(float mat [9][9], float mat2[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            mat[i][j] += mat2[i][j];
        }
    }
}