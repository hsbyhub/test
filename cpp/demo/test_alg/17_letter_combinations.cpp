#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<string> ans;
    vector<string> strs;
    string via;

public:

    void dfs(int i) {
        if (i > strs.size()) {
            ans.push_back(via);
            return;
        }
        for (int j = 0; j < strs[i].size(); j++) {
            via[i] = strs[i][j];
            dfs(i+1);
        } 
    }

    vector<string> letterCombinations(string digits) {
        int len = digits.size();
        strs.resize(len, "");
        via.resize(len);
        for (int i = 0; i < digits.size(); i++) {
            strs[i] = getLetters(digits[i]);
        }
        dfs(0);
        return ans;
    }

    string getLetters(char digit) {
        switch (digit) {
            case '2':
                return "abc";
            case '3':
                return "def";
            case '4':
                return "ghi";
            case '5':
                return "jkl";
            case '6':
                return "mmo";
            case '7':
                return "pqrs";
            case '8':
                return "tuv";
            case '9':
                return "wxyz";
        }
    }
};

int main() {

}
