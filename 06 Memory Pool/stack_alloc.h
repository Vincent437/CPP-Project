/*
* @author Vincent
* @brief Stack allocation utilities for C++.
* @details This header file provides utilities for stack allocation of objects in C++.
* It includes a `stack_alloc` class template that allows for stack allocation of objects
* with automatic cleanup. The class supports placement new for constructing objects in a
* pre-allocated memory buffer, and it provides a method to deallocate the memory when done
* with the object.
*/

#ifndef STACK_ALLOC_H
#define STACK_ALLOC_H

#include <memory>

// Stack node
template <typename T>
struct stack_node {
    // storing data
    T value;
    // pointing to previous node
    stack_node* prev;

    // Default constructor
    stack_node()= default;
    // Constructor to initialize the value and set the previous pointer to nullptr
    stack_node(const T& val) : value(val), prev(nullptr) {}
};

template <class T, class Alloc = std::allocator<T>>
class stack_alloc
{
    // 类内自定义简化类型名
    using Node = stack_node<T>;
    using allocator = typename Alloc:: template rebind<Node>::other;

private:
    // 链表栈的头节点
    Node *head_;
    // 内存分配器
    allocator allocator_;

public:
    // 默认构造
    stack_alloc();

    // 默认析构
    ~stack_alloc();

    // 判断栈是否为空
    bool empty();

    // 返回栈顶元素
    T top();

    // 入栈，将一个数据压入栈内
    void push(T element);

    // 出栈，将栈顶数据弹出并返回
    T pop();

    // 清空栈内全部元素
    void clear();
};

#include "stack_alloc_impl.h"

#endif // STACK_ALLOC_H