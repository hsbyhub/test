#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>

class Lru {
public:
    Lru(int cap) : cap_(cap) {}

    void Put(int k, int v) {
        auto it = mp_.find(k);
        if (it != mp_.end()) {
            // 更新
            li_.erase(it->second.second); // 删除原来节点的位置
        } else {
            // 淘汰
            if (mp_.size() >= cap_) {
                mp_.erase(li_.back());
                li_.pop_back();
            }
        }
        li_.push_front(k);
        mp_[k] = {v, li_.begin()};
    }

    int Get(int k) {
        auto it = mp_.find(k);
        if (it == mp_.end()) return -1;
        // 刷新
        li_.erase(it->second.second);
        li_.push_front(k);
        it->second.second = li_.begin();
        return it->second.first;
    }

private:
    int cap_; // 容量
    std::list<int> li_; // 新老顺序
    std::unordered_map<int, std::pair<int, std::list<int>::iterator> > mp_; // 索引 key->(value, ListNode) 
};

int main() {
    Lru lru(5);
    lru.Put(1, 1);
    lru.Put(2, 2);
    lru.Put(3, 3);
    lru.Put(4, 4);
    std::cout << lru.Get(1) << std::endl;
    lru.Put(5, 5);
    lru.Put(6, 6);
    std::cout << lru.Get(2) << std::endl;
}
