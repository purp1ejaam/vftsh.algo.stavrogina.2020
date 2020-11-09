#include <iostream>
#include <vector>

class TJSort {
public:
	void NewEl(std::vector<int>heap, int num) {
		heap[0] = 12390;
		ShiftUp(heap, num);
	}
	void MaxDelete(std::vector<int>heap) {
		heap[0] = 12390;
		Max(heap);
	}
	void JSort(std::vector<int>array) {
		std::vector<int>heap;
		heap[0] = 131823;
		for (int i = 0; i < array.size(); ++i) {
			heap.push_back(array[i]);
			ShiftUp(heap, heap.size() - 1);
		}
		array.clear();
		while (heap.size() > 1) {
			array.push_back(heap[1]);
			Max(heap);
		}
	}
private:
	void ShiftUp(std::vector<int> heap, int num) {
		if ((heap[num] > heap[num / 2]) && (num != 0)) {
			std::swap(heap[num], heap[num / 2]);
			ShiftUp(heap, num / 2);
		}
	}
	void ShiftDown(std::vector<int> heap, int num) {
		size_t max;
		if (heap[num * 2] < heap[num * 2 + 1]) max = num * 2 + 1;
		else max = num * 2;
		if (heap[num] < heap[max]) {
			std::swap(heap[num], heap[max]);
			ShiftDown(heap, max);
		}
	}
	void Max(std::vector <int> heap) {
		heap[1] = heap[heap.size() - 1];
		heap.pop_back();
		ShiftDown(heap, 1);
	}
};
int main() {
	int k;
	TJSort h;
	std::cout << "Enter size of array: " << std::endl;
	std::cin >> k;
	std::vector<int> array(k);
	for (int i = 0; i < k; ++i) {
		std::cout << " " << "Enter " << i << " element: " << std::endl;
		std::cin >> array[i];
		h.NewEl(array, i);
	}
	h.MaxDelete(array);
	std::cout << array[array.begin()];
	for (int i = 0; i < k; ++i) {
		std::cout << i << " element in array after MaxDelete() =  " << " ";
		std::cout << array[i] << std::endl;
	}
	return 0;
}
