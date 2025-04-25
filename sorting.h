#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h> // Add this line for the log() function

// Struktur untuk mengukur waktu dan memori
typedef struct {
    double execution_time;
    size_t memory_usage;
} PerformanceMetrics;

// Bubble Sort
// Prinsip kerja: Membandingkan dua elemen bersebelahan dan menukar posisinya jika tidak sesuai urutan.
// Proses ini diulang hingga tidak ada lagi pertukaran yang dilakukan (array terurut).
// Kompleksitas waktu: O(n²) - Worst case, Average case, Best case: O(n) jika sudah terurut
void bubbleSortInt(int arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    for (int i = 0; i < n-1; i++) {
        int swapped = 0;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
            }
        }
        // Jika tidak ada pertukaran dalam satu iterasi, array sudah terurut
        if (swapped == 0)
            break;
    }

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    metrics->memory_usage = n * sizeof(int); // Memori yang digunakan hanya untuk array
}

void bubbleSortString(char *arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    for (int i = 0; i < n-1; i++) {
        int swapped = 0;
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                // Swap elements
                char *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
            }
        }
        // Jika tidak ada pertukaran dalam satu iterasi, array sudah terurut
        if (swapped == 0)
            break;
    }

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Perkiraan penggunaan memori (array pointer + panjang string)
    size_t memUsage = n * sizeof(char*);
    for (int i = 0; i < n; i++) {
        memUsage += strlen(arr[i]) + 1; // +1 untuk null terminator
    }
    metrics->memory_usage = memUsage;
}

// Selection Sort
// Prinsip kerja: Mencari elemen terkecil dari bagian yang belum terurut dan menempatkannya
// di posisi awal bagian belum terurut. Proses ini diulang hingga seluruh array terurut.
// Kompleksitas waktu: O(n²) - Worst case, Average case, Best case
void selectionSortInt(int arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    for (int i = 0; i < n-1; i++) {
        // Temukan elemen minimum dalam array yang belum terurut
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap elemen minimum dengan elemen pertama
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    metrics->memory_usage = n * sizeof(int);
}

void selectionSortString(char *arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    for (int i = 0; i < n-1; i++) {
        // Temukan elemen minimum dalam array yang belum terurut
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        // Swap elemen minimum dengan elemen pertama
        if (min_idx != i) {
            char *temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Perkiraan penggunaan memori
    size_t memUsage = n * sizeof(char*);
    for (int i = 0; i < n; i++) {
        memUsage += strlen(arr[i]) + 1;
    }
    metrics->memory_usage = memUsage;
}

// Insertion Sort
// Prinsip kerja: Membagi array menjadi bagian terurut dan belum terurut. Setiap elemen
// dari bagian yang belum terurut diambil dan ditempatkan pada posisi yang tepat di bagian terurut.
// Kompleksitas waktu: O(n²) - Worst case, Average case, Best case: O(n) jika sudah hampir terurut
void insertionSortInt(int arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Geser elemen yang lebih besar dari key ke posisi satu indeks di depannya
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    metrics->memory_usage = n * sizeof(int);
}

void insertionSortString(char *arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;

        // Geser elemen yang lebih besar dari key ke posisi satu indeks di depannya
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Perkiraan penggunaan memori
    size_t memUsage = n * sizeof(char*);
    for (int i = 0; i < n; i++) {
        memUsage += strlen(arr[i]) + 1;
    }
    metrics->memory_usage = memUsage;
}

// Merge Sort
// Prinsip kerja: Algoritma divide-and-conquer yang membagi array menjadi dua bagian,
// mengurutkan kedua bagian secara rekursif, lalu menggabungkan kedua bagian yang telah terurut.
// Kompleksitas waktu: O(n log n) - Worst case, Average case, Best case
void mergeInt(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Buat array sementara
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    // Salin data ke array sementara
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Gabungkan array sementara kembali ke arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Salin elemen yang tersisa dari L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Salin elemen yang tersisa dari R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSortIntHelper(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSortIntHelper(arr, l, m);
        mergeSortIntHelper(arr, m + 1, r);

        mergeInt(arr, l, m, r);
    }
}

void mergeSortInt(int arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    mergeSortIntHelper(arr, 0, n - 1);

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // Memori tambahan yang digunakan saat proses merge adalah O(n)
    metrics->memory_usage = 2 * n * sizeof(int); // Array asli + tambahan untuk merge
}

void mergeString(char *arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Buat array sementara
    char **L = (char**)malloc(n1 * sizeof(char*));
    char **R = (char**)malloc(n2 * sizeof(char*));

    // Salin data ke array sementara
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Gabungkan array sementara kembali ke arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Salin elemen yang tersisa dari L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Salin elemen yang tersisa dari R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSortStringHelper(char *arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSortStringHelper(arr, l, m);
        mergeSortStringHelper(arr, m + 1, r);

        mergeString(arr, l, m, r);
    }
}

void mergeSortString(char *arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    mergeSortStringHelper(arr, 0, n - 1);

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Perkiraan penggunaan memori (array asli + tambahan untuk merge)
    size_t memUsage = n * sizeof(char*);
    for (int i = 0; i < n; i++) {
        memUsage += strlen(arr[i]) + 1;
    }
    memUsage += n * sizeof(char*); // Tambahan untuk array sementara
    metrics->memory_usage = memUsage;
}

// Quick Sort
// Prinsip kerja: Algoritma divide-and-conquer yang memilih pivot (elemen pembagi),
// mempartisi array sedemikian rupa sehingga elemen yang lebih kecil dari pivot berada
// di sebelah kiri pivot dan elemen yang lebih besar berada di sebelah kanan, lalu
// mengurutkan kedua bagian tersebut secara rekursif.
// Kompleksitas waktu: O(n²) - Worst case, O(n log n) - Average case, Best case
int partitionInt(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortIntHelper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionInt(arr, low, high);

        quickSortIntHelper(arr, low, pi - 1);
        quickSortIntHelper(arr, pi + 1, high);
    }
}

void quickSortInt(int arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    quickSortIntHelper(arr, 0, n - 1);

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // Memori tambahan yang digunakan untuk stack rekursif adalah O(log n) rata-rata
    metrics->memory_usage = n * sizeof(int) + (int)(log(n) / log(2)) * sizeof(int);
}

int partitionString(char *arr[], int low, int high) {
    char *pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            // Swap
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap
    char *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortStringHelper(char *arr[], int low, int high) {
    if (low < high) {
        int pi = partitionString(arr, low, high);

        quickSortStringHelper(arr, low, pi - 1);
        quickSortStringHelper(arr, pi + 1, high);
    }
}

void quickSortString(char *arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    quickSortStringHelper(arr, 0, n - 1);

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Perkiraan penggunaan memori
    size_t memUsage = n * sizeof(char*);
    for (int i = 0; i < n; i++) {
        memUsage += strlen(arr[i]) + 1;
    }
    memUsage += (int)(log(n) / log(2)) * sizeof(char*); // Stack recursion
    metrics->memory_usage = memUsage;
}

// Shell Sort
// Prinsip kerja: Variasi dari insertion sort yang membandingkan elemen yang jauh terpisah,
// lalu mengurangi jarak (gap) hingga menjadi 1. Urutan pengurangan gap mempengaruhi kinerja algoritma.
// Kompleksitas waktu: Tergantung pada urutan gap, tetapi umumnya O(n^(3/2)) atau O(n^(4/3))
void shellSortInt(int arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            // Shift earlier gap-sorted elements up until the correct location for arr[i] is found
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            // Put temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    metrics->memory_usage = n * sizeof(int);
}

void shellSortString(char *arr[], int n, PerformanceMetrics *metrics) {
    clock_t start = clock();

    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j;

            // Shift earlier gap-sorted elements up until the correct location for arr[i] is found
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }

            // Put temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }

    clock_t end = clock();
    metrics->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Perkiraan penggunaan memori
    size_t memUsage = n * sizeof(char*);
    for (int i = 0; i < n; i++) {
        memUsage += strlen(arr[i]) + 1;
    }
    metrics->memory_usage = memUsage;
}

// Functions for generating test data
void generate_random_numbers(const char *filename, int count, int max_value) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File tidak dapat dibuka");
        return;
    }

    srand(time(NULL)); // Inisialisasi seed
    for (int i = 0; i < count; i++) {
        int num = rand() % max_value;
        fprintf(fp, "%d\n", num);
    }

    fclose(fp);
}

