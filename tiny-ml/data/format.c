#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_SAMPLES 40
#define NUM_GAP 10
#define NUM_GESTURES_TRAIN 80
#define NUM_GESTURES_TEST 20
#define NUM_GESTURES (NUM_GESTURES_TRAIN + NUM_GESTURES_TEST)
#define ACC_THR 30.0

FILE *train_dst, *test_dst;

void process(FILE *afile, FILE *gfile, int tgt) { 
    char h1[100];
    fscanf(afile, "%s", h1);
    fscanf(gfile, "%s", h1);
    double time, el, ax, ay, az, gx, gy, gz;
    int ng = 0;
    FILE *dst;
    while (ng < NUM_GESTURES && fscanf(afile, "%lf,%lf,%lf,%lf,%lf", &time, &el, &az, &ay, &ax) != -1) {
        fscanf(gfile, "%lf,%lf,%lf,%lf,%lf", &time, &el, &gz, &gy, &gx);
        if (fabs(ax) + fabs(ay) + fabs(az) < ACC_THR) continue;
        if (ng < NUM_GESTURES_TRAIN) dst = train_dst;
        else dst = test_dst;
        fprintf(dst, "%lf,%lf,%lf,%lf,%lf,%lf,", ax, ay, az, gx, gy, gz);
        for (int i = 1; i < NUM_SAMPLES; i++) {
            fscanf(afile, "%lf,%lf,%lf,%lf,%lf", &time, &el, &az, &ay, &ax);
            fscanf(gfile, "%lf,%lf,%lf,%lf,%lf", &time, &el, &gz, &gy, &gx);
            fprintf(dst, "%lf,%lf,%lf,%lf,%lf,%lf,", ax, ay, az, gx, gy, gz);
        }
        fprintf(dst, "%d\n", tgt);
        for (int i = 0; i < NUM_GAP; i++) {
            fscanf(afile, "%lf,%lf,%lf,%lf,%lf", &time, &el, &az, &ay, &ax);
            fscanf(gfile, "%lf,%lf,%lf,%lf,%lf", &time, &el, &gz, &gy, &gx);
        }
        ++ng;
    }
}

int main() {
    FILE *ach = fopen("acce_chop.csv", "r");
    FILE *gch = fopen("gyro_chop.csv", "r");
    FILE *awr = fopen("acce_wrist.csv", "r");
    FILE *gwr = fopen("gyro_wrist.csv", "r");
    train_dst = fopen("train.csv", "w");
    test_dst = fopen("test.csv", "w");
    for(int i = 0; i < NUM_SAMPLES; i++) {
        fprintf(train_dst, "ax%d,ay%d,az%d,gx%d,gy%d,gz%d,", i, i, i, i, i, i);
        fprintf(test_dst, "ax%d,ay%d,az%d,gx%d,gy%d,gz%d,", i, i, i, i, i, i);
    }
    fprintf(train_dst, "target\n");
    fprintf(test_dst, "target\n");
    process(ach, gch, 0);
    process(awr, gwr, 1);
    fclose(ach), fclose(gch), fclose(awr), fclose(gwr), fclose(train_dst), fclose(test_dst);
    return 0;
}
