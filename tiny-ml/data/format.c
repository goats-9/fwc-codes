#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_SAMPLES 30
#define NUM_GAP 10
#define NUM_GESTURES 100
#define ACC_THR 30.0

FILE *dst;

void process(FILE *afile, FILE *gfile, int tgt) { 
    char h1[100];
    fscanf(afile, "%s", h1);
    fscanf(gfile, "%s", h1);
    double time, el, ax, ay, az, gx, gy, gz;
    int ng = 0;
    while (ng < NUM_GESTURES && fscanf(afile, "%lf,%lf,%lf,%lf,%lf", &time, &el, &az, &ay, &ax) != -1) {
        fscanf(gfile, "%lf,%lf,%lf,%lf,%lf", &time, &el, &gz, &gy, &gx);
        if (fabs(ax) + fabs(ay) + fabs(az) < ACC_THR) continue;
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
    dst = fopen("data.csv", "w");
    for(int i = 0; i < NUM_SAMPLES; i++) {
        fprintf(dst, "ax%d,ay%d,az%d,gx%d,gy%d,gz%d,", i, i, i, i, i, i);
    }
    fprintf(dst, "target\n");
    process(ach, gch, 0);
    process(awr, gwr, 1);
    fclose(ach), fclose(gch), fclose(awr), fclose(gwr), fclose(dst);
    return 0;
}
