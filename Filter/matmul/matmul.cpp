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