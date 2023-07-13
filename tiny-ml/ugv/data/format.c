#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_SAMPLES 20
#define NUM_GAP 5
#define NUM_GESTURES_TRAIN 60
#define NUM_GESTURES_TEST 20
#define NUM_GESTURES (NUM_GESTURES_TRAIN + NUM_GESTURES_TEST)
#define DIM_OUTPUT 4

FILE *train_dst, *test_dst;

void process(char *ofile, int tgt) {
    FILE *optr = fopen(ofile, "r");
    char h1[200];
    fscanf(optr, "%s", h1);
    double r, p, y;
    int ng = 0;
    FILE *dst;
    while (ng < NUM_GESTURES && fscanf(optr, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &r, &r, &r, &r, &r, &r, &r, &p, &y) != -1) {
        if (ng < NUM_GESTURES_TRAIN) dst = train_dst;
        else dst = test_dst;
        fprintf(dst, "%lf,%lf,%lf,", r, p, y);
        for (int i = 1; i < NUM_SAMPLES; i++) {
            fscanf(optr, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &r, &r, &r, &r, &r, &r, &r, &p, &y);
            fprintf(dst, "%lf,%lf,%lf,", r, p, y);
        }
        fprintf(dst, "%d\n", tgt);
        for (int i = 0; i < NUM_GAP; i++) fscanf(optr, "%s", h1);
        ++ng;
    }
    fclose(optr);
}

int main() {
    train_dst = fopen("train.csv", "w");
    test_dst = fopen("test.csv", "w");
    for(int i = 0; i < NUM_SAMPLES; i++) {
        fprintf(train_dst, "r%d,p%d,y%d,", i, i, i);
        fprintf(test_dst, "r%d,p%d,y%d,", i, i, i);
    }
    fprintf(train_dst, "target\n");
    fprintf(test_dst, "target\n");
    process("Forward.csv", 0);
    process("Right.csv", 1);
    process("Reverse.csv", 2);
    process("Left.csv", 3);
    process("Stop.csv", 4);
    return 0;
}
