#ifndef MaxHeap_H
#define MaxHeap_H
template <class T>
class MaxHeap {
public:
	MaxHeap(int MSize) {
		MaxSize = MSize;
		heap = new T[MaxSize + 1];
		Size = 0;
	}
	MaxHeap<T>& Insert(T& x);
	MaxHeap<T>& Delete(T& x);
	~MaxHeap() {
		delete[] heap;
	}
	int Size;

private:
	int MaxSize;
	T* heap;
};
#endif