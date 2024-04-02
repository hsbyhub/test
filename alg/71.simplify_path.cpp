#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<pair<int, int>> st;
        st.reserve(300);
        int i = -1;
        for (int j = 0; j <= path.size(); j++) {
            if (path[j] == '/' || path[j] == '\0') {
                int p = i;
                int c = j - i;
                i = j;

                if (p == -1) {
                    continue;
                }

                if (c <= 1) {
                    continue;
                }

                if (path.substr(p, c) == "/." || path.substr(p, c) == "/") {
                    continue;
                }

                if (path.substr(p, c) == "/.." && !st.empty()) {
                    st.pop_back();
                    continue;
                }

                st.push_back({p, c});
            }
        }
        string ans;
        ans.reserve(path.size());
        for (auto& p : st) {
            ans.append(path.substr(p.first, p.second));
        }
        if (ans.empty()) ans.push_back('/');
        return ans;
    }
};

int main() {
    cout << Solution().simplifyPath("/a/./b/../../c/") << endl;
}
