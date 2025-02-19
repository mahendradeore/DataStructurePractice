#include <stdio.h>
#include <string.h>

// Function to expand around the center and find the longest palindrome
int expandAroundCenter(const char* str, int left, int right) {
    int length = strlen(str);
    while (left >= 0 && right < length && str[left] == str[right]) {
        left--;
        right++;
    }
    return right - left - 1; // Return length of the palindrome
}

// Function to find the longest palindromic substring
void longestPalindromicSubstring(const char* str, char* result) {
    int n = strlen(str);
    if (n == 0) {
        result[0] = '\0'; // Empty string case
        return;
    }

    int start = 0, maxLength = 1;

    for (int i = 0; i < n; i++) {
        // Odd-length palindromes (center at one character)
        int len1 = expandAroundCenter(str, i, i);

        // Even-length palindromes (center between two characters)
        int len2 = expandAroundCenter(str, i, i + 1);

        int len = (len1 > len2) ? len1 : len2;

        if (len > maxLength) {
            maxLength = len;
            start = i - (len - 1) / 2;
        }
    }

    // Copy the longest palindromic substring to the result
    strncpy(result, str + start, maxLength);
    result[maxLength] = '\0'; // Null-terminate the result
}

// Driver function
int main() {
    char str[] = "babad";
    char result[100];

    longestPalindromicSubstring(str, result);

    printf("The longest palindromic substring is: %s\n", result);

    return 0;
}
