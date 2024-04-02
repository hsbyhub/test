#include <map>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:

    using MapType = unordered_map<int, int>;

    class cmp {
    public:
        bool operator()(MapType::iterator l, MapType::iterator r) {
            return l->second < r->second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        MapType freq;
        for (auto num : nums) freq[num]++;
        // 大顶堆
        priority_queue<
            MapType::iterator, 
            vector<MapType::iterator>, 
            cmp
        > q;
        for (MapType::iterator it = freq.begin(); it != freq.end(); it++) {
            q.push(it);
        }
        vector<int> ans;
        while(k--) {
            ans.push_back(q.top()->first);
            q.pop();
        }
        return ans;
    }
};

int main() {
    vector<int> nums{1, 1, 2, 2, 3, 3, 3, 5};
    vector<int> ans = Solution().topKFrequent(nums, 2);
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << endl;
}
