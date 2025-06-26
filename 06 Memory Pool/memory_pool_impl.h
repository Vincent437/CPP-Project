#define pointer T*
template <typename T, size_t BlockSize>
MemoryPool<T,BlockSize>::MemoryPool() noexcept
{
	// 当前内存块
	currentBlock_ = nullptr;

	// 当前内存块的一个对象槽
	currentSlot_ = nullptr;
	// 当前内存区块的最后一个对象槽
	lastSlot_ = nullptr;

	// 当前内存区块中的空闲对象槽
	freeSlots_ = nullptr;
}

// 析构函数，销毁当前内存池
template <typename T, size_t BlockSize>
MemoryPool<T,BlockSize>::~MemoryPool() noexcept
{
	// 循环销毁内存池中分配的内存区块
	slot_pointer_ curr = currentBlock_;
	while (curr != nullptr)
	{
		slot_pointer_ prev = curr->next;
		operator delete(reinterpret_cast<void*>(curr));//全局delete，不会使得delete表达式调用析构函数
		curr = prev;
	}
}

// 分配内存区块，并返回一个数据指针
// 同一时间只能分配一个对象, n 和 hint 会被忽略
template <typename T, size_t BlockSize>
pointer MemoryPool<T,BlockSize>::allocate(size_t n, const T* hint)
{
	// 如果有空闲的对象槽，那么直接将空闲区域交付出去
	if (freeSlots_ != nullptr)
	{
		// 强制类型转换为指定数据类型的指针
		pointer result = reinterpret_cast<pointer>(freeSlots_);
		// 空闲指针指向下一块空闲对象槽
		freeSlots_ = freeSlots_->next;

		return result;
	}
	// 空闲对象槽指针为空
	else
	{
		// 当前对象槽超出当前内存块最后一个对象槽，则分配一个新的内存区块
		if (currentSlot_ >= lastSlot_)
		{
			// 分配一个新的内存区块，并指向前一个内存区块

			// 申请一个指定大小的内存区块，获得一个字符指针
			data_pointer_ newBlock = reinterpret_cast<data_pointer_>(operator new(BlockSize));
			// 将字符指针强制类型转换为对象槽指针，并指向当前内存区块
			reinterpret_cast<slot_pointer_>(newBlock)->next = currentBlock_;
			// 更新当前区块为获得新的内存区块后的区块指针
			currentBlock_ = reinterpret_cast<slot_pointer_>(newBlock);

			// 填补整个区块来满足元素内存区域的对齐要求

			// 区块体 为 内存区块大小与区块指针大小之和
			data_pointer_ body = newBlock + sizeof(slot_pointer_);
			// 对区块体指针强制类型转换
			uintptr_t result = reinterpret_cast<uintptr_t>(body);
			// 区块体对齐大小
			size_t bodyPadding = (alignof(slot_type_) - result) % alignof(slot_type_);
			// 起始位置之前应当留出对齐内存所需空间
			currentSlot_ = reinterpret_cast<slot_pointer_>(body + bodyPadding);
			// 末尾位置 为 区块起始位置加区块大小减去一个数据大小+1
			lastSlot_ = reinterpret_cast<slot_pointer_>(newBlock + BlockSize - sizeof(slot_type_) + 1);
			// 无需初始化 freeSlots_，freeslot自己维护着一个链表
			// freeSlots_ = reinterpret_cast<slot_pointer_>(currentSlot_);
		}

		// 将当前对象槽强制类型转换后返回指定数据类型指针
		return reinterpret_cast<pointer>(currentSlot_++);
	}
}

// 销毁指针 p 指向的内存区块
template <typename T, size_t BlockSize>
void MemoryPool<T,BlockSize>::deallocate(pointer p, size_t n)
{
	if (p != nullptr)
	{
		// reinterpret_cast 是强制类型转换符
		// 要访问 next 必须强制将 p 转成 slot_pointer_

		// 将待销毁的指针指向空闲对象槽，下次即可分配出
		reinterpret_cast<slot_pointer_>(p)->next = freeSlots_;
		// 空前槽节点更新
		freeSlots_ = reinterpret_cast<slot_pointer_>(p);
	}
}

// 调用对象构造函数，使用 std::forward 转发变参模板
template <typename T, size_t BlockSize>
template <typename U, typename... Args>
void MemoryPool<T,BlockSize>::construct(U* p, Args &&...args)
{
	new (p) U(std::forward<Args>(args)...);
}

// 调用对象析构函数
template <typename T, size_t BlockSize>
template <typename U>
void MemoryPool<T,BlockSize>::destroy(U* p)
{
	p->~U();
}