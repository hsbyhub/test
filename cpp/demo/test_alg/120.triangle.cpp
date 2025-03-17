#include <iostream>
#include <tuple>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (!triangle.size() || !triangle[0].size()) return 0;
        for (int i = triangle.size()-1; i >= 0; i--) {
            for (int j = 0; j < triangle[i].size(); j++) {
                if (i + 1 < triangle.size()-1) {
                    triangle[i][j] += triangle[i+1][j] < triangle[i+1][j+1] ? triangle[i+1][j] : triangle[i+1][j+1];
                }
            }
        }
        return triangle[0][0];
    }
};

int main() {

}
