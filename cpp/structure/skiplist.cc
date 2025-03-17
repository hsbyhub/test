#include <vector>

#include "skiplist.h"

SkipList::SkipList(int branching) :
        head_(new Node(0, 0, kMaxHeight)),
        max_height_(0),
        rng_(NowMicros(),NowMicros()){
    if (branching < 2) {
        branching = 2;
    }
    branching_ = branching;
}

SkipList::~SkipList() {
    Node* ptr = head_->next[0];
    while(ptr) {
        Node* next = ptr->next[0];
        delete ptr;
        ptr = next;
    }
    delete head_;
    head_ = nullptr;
}

void SkipList::Put(uint64_t key, uint64_t value) {
     // 获取高度
    int height = GenarateHeight();

    // 拓展高度
    if (height > max_height_) {
        max_height_ = height;
    }

    // 从最高层开始查找
    Node* ptr = head_;
    std::vector<Node*> pre(height, nullptr);
    Node* insert_node = nullptr;
    for (int level = max_height_ - 1; level >= 0; level--) {
        test_put_iter_++;
        // 向右跳跃
        while(ptr->next[level] && key > ptr->next[level]->key) {
            test_put_iter_++;
            ptr = ptr->next[level];
        }

        // 如果当前节点与插入节点相等，则更新值
        if (ptr->key == key) {
            insert_node = ptr;
            break;
        }

        // 如果节点高度大于等于当前高度，则插入本层链表
        if (level < height) {
            pre[level] = ptr;
        }
    }

    // 更新或插入节点
    if (insert_node != nullptr) {
        insert_node->value = value;
    } else {
        insert_node = new Node(key, value, height);
        for (int level = 0; level < height; level++) {
            Node* next = pre[level]->next[level];
            pre[level]->next[level] = insert_node;
            insert_node->next[level] = next;
        }
    }
}

uint64_t SkipList::Get(uint64_t key) {
    // 从最高层开始查找
    Node* ptr = head_;
    for (int level = max_height_-1; level >= 0; level--) {
        test_get_iter_++;

        // 向右跳跃
        while(ptr->next[level] && key > ptr->next[level]->key) {
            test_get_iter_++;
            ptr = ptr->next[level];
        }

        if (ptr->next[level] && ptr->next[level]->key == key) {
            return ptr->next[level]->value;
        }
    }

    return 0;
}

void SkipList::TestDump(std::ostream& os) {
    Node* cur = head_->next[max_height_-1];
    for (int level = max_height_ - 1; level >= 0; level--) {
        while(cur) {
            os << "[" << cur->key << ":" << cur->value << "],";
            cur = cur->next[level];
        }
        os << std::endl;
    }
}

int SkipList::GenarateHeight() {
    int height = 1;
    while(height < kMaxHeight && (rng_.Next() % branching_) == 0) {
        height++;
    }
    return height;
}
