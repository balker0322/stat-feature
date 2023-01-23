#include "main.h"


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

double calculate_stdev(double* data, int size, double mean, bool unbiased) {
    double result = 0.0, n;
    int i;

    n = (double)size;
    if (unbiased) {
        n-=1.0;
    }

    for (i=0; i<size; i++) {
        result += pow(data[i] - mean, 2);
    }

    return sqrt(result / n);
}

double calculate_mode(double* data, int size) {
    int previous_value=0, current_value;
    double result = 0.0;
    double* sorted_data = (double*)malloc(size*sizeof(double));
    int i, current_counter=1, max_count=1;

    sort_array(data, sorted_data, size);

    for (i=0; i<size; i++) {
        current_value = (int)round(sorted_data[i]*1000000);
        if (i==0) {
            previous_value = current_value;
            result = current_value;
            continue;
        }
        if (current_value == previous_value) {
            current_counter+=1;
            if (current_counter>max_count) {
                max_count = current_counter;
                result = current_value;
            }
            previous_value = current_value;
            continue;
        }
        current_counter=1;
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

void calculate_skewness_and_kurtosis(double* data, int size, double mean, double* skewness, double* kurtosis) {
    int i;
    double stdev = calculate_stdev(data, size, mean, false);
    double temp_val, z_score;

    *skewness = 0.0;
    *kurtosis = 0.0;

    for (i=0; i<size; i++) {
        z_score = (data[i]-mean)/stdev;
        temp_val = pow(z_score, 3)/((double)size);
        *skewness += temp_val;
        *kurtosis += (temp_val*z_score);
    }
}

void sort_array(double* source, double* result, int size) {
    int i=0;
    bool swap_occur = true;

    for (i=0; i<size; i++) {
        result[i] = source[i];
    }

    while (swap_occur == 1) {
        swap_occur = false;
        for (i=0; i<size-1; i++) {
            if (result[i] > result[i+1]) {
                swap_num(&result[i], &result[i+1]);
                swap_occur = true;
            }
        }
    }
}

int get_sign(double num) {
    if (num < 0.0) return -1;
    if (num > 0.0) return 1;
    return 0;
}

void swap_num(double* a, double* b) {
    double temp_num = *a;
    *a = *b;
    *b = temp_num;
}

double rand_uniform(void) {
    // Generate random variable from interval (0,1]
    double result = 0.0;
    while (result==0.0) {
        result = (double)rand() / (double)RAND_MAX;
    }
    return result;
}

double rand_normal(void) {
    // Using Box-Muller transform to convert uniform random into normal distribution w/ standard deviation = 1
    double PI = 3.14159;
    double r, theta, x;
    double mean = 0.0;
    double stdev = 1.0;

    r = sqrt(-2.0*log(rand_uniform()));
    theta = 2.0*PI*rand_uniform();
    x = r*cos(theta);

    return (x * stdev) + mean;
}

void set_random_normal(double** data, int* shape) {
    int i, j;

    for (i=0; i<shape[0]; i++) {
        for (j=0; j<shape[1]; j++) {
            data[i][j] = rand_normal();
        }
    }
}

void get_statistical_features(double** data, int* shape, double** statistical_features) {
    double mean, stdev, mode, zero_cross, skewness, kurtosis;
    int i;

    for (i=0; i<shape[0]; i++) {
        mean = calculate_mean(data[i], shape[1]);
        stdev = calculate_stdev(data[i], shape[1], mean, true);
        mode = calculate_mode(data[i], shape[1]);
        zero_cross = calculate_zero_cross(data[i], shape[1]);
        calculate_skewness_and_kurtosis(data[i], shape[1], mean, &skewness, &kurtosis);

        statistical_features[i][0] = mean;
        statistical_features[i][1] = mode;
        statistical_features[i][2] = stdev;
        statistical_features[i][3] = zero_cross;
        statistical_features[i][4] = skewness;
        statistical_features[i][5] = kurtosis;
    }
}

int main() {
    int i;
    int statistical_feature_count = 6;
    int data_shape[] = {2, 10000};
    int statistical_features_shape[] = {data_shape[0], statistical_feature_count};
    double** data = allocate_array(data_shape);
    double** statistical_features = allocate_array(statistical_features_shape);

    set_random_normal(data, data_shape);

    printf("shape: (%d, %d)\n", data_shape[0], data_shape[1]);
    get_statistical_features(data, data_shape, statistical_features);

    for (i=0; i<data_shape[0]; i++) {
        printf("\nVariable %d\n", i+1);
        printf("mean: %f\n", statistical_features[i][0]);
        printf("mode: %f\n", statistical_features[i][1]);
        printf("stdev: %f\n", statistical_features[i][2]);
        printf("zero_cross: %f\n", statistical_features[i][3]);
        printf("skewness: %f\n", statistical_features[i][4]);
        printf("kurtosis: %f\n", statistical_features[i][5]);
    }

    free_array(data, data_shape);
    free_array(statistical_features, statistical_features_shape);

    return 0;
}
