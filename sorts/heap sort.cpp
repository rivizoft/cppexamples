#include <iostream>

void siftDown(int arr[], int size, int parent) {
	int largest = parent;		//корень дерева
	int left = 2 * parent + 1;	//левый дочерний
	int right = 2 * parent + 2;	//правый дочерний

	//случай если левый дочерний элемент больше предка
	if (left < size && arr[left] > arr[largest]) {
		largest = left;
	}

	//случай если правый дочерний элемент больше предка
	if (right < size && arr[right] > arr[largest]) {
		largest = right;
	}

	if (largest != parent) {
		//меняем местами предка и дочерний элемент
		std::swap(arr[parent], arr[largest]);
		//продолжаем рекурсивно поднимать наибольший элемент на вершину
		siftDown(arr, size, largest);
	}
}

//основная функция сортировки
void heap_sort (int arr[], int size) {

	//1-ая часть
	for (int i = size / 2 - 1; i >= 0; i--) {
		siftDown(arr, size, i);
	}

	//2-ая часть
	for (int i = size - 1; i >= 0; i--) {
		//перемещаем текущий корень в конец
		std::swap(arr[0], arr[i]);
		//вызываем на куче с размером size - 1
		siftDown(arr, i, 0);
	}
}

int main(int argc, char* argv[])
{
	int arr[] = { 10, 5, 6, 45, 67, 0, -11, 20, 50, 5, 5, 101, -566, 7};
	int size = 14;

	heap_sort(arr, 14);
	
	for (auto i : arr)
		std::cout << i << " ";

	return 0;
}
