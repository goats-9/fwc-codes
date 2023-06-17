#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_SAMPLES 20
#define NUM_GAP 10
#define NUM_GESTURES 30
#define ACC_THR 30.0

FILE *dst;

void process(FILE *afile, FILE *gfile, int tgt) { 
    char h1[5], h2[5], h3[5], h4[5];
    fscanf(afile, "%s %s %s %s", h1, h2, h3, h4);
    fscanf(gfile, "%s %s %s %s", h1, h2, h3, h4);
    double time, ax, ay, az, gx, gy, gz;
    int ng = 0;
    while (ng < NUM_GESTURES && fscanf(afile, "%lf %lf %lf %lf", &time, &ax, &ay, &az) != -1) {
        fscanf(gfile, "%lf %lf %lf %lf", &time, &gx, &gy, &gz);
        if (fabs(ax) + fabs(ay) + fabs(az) < ACC_THR) continue;
        fprintf(dst, "%lf,%lf,%lf,%lf,%lf,%lf,", ax, ay, az, gx, gy, gz);
        for (int i = 1; i < NUM_SAMPLES; i++) {
            fscanf(afile, "%lf %lf %lf %lf", &time, &gx, &gy, &gz);
            fscanf(gfile, "%lf %lf %lf %lf", &time, &gx, &gy, &gz);
            fprintf(dst, "%lf,%lf,%lf,%lf,%lf,%lf,", ax, ay, az, gx, gy, gz);
        }
        fprintf(dst, "%d\n", tgt);
        for (int i = 0; i < NUM_GAP; i++) {
            fscanf(afile, "%lf %lf %lf %lf", &time, &gx, &gy, &gz);
            fscanf(gfile, "%lf %lf %lf %lf", &time, &gx, &gy, &gz);
        }
        ++ng;
    }
}

int main() {
    FILE *ach = fopen("acce_chop.txt", "r");
    FILE *gch = fopen("gyro_chop.txt", "r");
    FILE *awr = fopen("acce_wrist.txt", "r");
    FILE *gwr = fopen("gyro_wrist.txt", "r");
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
