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


#define BENCH_VEC_N 5000000
#define BENCH_BENCHMARKS_N 5

Vec3 *data;
Vec3 *dataV;
Vec3 *dataP;
Vec3 *dataPP;

float vTime = 0;
float pTime = 0;
float ppTime = 0;

void runBenchmarks() {
    float startTime;
    float endTime;
    float timeElapsed;

    // test passing by value
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_VEC_N - 1 ; i++) {
        dataV[i] = vec3Normalize(vec3CrossProduct(data[i], data[i+1]));
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    vTime += timeElapsed;
    printf("Passing by value: %f\n", timeElapsed);

    // test passing parameters by pointer
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_VEC_N - 1 ; i++) {
        dataP[i] = vec3CrossProductP(&data[i], &data[i+1]);
        dataP[i] = vec3NormalizeP(&dataP[i]);
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    pTime += timeElapsed;
    printf("Passing by pointer: %f\n", timeElapsed);

    // test passing parameters and return value by pointer
    startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i = 0 ; i < BENCH_VEC_N - 1 ; i++) {
        vec3CrossProductPP(&dataPP[i], &data[i], &data[i+1]);
        vec3NormalizePP(&dataPP[i], &dataPP[i]);
    }
    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    ppTime += timeElapsed;
    printf("Passing parameters and return value by pointer: %f\n", timeElapsed);

    // prevent optimization by printing a random value from the data
    int rR = rand() % BENCH_VEC_N;
    printf("These values should be equal: %f %f %f\n", dataV[rR].x, dataP[rR].x, dataPP[rR].x);
}

int main() {
    data = malloc(BENCH_VEC_N * sizeof(Vec3));
    dataV = malloc(BENCH_VEC_N * sizeof(Vec3));
    dataP = malloc(BENCH_VEC_N * sizeof(Vec3));
    dataPP = malloc(BENCH_VEC_N * sizeof(Vec3));

    for (int i = 0 ; i < BENCH_VEC_N ; i++) {
        data[i].x = rand();
        data[i].y = rand();
        data[i].z = rand();
    }

    for (int i = 0 ; i < BENCH_BENCHMARKS_N ; i++) {
        runBenchmarks();
    }

    printf("Average time:\n");
    printf(" - Parameters by value, return by value: %f\n", vTime / BENCH_BENCHMARKS_N);
    printf(" - Parameters by pointer, return by value: %f\n", pTime / BENCH_BENCHMARKS_N);
    printf(" - Parameters by pointer, return by pointer: %f\n", ppTime / BENCH_BENCHMARKS_N);

}
