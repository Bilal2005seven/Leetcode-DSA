#include <bits/stdc++.h>
using namespace std;

class MinStack {

public:

    stack<int> st;
    stack<int> minst;
    
    MinStack() {
        
    }
    
    void push(int value) {

        st.push(value);

        if (minst.empty()) {
            minst.push(value);
        }
        else {
            minst.push(min(value, minst.top()));
        }
    }
    
    void pop() {
        st.pop();
        minst.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minst.top();
    }
};