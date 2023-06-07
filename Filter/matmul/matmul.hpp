#ifndef MATMUL
#define MATMUL

void scalarMult3_3(float mat[3][3], float scalar, float out[3][3]);
void vecMultTranspose_3(float vector[3], float out[3][3]);
void skewSymetric (float vector[3], float out[3][3]);
void addMat (float mat[3][3], float mat_2[3][3]);
void addMat_4 (float mat[4][4], float mat_2[4][4]);
void scalarMult4_4(float mat[4][4], float scalar, float out[4][4]);
void matVecMult_4(float mat[4][4], float vector[4], float out[4]);
void matVecMult_3(float mat[3][3], float vector[3], float out[3]);

#endif MATMUl
