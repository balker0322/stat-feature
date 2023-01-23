#ifndef D54FBF41_3E70_410E_9E44_F317E74DE4E8
#define D54FBF41_3E70_410E_9E44_F317E74DE4E8

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

double** allocate_array(int*);
void free_array(double**, int*);
void print_array(double**, int, int);
void get_statistical_features(double**, int*, double**);
double calculate_mean(double*, int);
double calculate_stdev(double*, int, double, bool);
double calculate_mode(double*, int);
double calculate_zero_cross(double*, int);
void calculate_skewness_and_kurtosis(double*, int, double, double*, double*);
void sort_array(double*, double*, int);
int get_sign(double);
void swap_num(double*, double*);


#endif /* D54FBF41_3E70_410E_9E44_F317E74DE4E8 */
