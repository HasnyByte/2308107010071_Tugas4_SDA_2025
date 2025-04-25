#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_DATA_SIZES 8
#define NUM_ALGORITHMS 6

// Function prototypes
void runIntegerSortingExperiments(const char* dataFile);
void runStringSortingExperiments(const char* dataFile);
void copyIntArray(int* source, int* dest, int size);
void copyStringArray(char** source, char** dest, int size);
void printSortingResultsSummary(double results[NUM_ALGORITHMS][NUM_DATA_SIZES][2], int sizeIndex, int dataSize, const char* dataType);
int getUserChoice();

int main() {
    int choice;

    printf("Generating random numbers data...\n");
    generate_random_numbers("data_angka.txt", 2000000, 2000000);

    printf("Generating random words data...\n");
    generate_random_words("data_kata.txt", 2000000, 20);

    // Get user choice for which sorting to run first
    choice = getUserChoice();

    if (choice == 1) {
        printf("Starting integer sorting experiments...\n");
        runIntegerSortingExperiments("data_angka.txt");

        printf("Starting string sorting experiments...\n");
        runStringSortingExperiments("data_kata.txt");
    } else {
        printf("Starting string sorting experiments...\n");
        runStringSortingExperiments("data_kata.txt");

        printf("Starting integer sorting experiments...\n");
        runIntegerSortingExperiments("data_angka.txt");
    }

    printf("All experiments completed successfully!\n");
    return 0;
}

// Function to get user's choice
int getUserChoice() {
    int choice = 0;
    while (choice != 1 && choice != 2) {
        printf("\nPilih jenis sorting yang ingin dijalankan terlebih dahulu:\n");
        printf("1. Sorting angka\n");
        printf("2. Sorting kata\n");
        printf("Pilihan Anda (1/2): ");
        scanf("%d", &choice);

        if (choice != 1 && choice != 2) {
            printf("Pilihan tidak valid. Silakan pilih 1 atau 2.\n");
        }
    }
    return choice;
}

