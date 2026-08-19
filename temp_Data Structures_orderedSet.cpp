#include "bits/stdc++.h"

using namespace std;
using namespace __gnu_pbds;
 
template <typename T> 
using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

// use pair<int,int> -> value,id for multiset
class Policy {
private:
    ordered_set<int> pbds;
public:
    Policy() {
        pbds.clear();
    }
    void add(int value) {
        pbds.insert(value);
    }
    void remov(int value) {
        auto fnd = pbds.find(value);
        if (fnd != pbds.end()) {
            pbds.erase(fnd);
        }
    }
    int kth(int k) {
        return *pbds.find_by_order(k); // zero-based
    }
    int countLess(int value) {
        return pbds.order_of_key(value);
    }
    int countEqual(int value) {
        return countLess(value + 1) - countLess(value);
    }
    int countLessOrEqual(int value) {
        return countLess(value + 1);
    }
    int countGreater(int value) {
        return pbds.size() - countLess(value + 1);
    }
};