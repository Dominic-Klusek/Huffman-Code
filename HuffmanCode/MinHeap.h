#ifndef MinHeap_H
#define MinHeap_H
template <class T>
class MinHeap {
public:
	MinHeap(int MSize) {
		MaxSize = MSize;
		heap = new T[MaxSize + 1];
		Size = 0;
	}
	MinHeap<T>& Insert(T& x);
	MinHeap<T>& Delete(T& x);
	~MinHeap() {
		delete[] heap;
	}
	int Size;

private:
	int MaxSize;
	T* heap;
};
#endif