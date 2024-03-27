#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

template<typename T>
class List {
public:
    List() : head_(new Node()) {
        head_->next_ = head_;
        head_->prev_ = head_;
    }

public:
    struct Node;
    typedef T DataType;
    typedef Node* Iter;

    struct Node {
        Node() : prev_(nullptr), next_(nullptr), data_(T()) {}
        Node(T data) : prev_(nullptr), next_(nullptr), data_(data) {}

        Node* prev_;
        Node* next_;
        T data_;
    };

public:
    void Push(T data) { 
        Node* node = new Node(data);
        Node* tail = head_->prev_;
        node->next_ = tail->next_;
        node->prev_ = tail;
        tail->next_->prev_ = node;
        tail->next_ = node;
    }

     T Pop() {
        Node* old = head_->next_;
        if (old == head_) {
            return T();
        }
        old->next_->prev_ = old->prev_;
        old->prev_->next_ = old->next_;
        old->next_ = nullptr;
        old->prev_ = nullptr;
        return old->data_;
    }

    bool Remove(Iter it) {
        Node* prev = it->prev_;
        Node* next = it->next_;
    }

    Iter Font() {
        return head_->next_;
    }
    
    Iter Back() {
        return head_->prev_;
    }

private:
    Node* head_;
};

class Lru {
public:
private:

};

int main() {
    List<int> l;
    l.Push(1);
    l.Push(2);
    std::cout << l.Pop() << std::endl;
    std::cout << l.Pop() << std::endl;
}
