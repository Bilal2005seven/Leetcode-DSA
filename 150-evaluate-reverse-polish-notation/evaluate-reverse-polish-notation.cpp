#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {

        stack<int> st;

        for (int i = 0; i < tokens.size(); i++) {

            if (tokens[i] == "+") {

                int first = st.top();
                st.pop();

                int second = st.top();
                st.pop();

                int result = second + first;
                st.push(result);
            }

            else if (tokens[i] == "-") {

                int first = st.top();
                st.pop();

                int second = st.top();
                st.pop();

                int result = second - first;
                st.push(result);
            }

            else if (tokens[i] == "*") {

                int first = st.top();
                st.pop();

                int second = st.top();
                st.pop();

                int result = second * first;
                st.push(result);
            }

            else if (tokens[i] == "/") {

                int first = st.top();
                st.pop();

                int second = st.top();
                st.pop();

                int result = second / first;
                st.push(result);
            }

            else {
                // Token is a number
                st.push(stoi(tokens[i]));
            }
        }

        return st.top();
    }
};