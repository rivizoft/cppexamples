#include <iostream>

void siftDown(int arr[], int size, int parent) {
	int largest = parent;		//������ ������
	int left = 2 * parent + 1;	//����� ��������
	int right = 2 * parent + 2;	//������ ��������

	//������ ���� ����� �������� ������� ������ ������
	if (left < size && arr[left] > arr[largest]) {
		largest = left;
	}

	//������ ���� ������ �������� ������� ������ ������
	if (right < size && arr[right] > arr[largest]) {
		largest = right;
	}

	if (largest != parent) {
		//������ ������� ������ � �������� �������
		std::swap(arr[parent], arr[largest]);
		//���������� ���������� ��������� ���������� ������� �� �������
		siftDown(arr, size, largest);
	}
}

//�������� ������� ����������
void heap_sort (int arr[], int size) {

	//1-�� �����
	for (int i = size / 2 - 1; i >= 0; i--) {
		siftDown(arr, size, i);
	}

	//2-�� �����
	for (int i = size - 1; i >= 0; i--) {
		//���������� ������� ������ � �����
		std::swap(arr[0], arr[i]);
		//�������� �� ���� � �������� size - 1
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
