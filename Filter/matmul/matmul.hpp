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
void scalarMult6_6(float mat[6][6], float scalar, float out[6][6]);
void matMult9_9(float mat[9][9], float mat2[9][9], float out[9][9]);
void transpose_9_9(float mat[9][9], float out[9][9]);
void matMult9_6(float mat[9][6], float mat2[6][6], float out[9][6]);
void matMult6_9(float mat[9][6], float mat2[6][9], float out[9][9]);
void transpose_9_6(float mat[9][6], float out[6][9]);
void addMat_9_9(float mat [9][9], float mat2[9][9]);


#endif MATMUl
