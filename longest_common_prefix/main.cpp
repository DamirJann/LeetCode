#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int i = 0;
        string prefix;
        bool isEndOfSearch = false;
        while (!isEndOfSearch){
            char commonSymbol;
            if (i < strs[0].size()){
                commonSymbol = strs[0][i];
            } else{
                break;
            }
            for (string& str: strs){
                if (i >= str.size() || str[i] != commonSymbol) {
                    isEndOfSearch = true;
                }
            }
            if (!isEndOfSearch) {
                prefix += commonSymbol;
            }
            i++;
        }
        return prefix;
    }
};

int main() {
    return 0;
}
