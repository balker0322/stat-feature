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

void calculate_skewness_and_kurtosis(double* data, int size, double* skewness, double* kurtosis) {
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
                swap_num(&result[i], &result[i+1]);
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

int main_dummy() {
    int size_dim0, size_dim1;
    int statistical_feature_count = 6;
    int data_shape[] = {2, 10000};
    int statistical_features_shape[] = {data_shape[0], statistical_feature_count};
    double** data = allocate_array(data_shape);
    double** statistical_features = allocate_array(statistical_features_shape);

    size_dim0 = 1;
    size_dim1 = 2;
    print_array(data, size_dim0, size_dim1);
    get_statistical_features(data, data_shape, statistical_features);

    size_dim0 = statistical_features_shape[0];
    size_dim1 = statistical_features_shape[1];
    print_array(statistical_features, size_dim0, size_dim1);

    free_array(data, data_shape);
    free_array(statistical_features, statistical_features_shape);

    return 0;
}

int main() {
    double value[] = {1.0, 2.0, 1.0, 4.0, 2.0, 1.0};
    int data_shape[] = {1, sizeof(value)/sizeof(value[0])};
    double** data = allocate_array(data_shape);
    double** s_data = allocate_array(data_shape);
    int i;
    for(i=0;i<data_shape[1];i++){
        data[0][i]=value[i];
    }
    // data[0] = {1.0, 2.0, 3.0};
    // data[0][0] = value[0];
    // data[0][1] = value[1];
    // data[0][2] = value[2];
    // data[1][0] = value[3];
    // data[1][1] = value[4];
    // data[1][2] = value[5];
    sort_array(data[0], s_data[0], data_shape[1]);
    print_array(data, data_shape[0], data_shape[1]);
    print_array(s_data, data_shape[0], data_shape[1]);

    printf("mean: %f\n", calculate_mean(data[0], data_shape[1]));
    printf("mode: %f\n", calculate_mode(data[0], data_shape[1]));

    double a=1.0, b=2.0;

    printf("a=%f, b=%f\n", a, b);
    swap_num(&a, &b);
    printf("a=%f, b=%f\n", a, b);

    free_array(data, data_shape);
    return 0;
}