void random_word(char *word, int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        word[i] = charset[key];
    }
    word[length] = '\0';
}

void generate_random_words(const char *filename, int count, int max_word_length) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File tidak dapat dibuka");
        return;
    }

    srand(time(NULL));
    char word[100];
    for (int i = 0; i < count; i++) {
        int length = (rand() % (max_word_length - 3)) + 3; // panjang kata minimal 3
        random_word(word, length);
        fprintf(fp, "%s\n", word);
    }

    fclose(fp);
}

// Functions to load data for testing
int* loadIntData(const char* filename, int size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    int* data = (int*)malloc(size * sizeof(int));
    if (!data) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%d", &data[i]) != 1) {
            if (feof(file)) {
                printf("Warning: End of file reached before reading %d items.\n", size);
            } else {
                printf("Error reading from file.\n");
            }
            break;
        }
    }

    fclose(file);
    return data;
}

char** loadStringData(const char* filename, int size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char** data = (char**)malloc(size * sizeof(char*));
    if (!data) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    char buffer[100];
    for (int i = 0; i < size; i++) {
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            // Remove trailing newline if present
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
            }

            data[i] = strdup(buffer);
            if (!data[i]) {
                perror("Memory allocation failed");
                // Free previously allocated memory
                for (int j = 0; j < i; j++) {
                    free(data[j]);
                }
                free(data);
                fclose(file);
                return NULL;
            }
        } else {
            if (feof(file)) {
                printf("Warning: End of file reached before reading %d items.\n", size);
            } else {
                printf("Error reading from file.\n");
            }
            break;
        }
    }

    fclose(file);
    return data;
}

void freeStringData(char** data, int size) {
    if (data) {
        for (int i = 0; i < size; i++) {
            if (data[i]) {
                free(data[i]);
            }
        }
        free(data);
    }
}

#endif /* SORTING_H */