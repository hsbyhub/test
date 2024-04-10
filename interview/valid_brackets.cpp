#include <iostream>
#include <vector>
#include <string>
#include <stack>

void gen_ex(int n, int i, std::string& cur, std::stack<char>& st, std::vector<std::string>& res) {
    if (i >= n) {
        if (st.empty()) {
            res.push_back(cur);
        }
        return;
    }
    
    cur[i] = '(';
    st.push('(');
    gen_ex(n, i+1, cur, st, res);
    st.pop();

    if (!st.empty() && st.top() == '(') {
        st.pop();
        cur[i] = ')';
        gen_ex(n, i+1, cur, st, res);
        st.push('(');
    } else {
        st.push(')');
        cur[i] = ')';
        gen_ex(n, i+1, cur, st, res);
        st.pop();
    }
}

std::vector<std::string> gen(int pairs) {
    std::vector<std::string> res;
    std::string str(pairs*2, '\0');
    std::stack<char> st;
    gen_ex(pairs*2, 0, str, st, res);
    return res;
}

int main() {
    auto res = gen(3);
    for (auto& str : res) {
        std::cout << str << std::endl;
    }
}
