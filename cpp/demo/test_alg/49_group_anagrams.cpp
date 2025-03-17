#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Key {
public:
    static void fmt(const string& str, Key& k) {
        k.lc.resize(26, 0);
        for (auto c : str) {k.lc[c-'a']++;}
    }
    bool operator<(const Key& other) const {
        if (lc.size() < other.lc.size()) return true;
        if (lc.size() > other.lc.size()) return false;
        for (int i = 0; i < lc.size(); i++) {
            if (lc[i] < other.lc[i]) return true;
            if (lc[i] > other.lc[i]) return false;
        }
        return false;
    }
    vector<int> lc;
};

ostream& operator<<(ostream& os, const Key& k) {
        for (int i = 0; i < k.lc.size(); i++) {
            if (k.lc[i] > 0) {
                os << char(i) << ":" << k.lc[i];
                if (i < k.lc.size() - 1) os << ",";
            }
        }
        os << endl;
        return os;
}

class Solution {
public:
    
    vector<vector<string> > groupAnagrams(const vector<string>& strs) {
        map<Key, vector<string> > mp;
        for (auto& str : strs) {
            Key k;
            Key::fmt(str, k);
            cout << str << "->" << k;
            auto it = mp.find(k);
            if (it == mp.end()) {
                mp[k] = vector<string>();
            }
            mp[k].push_back(str);
        }
        vector<vector<string> > ans;
        for (auto it = mp.begin(); it != mp.end(); it++) {
            ans.push_back(it->second);
        }
        return ans;
    }
};

int main() {
    vector<vector<string> > ans = Solution().groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"});
    for (auto& strs : ans) {
        for (auto& str : strs) {
            cout << str << " ";
        }
        cout << endl;
    }
}
