#pragma once

#include "utlvector.h"

#if 0
#include "CUtlMemory.h"

template< class T >
class CUtlFixedMemory
{
protected:
	struct BlockHeader_t;
public:
	T & operator[](int i)
	{
		return *(T*)i;
	}

	const T& operator[](int i) const
	{
		return *(T*)i;
	}

	class Iterator_t
	{
	public:
		Iterator_t(BlockHeader_t *p, int i) : m_pBlockHeader(p), m_nIndex(i) {}
		BlockHeader_t *m_pBlockHeader;
		int m_nIndex;

		bool operator==(const Iterator_t it) const { return m_pBlockHeader == it.m_pBlockHeader && m_nIndex == it.m_nIndex; }
		bool operator!=(const Iterator_t it) const { return m_pBlockHeader != it.m_pBlockHeader || m_nIndex != it.m_nIndex; }
	};

	static const int INVALID_INDEX = 0; // For use with COMPILE_TIME_ASSERT
	static int InvalidIndex() { return INVALID_INDEX; }

	bool IsIdxValid(int i) const
	{
		return i != InvalidIndex();
	}

	bool IsInBlock(int i, BlockHeader_t *pBlockHeader) const
	{
		T *p = (T*)i;
		const T *p0 = HeaderToBlock(pBlockHeader);
		return p >= p0 && p < p0 + pBlockHeader->m_nBlockSize;
	}

	int GetIndex(const Iterator_t &it) const
	{
		if (!IsValidIterator(it))
			return InvalidIndex();

		return (int)(HeaderToBlock(it.m_pBlockHeader) + it.m_nIndex);
	}

	bool IsIdxAfter(int i, const Iterator_t &it) const
	{
		if (!IsValidIterator(it))
			return false;

		if (IsInBlock(i, it.m_pBlockHeader))
			return i > GetIndex(it);

		for (BlockHeader_t * __restrict pbh = it.m_pBlockHeader->m_pNext; pbh; pbh = pbh->m_pNext)
		{
			if (IsInBlock(i, pbh))
				return true;
		}

		return false;
	}

protected:
	bool IsValidIterator(const Iterator_t &it) const { return it.m_pBlockHeader && it.m_nIndex >= 0 && it.m_nIndex < it.m_pBlockHeader->m_nBlockSize; }

	const T *HeaderToBlock(const BlockHeader_t *pHeader) const { return (T*)(pHeader + 1); }

	struct BlockHeader_t
	{
		BlockHeader_t *m_pNext;
		int m_nBlockSize;
	};

	BlockHeader_t* m_pBlocks;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template< class T, class A = CUtlMemory<T> >
class CUtlVector_full
{
	typedef A CAllocator;
public:
	typedef T ElemType_t;

	inline CUtlVector_full<T, A>& operator=(const CUtlVector_full<T, A> &other)
	{
		int nCount = other.Count();
		SetSize(nCount);
		for (int i = 0; i < nCount; i++)
		{
			(*this)[i] = other[i];
		}
		return *this;
	}

	// element access
	inline T& operator[](int i)
	{
		return m_Memory[i];
	}

	inline const T& operator[](int i) const
	{
		return m_Memory[i];
	}

	inline T& Element(int i)
	{
		return m_Memory[i];
	}

	inline const T& Element(int i) const
	{
		return m_Memory[i];
	}

	inline T& Head()
	{
		return m_Memory[0];
	}

	inline const T& Head() const
	{
		return m_Memory[0];
	}

	inline T& Tail()
	{
		return m_Memory[m_Size - 1];
	}

	inline const T& Tail() const
	{
		return m_Memory[m_Size - 1];
	}

	// Gets the base address (can change when adding elements!)
	T* Base()
	{
		return m_Memory.Base();
	}

	const T* Base() const
	{
		return m_Memory.Base();
	}

	inline int InsertMultipleBefore(int elem, int num)
	{
		if (num == 0)
			return elem;

		// Can insert at the end
		if (!((elem == Count()) || IsValidIndex(elem)))
			return 0;

		GrowVector(num);
		ShiftElementsRight(elem, num);

		// Invoke default constructors
		for (int i = 0; i < num; ++i) {
			Construct(&Element(elem + i));
		}

		return elem;
	}

	inline int InsertMultipleBefore(int elem, int num, const T *pToInsert)
	{
		if (num == 0)
			return elem;

		// Can insert at the end
		assert((elem == Count()) || IsValidIndex(elem));

		GrowVector(num);
		ShiftElementsRight(elem, num);

		// Invoke default constructors
		if (!pToInsert) {
			for (int i = 0; i < num; ++i) {
				Construct(&Element(elem + i));
			}
		}
		else {
			for (int i = 0; i < num; i++) {
				CopyConstruct(&Element(elem + i), pToInsert[i]);
			}
		}

		return elem;
	}

	inline int AddMultipleToHead(int num)
	{
		return InsertMultipleBefore(0, num);
	}

	inline int AddMultipleToTail(int num)
	{
		return InsertMultipleBefore(m_Size, num);
	}

