# Memory Pool
This project has realized a dynamic memory allocation list queue based on C++ 11 *high performance memory pool*. The queue supports 30 Hz to 50 Hz data input and 10 Hz data output under *multithreading*. The project includes a self-implemented memory pool allocator. Can *improve memory allocation performance* to some extent, reduce the generation of memory fragmentation and memory allocation failure caused by the program crash.
# Project Schema
## Memory Pool Design
Pointer, is a unique point of C/C++, in the program design, it is inevitable to operate the memory, but the convenience of direct operation of memory will also bring many hidden dangers to the program design, may encounter insufficient memory, allocation failure and other special cases, and each memory allocation needs to apply to the operating system, there is time and space overhead, efficiency is not high. In order to better manage and optimize program memory, memory pooling technology can be used to reduce the cost of operating memory to a certain extent and improve program efficiency. Therefore, in this project, a memory pool with good performance will be realized to solve some project requirements encountered in the process of work.
## Linked List Stack
In order to verify the performance of the memory pool design, it is also necessary to design a data structure that can be used for dynamic memory allocation as the carrier. The default allocator and memory pool are used as memory allocation tools respectively to carry out the same data input and output, and observe the allocation efficiency of both. The common test tool is the linked list stack structure, so the author will first implement a linked list stack, as a test to assign its performance tool.
## Data Cache Pool
Data pool can store multiple formats of data, and ensure data 'first-in, first-out' access, through the memory pool to improve the efficiency of data access. For some reason, the data cache queue implemented by the memory pool is not presented here. I believe that interested readers can implement the memory pool implementation and queue design by themselves.
# Memory Pool
本项目实现了一个基于 C++ 11 *高性能内存池*的*可动态内存分配*的链表队列，队列支持多线程下 30 Hz 到 50 Hz 的数据输入和 10 Hz 的数据输出，项目内含自实现的 内存池 分配器，可以在一定程度上*提升内存分配性能*，减少内存碎片的产生和内存分配失败引起的程序崩溃。
# 项目架构
## 内存池设计
指针，是 C/C++ 独特的一点，在程序设计中，不可避免的需要操作内存，但是直接操作内存的便捷性也会给程序设计带来许多隐患，可能会遇到内存不足、分配失败等特殊情况，而且每次内存分配都需要向操作系统申请，都存在时空开销，效率并不高。 为了更好地管理和优化程序内存，可以通过内存池化技术，在一定程度上降低操作内存的成本，提升程序效率，因此，在本项目中将实现一个性能不错的内存池用于解决笔者在工作过程中遇到的一些项目需求。
## 链表栈
为了验证内存池设计的性能，还需要设计一个可以进行动态内存分配的数据结构作为载体，分别使用默认分配器和内存池作为内存分配工具，进行相同的数据输入输出，观察两者的分配效率。常用的测试工具为链表栈结构，因此，笔者将首先实现一个链表栈，作为测试分配其性能的工具。
## 数据缓存池
数据池可以存储多种格式数据，并保证数据的先入先出存取，通过内存池提升数据存取效率。 出于一些原因，在这里笔者并未给出通过内存池实现的数据缓存队列，相信感兴趣的读者可以通过给出的内存池实现和队列设计可以自行实现。