#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

// function that take arguments by value and return by value
float
vec3Length(Vec3 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Vec3
vec3Normalize(Vec3 vec) {
    float length = vec3Length(vec);
    Vec3 ret = {
        .x = vec.x / length,
        .y = vec.y / length,
        .z = vec.z / length
    };
    return ret;
}

Vec3
vec3CrossProduct(Vec3 a, Vec3 b) {
    Vec3 ret = {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x
    };
    return ret;
}

// functions that take arguments by pointer, and return by value
float
vec3LengthP(Vec3 const *vec) {
    return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

Vec3
vec3NormalizeP(Vec3 const *vec) {
    float length = vec3LengthP(vec);
    Vec3 ret = {
        .x = vec->x / length,
        .y = vec->y / length,
        .z = vec->z / length
    };
    return ret;
}

Vec3
vec3CrossProductP(Vec3 const *a, Vec3 const *b) {
    Vec3 ret = {
        .x = a->y * b->z - a->z * b->y,
        .y = a->z * b->x - a->x * b->z,
        .z = a->x * b->y - a->y * b->x
    };
    return ret;
}

// functions that take arguments by pointer, and return result by pointer
float
vec3LengthPP(Vec3 const *vec) {
    return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void
vec3NormalizePP(Vec3 *t, Vec3 const *vec) {
    float length = vec3LengthP(vec);
    t->x = vec->x / length;
    t->y = vec->y / length;
    t->z = vec->z / length;
}

void
vec3CrossProductPP(Vec3 *t, Vec3 const *a, Vec3 const *b) {
    t->x = a->y * b->z - a->z * b->y;
    t->y = a->z * b->x - a->x * b->z;
    t->z = a->x * b->y - a->y * b->x;
}

typedef struct Mat4f {
    // column 0
    float m00;
    float m01;
    float m02;
    float m03;

    // column 1
    float m10;
    float m11;
    float m12;
    float m13;

    // column 2
    float m20;
    float m21;
    float m22;
    float m23;

    // column 3
    float m30;
    float m31;
    float m32;
    float m33;
} Mat4f;

Mat4f
mat4fMul(Mat4f a, Mat4f b) {
    Mat4f ret;
    ret.m00 = a.m00*b.m00 + a.m10*b.m01 + a.m20*b.m02 + a.m30*b.m03;
    ret.m01 = a.m00*b.m10 + a.m10*b.m11 + a.m20*b.m12 + a.m30*b.m13;
    ret.m02 = a.m00*b.m20 + a.m10*b.m21 + a.m20*b.m22 + a.m30*b.m23;
    ret.m03 = a.m00*b.m30 + a.m10*b.m31 + a.m20*b.m32 + a.m30*b.m33;

    ret.m10 = a.m01*b.m00 + a.m11*b.m01 + a.m21*b.m02 + a.m31*b.m03;
    ret.m11 = a.m01*b.m10 + a.m11*b.m11 + a.m21*b.m12 + a.m31*b.m13;
    ret.m12 = a.m01*b.m20 + a.m11*b.m21 + a.m21*b.m22 + a.m31*b.m23;
    ret.m13 = a.m01*b.m30 + a.m11*b.m31 + a.m21*b.m32 + a.m31*b.m33;

    ret.m20 = a.m02*b.m00 + a.m12*b.m01 + a.m22*b.m02 + a.m32*b.m03;
    ret.m21 = a.m02*b.m10 + a.m12*b.m11 + a.m22*b.m12 + a.m32*b.m13;
    ret.m22 = a.m02*b.m20 + a.m12*b.m21 + a.m22*b.m22 + a.m32*b.m23;
    ret.m23 = a.m02*b.m30 + a.m12*b.m31 + a.m22*b.m32 + a.m32*b.m33;

    ret.m30 = a.m03*b.m00 + a.m13*b.m01 + a.m23*b.m02 + a.m33*b.m03;
    ret.m31 = a.m03*b.m10 + a.m13*b.m11 + a.m23*b.m12 + a.m33*b.m13;
    ret.m32 = a.m03*b.m20 + a.m13*b.m21 + a.m23*b.m22 + a.m33*b.m23;
    ret.m33 = a.m03*b.m30 + a.m13*b.m31 + a.m23*b.m32 + a.m33*b.m33;
    return ret;
}

Mat4f
mat4fMulP(Mat4f const *a, Mat4f const *b) {
    Mat4f ret;
    ret.m00 = a->m00*b->m00 + a->m10*b->m01 + a->m20*b->m02 + a->m30*b->m03;
    ret.m01 = a->m00*b->m10 + a->m10*b->m11 + a->m20*b->m12 + a->m30*b->m13;
    ret.m02 = a->m00*b->m20 + a->m10*b->m21 + a->m20*b->m22 + a->m30*b->m23;
    ret.m03 = a->m00*b->m30 + a->m10*b->m31 + a->m20*b->m32 + a->m30*b->m33;

    ret.m10 = a->m01*b->m00 + a->m11*b->m01 + a->m21*b->m02 + a->m31*b->m03;
    ret.m11 = a->m01*b->m10 + a->m11*b->m11 + a->m21*b->m12 + a->m31*b->m13;
    ret.m12 = a->m01*b->m20 + a->m11*b->m21 + a->m21*b->m22 + a->m31*b->m23;
    ret.m13 = a->m01*b->m30 + a->m11*b->m31 + a->m21*b->m32 + a->m31*b->m33;

    ret.m20 = a->m02*b->m00 + a->m12*b->m01 + a->m22*b->m02 + a->m32*b->m03;
    ret.m21 = a->m02*b->m10 + a->m12*b->m11 + a->m22*b->m12 + a->m32*b->m13;
    ret.m22 = a->m02*b->m20 + a->m12*b->m21 + a->m22*b->m22 + a->m32*b->m23;
    ret.m23 = a->m02*b->m30 + a->m12*b->m31 + a->m22*b->m32 + a->m32*b->m33;

    ret.m30 = a->m03*b->m00 + a->m13*b->m01 + a->m23*b->m02 + a->m33*b->m03;
    ret.m31 = a->m03*b->m10 + a->m13*b->m11 + a->m23*b->m12 + a->m33*b->m13;
    ret.m32 = a->m03*b->m20 + a->m13*b->m21 + a->m23*b->m22 + a->m33*b->m23;
    ret.m33 = a->m03*b->m30 + a->m13*b->m31 + a->m23*b->m32 + a->m33*b->m33;
    return ret;
}

void
mat4fMulPP(Mat4f *t, Mat4f const *a, Mat4f const *b) {
    t->m00 = a->m00*b->m00 + a->m10*b->m01 + a->m20*b->m02 + a->m30*b->m03;
    t->m01 = a->m00*b->m10 + a->m10*b->m11 + a->m20*b->m12 + a->m30*b->m13;
    t->m02 = a->m00*b->m20 + a->m10*b->m21 + a->m20*b->m22 + a->m30*b->m23;
    t->m03 = a->m00*b->m30 + a->m10*b->m31 + a->m20*b->m32 + a->m30*b->m33;

    t->m10 = a->m01*b->m00 + a->m11*b->m01 + a->m21*b->m02 + a->m31*b->m03;
    t->m11 = a->m01*b->m10 + a->m11*b->m11 + a->m21*b->m12 + a->m31*b->m13;
    t->m12 = a->m01*b->m20 + a->m11*b->m21 + a->m21*b->m22 + a->m31*b->m23;
    t->m13 = a->m01*b->m30 + a->m11*b->m31 + a->m21*b->m32 + a->m31*b->m33;

    t->m20 = a->m02*b->m00 + a->m12*b->m01 + a->m22*b->m02 + a->m32*b->m03;
    t->m21 = a->m02*b->m10 + a->m12*b->m11 + a->m22*b->m12 + a->m32*b->m13;
    t->m22 = a->m02*b->m20 + a->m12*b->m21 + a->m22*b->m22 + a->m32*b->m23;
    t->m23 = a->m02*b->m30 + a->m12*b->m31 + a->m22*b->m32 + a->m32*b->m33;

    t->m30 = a->m03*b->m00 + a->m13*b->m01 + a->m23*b->m02 + a->m33*b->m03;
    t->m31 = a->m03*b->m10 + a->m13*b->m11 + a->m23*b->m12 + a->m33*b->m13;
    t->m32 = a->m03*b->m20 + a->m13*b->m21 + a->m23*b->m22 + a->m33*b->m23;
    t->m33 = a->m03*b->m30 + a->m13*b->m31 + a->m23*b->m32 + a->m33*b->m33;
}

#define BENCH_VEC_N 1000000
#define BENCH_MAT_N 1000000
#define BENCH_BENCHMARKS_N 5

Vec3 *dataVec;
Vec3 *dataVecV;
Vec3 *dataVecP;
Vec3 *dataVecPP;

Mat4f *dataMat;
Mat4f *dataMatV;
Mat4f *dataMatP;
Mat4f *dataMatPP;

float vTimeVec = 0;
float pTimeVec = 0;
float ppTimeVec = 0;

float vTimeMat = 0;
float pTimeMat = 0;
float ppTimeMat = 0;

void runBenchmarks() {
    float startTime;
    float endTime;
    float timeElapsed;

    // VECTORS
    // test passing by value
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_VEC_N - 1 ; i++) {
        dataVecV[i] = vec3Normalize(vec3CrossProduct(dataVec[i], dataVec[i+1]));
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    vTimeVec += timeElapsed;
    printf("Vector: Passing by value: %f\n", timeElapsed);

    // test passing parameters by pointer
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_VEC_N - 1 ; i++) {
        dataVecP[i] = vec3CrossProductP(&dataVec[i], &dataVec[i+1]);
        dataVecP[i] = vec3NormalizeP(&dataVecP[i]);
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    pTimeVec += timeElapsed;
    printf("Vector: Passing by pointer: %f\n", timeElapsed);

    // test passing parameters and return value by pointer
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_VEC_N - 1 ; i++) {
        vec3CrossProductPP(&dataVecPP[i], &dataVec[i], &dataVec[i+1]);
        vec3NormalizePP(&dataVecPP[i], &dataVecPP[i]);
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    ppTimeVec += timeElapsed;
    printf("Vector: Passing parameters and return value by pointer: %f\n", timeElapsed);

    // prevent optimization by printing a random value from the data
    int rR = rand() % BENCH_VEC_N;
    printf("These values should be equal: %f %f %f\n\n", dataVecV[rR].x, dataVecP[rR].x, dataVecPP[rR].x);

    // MATRICES
    // test passing by value
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_MAT_N - 1 ; i++) {
        dataMatV[i] = mat4fMul(dataMat[i], dataMat[i+1]);
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    vTimeMat += timeElapsed;
    printf("Matrix: Passing by value: %f\n", timeElapsed);

    // test passing parameters by pointer
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_MAT_N - 1 ; i++) {
        dataMatP[i] = mat4fMulP(&dataMat[i], &dataMat[i+1]);
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    pTimeMat += timeElapsed;
    printf("Matrix: Passing by pointer: %f\n", timeElapsed);

    // test passing parameters and return value by pointer
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_MAT_N - 1 ; i++) {
        mat4fMulPP(&dataMatPP[i], &dataMat[i], &dataMat[i+1]);
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    ppTimeMat += timeElapsed;
    printf("Matrix: Passing parameters and return value by pointer: %f\n", timeElapsed);

    // prevent optimization by printing a random value from the data
    rR = rand() % BENCH_MAT_N;
    printf("These values should be equal: %f %f %f\n", dataMatV[rR].m00, dataMatP[rR].m00, dataMatPP[rR].m00);
}

int main() {
    dataVec = malloc(BENCH_VEC_N * sizeof(Vec3));
    dataVecV = malloc(BENCH_VEC_N * sizeof(Vec3));
    dataVecP = malloc(BENCH_VEC_N * sizeof(Vec3));
    dataVecPP = malloc(BENCH_VEC_N * sizeof(Vec3));

    dataMat = malloc(BENCH_MAT_N * sizeof(Mat4f));
    dataMatV = malloc(BENCH_MAT_N * sizeof(Mat4f));
    dataMatP = malloc(BENCH_MAT_N * sizeof(Mat4f));
    dataMatPP = malloc(BENCH_MAT_N * sizeof(Mat4f));

    for (int i = 0 ; i < BENCH_VEC_N ; i++) {
        dataVec[i].x = rand();
        dataVec[i].y = rand();
        dataVec[i].z = rand();
    }
    for (int i = 0 ; i < BENCH_MAT_N ; i++) {
        dataMat[i].m00 = rand();
        dataMat[i].m11 = rand();
        dataMat[i].m32 = rand();
    }

    for (int i = 0 ; i < BENCH_BENCHMARKS_N ; i++) {
        runBenchmarks();
    }

    printf("Vec average time:\n");
    printf(" - Parameters by value, return by value: %f\n", vTimeVec / BENCH_BENCHMARKS_N);
    printf(" - Parameters by pointer, return by value: %f\n", pTimeVec / BENCH_BENCHMARKS_N);
    printf(" - Parameters by pointer, return by pointer: %f\n", ppTimeVec / BENCH_BENCHMARKS_N);

    printf("Mat average time:\n");
    printf(" - Parameters by value, return by value: %f\n", vTimeMat / BENCH_BENCHMARKS_N);
    printf(" - Parameters by pointer, return by value: %f\n", pTimeMat / BENCH_BENCHMARKS_N);
    printf(" - Parameters by pointer, return by pointer: %f\n", ppTimeMat / BENCH_BENCHMARKS_N);

}
