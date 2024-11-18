#include <stdio.h>

#define MAX_COURSES 5
#define MAX_OUTCOMES 5

// Function to input the matrix
void inputMatrix(int matrix[MAX_COURSES][MAX_OUTCOMES], int courses, int outcomes) {
    printf("Enter the course articulation matrix:\n");
    for (int i = 0; i < courses; i++) {
        for (int j = 0; j < outcomes; j++) {
            printf("Matrix[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to display the matrix
void displayMatrix(int matrix[MAX_COURSES][MAX_OUTCOMES], int courses, int outcomes) {
    printf("\nCourse Articulation Matrix:\n");
    for (int i = 0; i < courses; i++) {
        for (int j = 0; j < outcomes; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate the sum of a row
int rowSum(int matrix[MAX_COURSES][MAX_OUTCOMES], int row, int outcomes) {
    int sum = 0;
    for (int i = 0; i < outcomes; i++) {
        sum += matrix[row][i];
    }
    return sum;
}

// Quick Sort Helper Functions
void swapRows(int matrix[MAX_COURSES][MAX_OUTCOMES], int row1, int row2, int outcomes) {
    for (int i = 0; i < outcomes; i++) {
        int temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

int partition(int matrix[MAX_COURSES][MAX_OUTCOMES], int low, int high, int outcomes) {
    int pivot = rowSum(matrix, high, outcomes);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (rowSum(matrix, j, outcomes) <= pivot) {
            i++;
            swapRows(matrix, i, j, outcomes);
        }
    }
    swapRows(matrix, i + 1, high, outcomes);
    return i + 1;
}

void quickSort(int matrix[MAX_COURSES][MAX_OUTCOMES], int low, int high, int outcomes) {
    if (low < high) {
        int pi = partition(matrix, low, high, outcomes);
        quickSort(matrix, low, pi - 1, outcomes);
        quickSort(matrix, pi + 1, high, outcomes);
    }
}

// Linear Search
int linearSearch(int matrix[MAX_COURSES][MAX_OUTCOMES], int courses, int outcomes, int target[MAX_OUTCOMES]) {
    for (int i = 0; i < courses; i++) {
        int found = 1;
        for (int j = 0; j < outcomes; j++) {
            if (matrix[i][j] != target[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

// Binary Search
int binarySearch(int matrix[MAX_COURSES][MAX_OUTCOMES], int low, int high, int outcomes, int target[MAX_OUTCOMES]) {
    if (low > high) {
        return -1;
    }
    int mid = (low + high) / 2;

    int match = 1;
    for (int i = 0; i < outcomes; i++) {
        if (matrix[mid][i] != target[i]) {
            match = 0;
            break;
        }
    }

    if (match) {
        return mid;
    }

    int midSum = rowSum(matrix, mid, outcomes);
    int targetSum = 0;
    for (int i = 0; i < outcomes; i++) {
        targetSum += target[i];
    }

    if (targetSum < midSum) {
        return binarySearch(matrix, low, mid - 1, outcomes, target);
    } else {
        return binarySearch(matrix, mid + 1, high, outcomes, target);
    }
}

int main() {
    int courses, outcomes;
    int target[MAX_OUTCOMES];

    printf("Enter the number of courses: ");
    scanf("%d", &courses);
    printf("Enter the number of outcomes: ");
    scanf("%d", &outcomes);

    int matrix[MAX_COURSES][MAX_OUTCOMES];

    inputMatrix(matrix, courses, outcomes);

    // Sorting using Quick Sort
    quickSort(matrix, 0, courses - 1, outcomes);

    printf("\nSorted ");
    displayMatrix(matrix, courses, outcomes);

    printf("Enter the course articulation to search for:\n");
    for (int i = 0; i < outcomes; i++) {
        printf("Target[%d]: ", i + 1);
        scanf("%d", &target[i]);
    }

    // Searching using Linear Search
    int linearIndex = linearSearch(matrix, courses, outcomes, target);
    if (linearIndex != -1) {
        printf("Course articulation found using Linear Search at index: %d\n", linearIndex + 1);
    } else {
        printf("Course articulation not found using Linear Search.\n");
    }

    // Searching using Binary Search
    int binaryIndex = binarySearch(matrix, 0, courses - 1, outcomes, target);
    if (binaryIndex != -1) {
        printf("Course articulation found using Binary Search at index: %d\n", binaryIndex + 1);
    } else {
        printf("Course articulation not found using Binary Search.\n");
    }

    return 0;
}