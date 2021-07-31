#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
#include <math.h>

class Solution {
public:
    vector<unsigned short> getDischargeVector(int x){
        vector<unsigned short> v;
        x = abs(x);
        while (x != 0){
            v.push_back(x % 10);
            x /= 10;
        }
        return v;
    }

    int getIntFromVector(vector<unsigned short> v){
        int value = 0;
        for (int i = 0; i < v.size(); i++) {
            value += v[i] * pow(10, i);
        }
        return value;
    }

    vector<unsigned short> reverseVector(vector<unsigned short> v){
        for (int i = 0; i < v.size() / 2; i++){
            swap(v[i], v[v.size()-1-i]);
        }
        return v;
    }

    int reverse2(int x, int MAX = INT_MAX) {
        vector<unsigned short> value = getDischargeVector(x);
        vector<unsigned short> max = x > 0 ?
                                getDischargeVector(MAX - 1) : getDischargeVector(MAX);
        if (value.size() > max.size()) {
            return 0;
        } else if (value.size() < max.size()){
            value = reverseVector(value);
            return x > 0 ? getIntFromVector(value) : -getIntFromVector(value);
        }
        else {
            for (int i = 0; i < value.size(); i++) {
                if (value[i] > max[value.size() - 1 - i]) return 0;
                if (value[i] < max[value.size() - 1 - i]) break;
            }
            value = reverseVector(value);
            return x > 0 ? getIntFromVector(value) : -getIntFromVector(value);
        }
    }

    int reverse(int x, int MAX = INT_MAX) {
        int sign = x > 0 ? 1 : -1;
        int border = x > 0 ? MAX : -MAX-1;
        if (x == -INT_MAX-1) return 0;
        x = abs(x);
        int tmp = 0;
        while (x != 0){
            int pop = x % 10;
            x /= 10;
            if (sign == 1 && tmp > (border - pop) / 10.0) return 0;
            if (sign == -1 && tmp > abs(((border + pop) / 10.0))) return 0;

            tmp = tmp * 10 + pop;
        }
        return tmp * sign;

    }


};

int main() {
    Solution solution;

    assert(solution.reverse(123) == 321);
    assert(solution.reverse(30001231) == 13210003);
    assert(solution.reverse(100) == 1);
    assert(solution.reverse(43434) == 43434);
    assert(solution.reverse(-34) == -43);
    assert(solution.reverse(123, 255) == 0);
    assert(solution.reverse(0, 255) == 0);
    assert(solution.reverse(-13, 31) == -31);
    assert(solution.reverse(-23, 31) == -32);
    assert(solution.reverse(23, 31) == 0);
    assert(solution.reverse(-2147483648) == 0);
    assert(solution.reverse(2147483647) == 0);


    return 0;
}
