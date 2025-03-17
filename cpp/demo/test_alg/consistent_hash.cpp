#include <iostream>
#include <map>
#include <ostream>

// 一致性哈希表
class CHashTable {
public:
    // 构造方法
    CHashTable(int limit = 1000) : limit_(limit){}

    // 设置
    void Set(int k, int v) {
        mp_[Hash(k)] = v;
    }

    // 获取
    int Get(int k) {
        if (!mp_.size()) return -1;
        int h = Hash(k);
        auto it = mp_.lower_bound(h);
        if (it == mp_.end()) {
            return mp_.begin()->second;
        }
        return it->second;
    }

private:
    // 哈希方法
    int Hash(int k) {
        return k%limit_;
    }

private:
    std::map<int, int> mp_;
    int limit_;
};

int main() {
    CHashTable cht;
    cht.Set(0, 0);
    cht.Set(100, 1);
    cht.Set(200, 2);
    std::cout << cht.Get(50) << std::endl;
    std::cout << cht.Get(150) << std::endl;
    std::cout << cht.Get(250) << std::endl;
}
