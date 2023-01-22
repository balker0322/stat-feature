
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** allocate_array(int*);
void free_array(double**, int*);
void print_array(double**, int, int);
void get_statistical_features(double**, int*, double**);
double calculate_mean(double*, int);
double calculate_stdev(double*, int);
double calculate_mode(double*, int);
double calculate_zero_cross(double*, int);
void calculate_skewness_and_kurtosis(double*, int, double*, double*);
void sort_array(double*, double*, int);
int get_sign(double);


double** allocate_array(int* shape) {
    double** array = (double**)malloc(sizeof(double*)*shape[0]);
    int i;
    for (i=0; i<shape[0]; i++) {
        array[i] = (double*)malloc(sizeof(double)*shape[1]);
    }
    return array;
}

void free_array(double** array, int* shape) {
    int i;
    for (i=0; i<shape[0]; i++) {
        free(array[i]);
    }
    free(array);
}

void print_array(double** array, int dim0, int dim1) {
    int i;
    for (i=0; i<dim0; i++) {
        for (int j=0; j<dim1; j++) {
            printf("%f ", array[i][j]);
        }
        printf("\n");
    }
}

double calculate_mean(double* data, int size) {
    double result = 0.0;
    int i;
    for (i=0; i<size; i++) {
        result += (data[i] / ((double)size));
    }
    return result;
}

double calculate_stdev(double* data, int size) {
    double mean = calculate_mean(data, size);
    double result = 0.0;
    int i;

    for (i=0; i<size; i++) {
        result += pow(data[i] - mean, 2);
    }

    return sqrt(result / ((double)size));
}

double calculate_mode(double* data, int size) {
    long previous_value, current_value;
    double result = 0.0;
    double* sorted_data = (double*)malloc(size*sizeof(double));
    int i, current_counter=0, max_count=0;

    sort_array(data, sorted_data, size);

    for (i=0; i<size; i++) {
        if (i==0) {
            previous_value = (long)round(data[i]*1000000);
            result = previous_value;
            continue;
        }
        current_value = (long)round(data[i]*1000000);
        if (current_value == previous_value) {
            current_counter+=1;
            if (current_counter>max_count) {
                max_count = current_counter;
                result = current_value;
            }
            previous_value = current_value;
            continue;
        }
        current_counter=0;
        previous_value = current_value;
    }

    free(sorted_data);

    return (double)(result/1000000.0);
}

double calculate_zero_cross(double* data, int size) {
    int i, current_sign, previous_sign, zero_cross_counter=0;

    for (i=0; i<size; i++) {
        if (i==0) {
            previous_sign = get_sign(data[i]);
            continue;
        }
        current_sign = get_sign(data[i]);
        if (current_sign != previous_sign) {
            zero_cross_counter += 1;
        }
        previous_sign = current_sign;
    }

    return (double)zero_cross_counter;
}

void calculate_skewness_and_kurtosis(double*, int, double*, double*) {
    // todo
}

void sort_array(double* source, double* result, int size) {
    int i=0;
    short swap_occur = 1;
    double temp_num;

    for (i=0; i<size; i++) {
        result[i] = source[i];
    }

    while (swap_occur == 1) {
        swap_occur = 0;
        for (i=0; i<size-1; i++) {
            if (result[i] > result[i+1]) {
                swap_occur = 1;
                temp_num = result[i];
                result[i] = result[i+1];
                result[i+1] = temp_num;
            }
        }
    }

}

int get_sign(double num) {
    if (num < 0.0) return -1;
    if (num > 0.0) return 1;
    return 0;
}


void get_statistical_features(double** data, int* shape, double** statistical_features) {
    double mean, stdev, mode, zero_cross, skewness, kurtosis;
    int i;

    for (i=0; i<shape[0]; i++) {
        mean = calculate_mean(data[i], shape[1]);
        stdev = calculate_stdev(data[i], shape[1]);
        mode = calculate_mode(data[i], shape[1]);
        zero_cross = calculate_zero_cross(data[i], shape[1]);
        calculate_skewness_and_kurtosis(data[i], shape[1], &skewness, &kurtosis);

        statistical_features[i][0] = mean;
        statistical_features[i][1] = stdev;
        statistical_features[i][2] = mode;
        statistical_features[i][3] = zero_cross;
        statistical_features[i][4] = skewness;
        statistical_features[i][5] = kurtosis;
    }
}

int main() {
    int size_dim0, size_dim1;
    int statistical_feature_count = 6;
    int data_shape[] = {2, 10000};
    int statistical_features_shape[] = {data_shape[0], statistical_feature_count};
    double** data = allocate_array(data_shape);
    double** statistical_features = allocate_array(statistical_features_shape);

    size_dim0 = 1;
    size_dim1 = 2;
    print_array(data_shape, size_dim0, size_dim1);
    get_statistical_features(data, data_shape, statistical_features);

    size_dim0 = statistical_features_shape[0];
    size_dim1 = statistical_features_shape[1];
    print_array(statistical_features, size_dim0, size_dim1);

    free_array(data, data_shape);
    free_array(statistical_features, statistical_features_shape);

    return 0;
}
