#include <iostream>
#include <string>
#include <map>
#include <assert.h>

using namespace std;


map<char, int> romanDigitToInt = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
};

class Solution {
public:
    int romanToInt(string s) {
        int transformedNumber = 0;
        int i = 0;
        while (i < s.size()) {
            int curr = romanDigitToInt[s[i]];
            if (i < s.size()) {
                int next = romanDigitToInt[s[i+1]];
                if (curr < next) {
                    transformedNumber += next - curr;
                    i += 2;
                } else {
                    transformedNumber += curr;
                    i++;
                }

            } else {
                transformedNumber += curr;
                i++;
            }
        }
        return transformedNumber;
    }

};


int main() {
    Solution solution;
    assert(solution.romanToInt("III") == 3);
    assert(solution.romanToInt("IV") == 4);
    assert(solution.romanToInt("IX") == 9);
    assert(solution.romanToInt("LVIII") == 58);
    assert(solution.romanToInt("MCMXCIV") == 1994);
    return 0;
}
