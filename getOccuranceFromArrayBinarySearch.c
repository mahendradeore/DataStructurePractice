#include <stdio.h>

int getFirstIndex(int index, int arr[], int target) {
    while (index >= 0 && arr[index] == target) {
        index--;
    }
    return index + 1;
}

int getLastIndex(int index, int arr[], int len, int target) {
    while (index < len && arr[index] == target) {
        index++;
    }
    return index - 1;
}

int binarySearch(int arr[], int start, int end, int num) {
    if (start > end) {
        return 0; // Element not found
    }

    int mid = (start + end) / 2;
    
    if (arr[mid] == num) {
        int first = getFirstIndex(mid, arr, num);
        int last = getLastIndex(mid, arr, end + 1, num);
        return (last - first + 1);
    }
    
    if (arr[mid] < num) {
        return binarySearch(arr, mid + 1, end, num);
    } else {
        return binarySearch(arr, start, mid - 1, num);
    }
}

int getOccurrence(int num, int arr[], int len) {
    return binarySearch(arr, 0, len - 1, num);
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 3, 5, 5, 5, 6, 6, 6, 6};
    int num = 6;
    int len = sizeof(arr) / sizeof(arr[0]);
    int occu = getOccurrence(num, arr, len);
  
    printf("\nOccurrence of %d = %d\n", num, occu);
    return 0;
}