void runIntegerSortingExperiments(const char* dataFile) {
    // Define the data sizes to test
    int dataSizes[NUM_DATA_SIZES] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};

    // Store results: [algorithm][data_size][metric] where metric 0=time, 1=memory
    double results[NUM_ALGORITHMS][NUM_DATA_SIZES][2];

    // Load the full dataset
    printf("Loading integer data...\n");
    int* fullData = loadIntData(dataFile, 2000000);
    if (!fullData) {
        printf("Error loading data. Exiting.\n");
        return;
    }

    // For each data size
    for (int size_idx = 0; size_idx < NUM_DATA_SIZES; size_idx++) {
        int dataSize = dataSizes[size_idx];
        printf("Testing with %d integers...\n", dataSize);

        // Create a copy of the data for each algorithm
        int* bubbleData = (int*)malloc(dataSize * sizeof(int));
        int* selectionData = (int*)malloc(dataSize * sizeof(int));
        int* insertionData = (int*)malloc(dataSize * sizeof(int));
        int* mergeData = (int*)malloc(dataSize * sizeof(int));
        int* quickData = (int*)malloc(dataSize * sizeof(int));
        int* shellData = (int*)malloc(dataSize * sizeof(int));

        if (!bubbleData || !selectionData || !insertionData || !mergeData || !quickData || !shellData) {
            printf("Memory allocation failed. Exiting.\n");
            free(fullData);
            return;
        }

        // Copy data for each algorithm
        copyIntArray(fullData, bubbleData, dataSize);
        copyIntArray(fullData, selectionData, dataSize);
        copyIntArray(fullData, insertionData, dataSize);
        copyIntArray(fullData, mergeData, dataSize);
        copyIntArray(fullData, quickData, dataSize);
        copyIntArray(fullData, shellData, dataSize);

        // Run each algorithm and collect metrics
        PerformanceMetrics metrics;

        // Bubble Sort
        printf("  Running Bubble Sort...\n");
        bubbleSortInt(bubbleData, dataSize, &metrics);
        results[0][size_idx][0] = metrics.execution_time;
        results[0][size_idx][1] = (double)metrics.memory_usage / 1024.0; // Convert to KB

        // Selection Sort
        printf("  Running Selection Sort...\n");
        selectionSortInt(selectionData, dataSize, &metrics);
        results[1][size_idx][0] = metrics.execution_time;
        results[1][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Insertion Sort
        printf("  Running Insertion Sort...\n");
        insertionSortInt(insertionData, dataSize, &metrics);
        results[2][size_idx][0] = metrics.execution_time;
        results[2][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Merge Sort
        printf("  Running Merge Sort...\n");
        mergeSortInt(mergeData, dataSize, &metrics);
        results[3][size_idx][0] = metrics.execution_time;
        results[3][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Quick Sort
        printf("  Running Quick Sort...\n");
        quickSortInt(quickData, dataSize, &metrics);
        results[4][size_idx][0] = metrics.execution_time;
        results[4][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Shell Sort
        printf("  Running Shell Sort...\n");
        shellSortInt(shellData, dataSize, &metrics);
        results[5][size_idx][0] = metrics.execution_time;
        results[5][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Print summary for current data size
        printSortingResultsSummary(results, size_idx, dataSize, "integer");

        // Free memory
        free(bubbleData);
        free(selectionData);
        free(insertionData);
        free(mergeData);
        free(quickData);
        free(shellData);
    }

    // Free the full dataset
    free(fullData);

    // Save results to CSV file
    FILE* fp = fopen("integer_sorting_results.csv", "w");
    if (!fp) {
        printf("Error creating results file.\n");
        return;
    }

    // Write header
    fprintf(fp, "Algorithm,Data Size,Execution Time (s),Memory Usage (KB)\n");

    // Write results
    const char* algorithmNames[NUM_ALGORITHMS] = {
        "Bubble Sort", "Selection Sort", "Insertion Sort",
        "Merge Sort", "Quick Sort", "Shell Sort"
    };

    for (int alg = 0; alg < NUM_ALGORITHMS; alg++) {
        for (int size_idx = 0; size_idx < NUM_DATA_SIZES; size_idx++) {
            fprintf(fp, "%s,%d,%.6f,%.2f\n",
                    algorithmNames[alg],
                    dataSizes[size_idx],
                    results[alg][size_idx][0],
                    results[alg][size_idx][1]);
        }
    }

    fclose(fp);
    printf("Integer sorting results saved to 'integer_sorting_results.csv'\n");
}

void runStringSortingExperiments(const char* dataFile) {
    // Define the data sizes to test
    int dataSizes[NUM_DATA_SIZES] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};

    // Store results: [algorithm][data_size][metric] where metric 0=time, 1=memory
    double results[NUM_ALGORITHMS][NUM_DATA_SIZES][2];

    // Load the full dataset
    printf("Loading string data...\n");
    char** fullData = loadStringData(dataFile, 2000000);
    if (!fullData) {
        printf("Error loading data. Exiting.\n");
        return;
    }

    // For each data size
    for (int size_idx = 0; size_idx < NUM_DATA_SIZES; size_idx++) {
        int dataSize = dataSizes[size_idx];
        printf("Testing with %d strings...\n", dataSize);

        // Create copies of the data for each algorithm
        char** bubbleData = (char**)malloc(dataSize * sizeof(char*));
        char** selectionData = (char**)malloc(dataSize * sizeof(char*));
        char** insertionData = (char**)malloc(dataSize * sizeof(char*));
        char** mergeData = (char**)malloc(dataSize * sizeof(char*));
        char** quickData = (char**)malloc(dataSize * sizeof(char*));
        char** shellData = (char**)malloc(dataSize * sizeof(char*));

        if (!bubbleData || !selectionData || !insertionData || !mergeData || !quickData || !shellData) {
            printf("Memory allocation failed. Exiting.\n");
            freeStringData(fullData, 2000000);
            return;
        }

        // Copy data for each algorithm
        copyStringArray(fullData, bubbleData, dataSize);
        copyStringArray(fullData, selectionData, dataSize);
        copyStringArray(fullData, insertionData, dataSize);
        copyStringArray(fullData, mergeData, dataSize);
        copyStringArray(fullData, quickData, dataSize);
        copyStringArray(fullData, shellData, dataSize);

        // Run each algorithm and collect metrics
        PerformanceMetrics metrics;

        // Bubble Sort
        printf("  Running Bubble Sort...\n");
        bubbleSortString(bubbleData, dataSize, &metrics);
        results[0][size_idx][0] = metrics.execution_time;
        results[0][size_idx][1] = (double)metrics.memory_usage / 1024.0; // Convert to KB

        // Selection Sort
        printf("  Running Selection Sort...\n");
        selectionSortString(selectionData, dataSize, &metrics);
        results[1][size_idx][0] = metrics.execution_time;
        results[1][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Insertion Sort
        printf("  Running Insertion Sort...\n");
        insertionSortString(insertionData, dataSize, &metrics);
        results[2][size_idx][0] = metrics.execution_time;
        results[2][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Merge Sort
        printf("  Running Merge Sort...\n");
        mergeSortString(mergeData, dataSize, &metrics);
        results[3][size_idx][0] = metrics.execution_time;
        results[3][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Quick Sort
        printf("  Running Quick Sort...\n");
        quickSortString(quickData, dataSize, &metrics);
        results[4][size_idx][0] = metrics.execution_time;
        results[4][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Shell Sort
        printf("  Running Shell Sort...\n");
        shellSortString(shellData, dataSize, &metrics);
        results[5][size_idx][0] = metrics.execution_time;
        results[5][size_idx][1] = (double)metrics.memory_usage / 1024.0;

        // Print summary for current data size
        printSortingResultsSummary(results, size_idx, dataSize, "string");

        // Free memory
        freeStringData(bubbleData, dataSize);
        freeStringData(selectionData, dataSize);
        freeStringData(insertionData, dataSize);
        freeStringData(mergeData, dataSize);
        freeStringData(quickData, dataSize);
        freeStringData(shellData, dataSize);
    }

    // Free the full dataset
    freeStringData(fullData, 2000000);

    // Save results to CSV file
    FILE* fp = fopen("string_sorting_results.csv", "w");
    if (!fp) {
        printf("Error creating results file.\n");
        return;
    }

    // Write header
    fprintf(fp, "Algorithm,Data Size,Execution Time (s),Memory Usage (KB)\n");

    // Write results
    const char* algorithmNames[NUM_ALGORITHMS] = {
        "Bubble Sort", "Selection Sort", "Insertion Sort",
        "Merge Sort", "Quick Sort", "Shell Sort"
    };

    for (int alg = 0; alg < NUM_ALGORITHMS; alg++) {
        for (int size_idx = 0; size_idx < NUM_DATA_SIZES; size_idx++) {
            fprintf(fp, "%s,%d,%.6f,%.2f\n",
                    algorithmNames[alg],
                    dataSizes[size_idx],
                    results[alg][size_idx][0],
                    results[alg][size_idx][1]);
        }
    }

    fclose(fp);
    printf("String sorting results saved to 'string_sorting_results.csv'\n");
}

// Function to print the sorting results summary in the requested format
void printSortingResultsSummary(double results[NUM_ALGORITHMS][NUM_DATA_SIZES][2], int sizeIndex, int dataSize, const char* dataType) {
    const char* algorithmNames[NUM_ALGORITHMS] = {
        "Bubble Sort", "Selection Sort", "Insertion Sort",
        "Merge Sort", "Quick Sort", "Shell Sort"
    };

    printf("\n----------------------------------------------\n");
    printf("Data %d (%s)\n", dataSize, dataType);
    for (int alg = 0; alg < NUM_ALGORITHMS; alg++) {
        printf("- %s: %.6f detik, %.2f KB\n",
               algorithmNames[alg],
               results[alg][sizeIndex][0],
               results[alg][sizeIndex][1]);
    }
    printf("----------------------------------------------\n\n");
}

// Helper function to copy integer arrays
void copyIntArray(int* source, int* dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// Helper function to copy string arrays
void copyStringArray(char** source, char** dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = strdup(source[i]);
        if (!dest[i]) {
            fprintf(stderr, "Memory allocation failed during string copy.\n");
            exit(1);
        }
    }
}