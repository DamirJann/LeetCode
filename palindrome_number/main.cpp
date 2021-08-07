#include <iostream>

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int divider = 1;
        while (x / divider > 9) {
            divider *= 10;
        }
        while (x != 0) {
            if (x / divider != x % 10) return false;
            x %= divider;
            x /= 10;
            divider /= 100;
        }
        return true;

    }
};