	inline int AddMultipleToTail(int num, const T *pToCopy)
	{
		// Can't insert something that's in the list... reallocation may hose us
		assert((Base() == NULL) || !pToCopy || (pToCopy + num <= Base()) || (pToCopy >= (Base() + Count())));

		return InsertMultipleBefore(m_Size, num, pToCopy);
	}


	// Returns the number of elements in the vector
	// SIZE IS DEPRECATED!
	inline int Size() const
	{
		return m_Size;
	}

	// don't use me!
	inline int Count() const
	{
		return m_Size;
	}

	// Is element index valid?
	inline bool IsValidIndex(int i) const
	{
		return (i >= 0) && (i < m_Size);
	}

	// Returns in invalid index
	inline int InvalidIndex()
	{
		return -1;
	}

	// Adds an element, uses default constructor
	inline int AddToHead()
	{
		return InsertBefore(0);
	}

	inline int AddToTail()
	{
		return InsertBefore(m_Size);
	}

	inline int AddToTail(const T& src)
	{
		return InsertBefore(m_Size, src);
	}

	inline int InsertAfter(int elem)
	{
		return InsertBefore(elem + 1);
	}

	//-----------------------------------------------------------------------------
	// Makes sure we have enough memory allocated to store a requested # of elements
	//-----------------------------------------------------------------------------
	void EnsureCapacity(int num)
	{
		m_Memory.EnsureCapacity(num);
		ResetDbgInfo();
	}

	int InsertBefore(int elem)
	{
		// Can insert at the end
		GrowVector();
		ShiftElementsRight(elem);
		Construct(&Element(elem));
		return elem;
	}

	int InsertBefore(int elem, const T& src)
	{
		GrowVector();
		ShiftElementsRight(elem);
		CopyConstruct(&Element(elem), src);
		return elem;
	}

	// Calls RemoveAll() then AddMultipleToTail.
	void SetCount(int count)
	{
		RemoveAll();
		AddMultipleToTail(count);
	}

	inline void SetSize(int size)
	{
		SetCount(size);
	}

	inline void SetSize2(int size)
	{
		m_Size = size;
	}

	// Calls SetSize and copies each element.
	void CopyArray(const T *pArray, int size)
	{
		SetSize(size);

		for (int i = 0; i < size; i++)
		{
			(*this)[i] = pArray[i];
		}
	}

	// Finds an element (element needs operator== defined)
	int Find(const T& src) const
	{
		for (int i = 0; i < Count(); ++i)
		{
			if (Element(i) == src)
				return i;
		}
		return -1;
	}

	bool HasElement(const T& src) const
	{
		return (Find(src) >= 0);
	}

	// Element removal
	void FastRemove(int elem)
	{
		Destruct(&Element(elem));
		if (m_Size > 0)
		{
			memcpy(&Element(elem), &Element(m_Size - 1), sizeof(T));
			--m_Size;
		}
	}

	void Remove(int elem)
	{
		Destruct(&Element(elem));
		ShiftElementsLeft(elem);
		--m_Size;
	}

	bool FindAndRemove(const T& src)
	{
		int elem = Find(src);
		if (elem != -1)
		{
			Remove(elem);
			return true;
		}
		return false;
	}

	void RemoveMultiple(int elem, int num)
	{
		for (int i = elem + num; --i >= elem;)
			Destruct(&Element(i));

		ShiftElementsLeft(elem, num);
		m_Size -= num;
	}

	void RemoveAll()
	{
		for (int i = m_Size; --i >= 0;)
			Destruct(&Element(i));

		m_Size = 0;
	}

	// Memory deallocation
	inline void Purge()
	{
		RemoveAll();
		m_Memory.Purge();
		ResetDbgInfo();
	}

	// Purges the list and calls delete on each element in it.
	inline void PurgeAndDeleteElements()
	{
		for (int i = 0; i < m_Size; i++)
			delete Element(i);

		Purge();
	}

	// Compacts the vector to the number of elements actually in use 
	inline void Compact()
	{
		m_Memory.Purge(m_Size);
	}

	// Set the size by which it grows when it needs to allocate more memory.
	void SetGrowSize(int size)
	{
		m_Memory.SetGrowSize(size);
	}

	// Only use this if you really know what you're doing!
	inline int NumAllocated() const
	{
		return m_Memory.NumAllocated();
	}

protected:
	// Grows the vector
	void GrowVector(int num = 1)
	{
		if (m_Size + num > m_Memory.NumAllocated())
			m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());

		m_Size += num;
		ResetDbgInfo();
	}

	// Shifts elements....
	void ShiftElementsRight(int elem, int num = 1)
	{
		int numToMove = m_Size - elem - num;
		if ((numToMove > 0) && (num > 0))
			memmove(&Element(elem + num), &Element(elem), numToMove * sizeof(T));
	}

	void ShiftElementsLeft(int elem, int num = 1)
	{
		int numToMove = m_Size - elem - num;
		if ((numToMove > 0) && (num > 0))
			memmove(&Element(elem), &Element(elem + num), numToMove * sizeof(T));
	}

	CAllocator m_Memory;
	int m_Size;

	// For easier access to the elements through the debugger
	// it's in release builds so this can be used in libraries correctly
	T *m_pElements;

	inline void ResetDbgInfo()
	{
		m_pElements = Base();
	}
};
#endif