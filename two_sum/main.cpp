#include "vector"
#include <cassert>
#include <iterator>
#include <iostream>

using namespace std;


template<typename K, typename V>
class HashNode {
public:
    HashNode(const K &key, const V &value, const int ind) :
            key(key), value(value), next(nullptr), ind(ind) {
    }

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    int getInd() const {
        return ind;
    }

    void setValue(V value) {
        HashNode::value = value;
    }

    HashNode *getNext() const {
        return next;
    }

    void setNext(HashNode *next) {
        HashNode::next = next;
    }

private:
    // key-value pair
    K key;
    V value;
    int ind;
    // next bucket with the same key
    HashNode *next;
};


template<typename K>
struct KeyHash {
    unsigned long operator()(const K &key) const;
};

template<typename K, typename V, typename F = KeyHash<K>>
class HashTable {
public:
    HashTable(int size) {
        this->size = size;
        table = new HashNode<K, V> *[size]();
    }

    ~HashTable() {
        // TODO
        for (int i = 0; i < size; i++) {
            HashNode<K, V> *prev;
            HashNode<K, V> *cur = table[i];

            while (cur != nullptr) {
                prev = cur;
                cur = cur->getNext();
                delete prev;
            }
        }
        delete[] table;
    }


    bool get(const K &key, V value, int &ind) {
        unsigned int hashValue = hashFunc(key);
        HashNode<K, V> *cur = table[hashValue];

        while (cur != nullptr && cur->getValue() != value) {
            cur = cur->getNext();
        }
        if (cur != nullptr && cur->getValue() == value) {
            ind = cur->getInd();
            return true;
        } else {
            return false;
        }
    }

    bool put(const K &key, V value, int ind) {
        unsigned int hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *cur = table[hashValue];

        while (cur != nullptr && cur->getValue() != value) {
            prev = cur;
            cur = cur->getNext();
        }

        if (cur != nullptr && cur->getValue() == value) {
            return false;
        } else {
            if (prev == nullptr) {
                table[hashValue] = new HashNode<K, V>(hashValue, value, ind);
            } else {
                prev->setNext(new HashNode<K, V>(hashValue, value, ind));
            }
            return true;
        }
    }

    bool remove(const K &key, V value) {
        unsigned int hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *cur = table[hashValue];

        while (cur != nullptr && cur->getValue() != value) {
            prev = cur;
            cur = cur->getNext();
        }

        if (cur != nullptr && cur->getValue() == value) {
            if (prev == nullptr) {
                delete table[hashValue];
                table[hashValue] = nullptr;
            } else {
                prev->setNext(cur->getNext());
                delete cur;
            }
            return true;
        } else {
            return false;
        }


    }


public:
    HashNode<K, V> **table;
    unsigned int size;
    F hashFunc;
};

struct MyKeyHash {
    unsigned long operator()(const int &k) const {
        return abs(k) % 1000;
    }
};

class Solution {
public:


    vector<int> twoSum(vector<int> &nums, int target) {
        HashTable<int, int, MyKeyHash> hashTable(1000);
        for (int i = 0; i < nums.size(); i++) {
            int snd_ind,
                    snd = target - nums[i];
            if (hashTable.get(snd, snd, snd_ind)) {
                return {snd_ind, i};
            }
            hashTable.put(nums.at(i), nums.at(i), i);
        }
        return {0, 0};
    }

};

int main() {

    Solution solution;
    {
        vector<int> v{2, 7, 11, 15};
        vector<int> r = solution.twoSum(v, 9);
        assert(r[0] == 0);
        assert(r[1] == 1);
    }
    {
        vector<int> v{7, 3, 7};
        vector<int> r = solution.twoSum(v, 14);
        assert(r[0] == 0);
        assert(r[1] == 2);
    }
    {
        vector<int> v{3, 2, 4};
        vector<int> r = solution.twoSum(v, 6);
        assert(r[0] == 1);
        assert(r[1] == 2);
    }

    {
        vector<int> v{3, 3};
        vector<int> r = solution.twoSum(v, 6);
        assert(r[0] == 0);
        assert(r[1] == 1);
    }


    {
        vector<int> v{3, 3,  4, 0};
        vector<int> r = solution.twoSum(v, 4);
        assert(r[0] == 2);
        assert(r[1] == 3);
    }
    {
        vector<int> v{0, 4, 3, 0};
        vector<int> r = solution.twoSum(v, 0);
        assert(r[0] == 0);
        assert(r[1] == 3);
    }


    // ------------------------------------------
    HashTable<int, int, MyKeyHash> table(1000);


    int ind;
    assert(!table.get(3, 3, ind));
    table.put(1, 1, 1);

    assert(table.get(1, 1, ind));
    table.put(2, 2, 1);

    assert(!table.get(3, 3, ind));
    table.put(3, 3, 1);
    table.put(4, 4, 1);
    table.put(5, 5, 1);
    table.put(6, 6, 1);
    assert(!table.put(6, 6, 1));

    assert(table.remove(6, 6));
    assert(!table.get(6, 6., ind));
    table.put(7, 7, 1);
    table.put(8, 8, 1);
    table.put(9, 9, 1);

    assert(table.get(1, 1, ind));
    assert(table.get(2, 2, ind));
    assert(table.get(3, 3, ind));
    assert(table.get(4, 4, ind));
    assert(table.get(5, 5, ind));
    assert(!table.get(6, 6, ind));


}