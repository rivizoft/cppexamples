#include <iostream>
#include <Windows.h>
#include <string>

int main() {
	DWORD actual_money = 0x0B9754D4; //Адрес в памяти, который хранит деньги
	DWORD pId;						 //Переменная для ID процесса - т.е. поток контры
	int new_money = 10;
	
	//Ищем окно с контрой
	auto hWind = FindWindow(0, "Counter-Strike");

	//Получаем процесс и проверяем на то, что нашли 
	GetWindowThreadProcessId(hWind, &pId);
	if (!hWind) {
		std::cout << "Process not found!";
		return -1;
	}

	//открываем наш процесс и просим полный доступ
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);	
	if (!pHandle) {
		std::cout << "Do not open procees!";
		return -1;
	}

	//Читаем, что находится по нашему адресу в памяти и записываем его в new_money
	ReadProcessMemory(pHandle, (LPVOID)actual_money, &new_money, sizeof(new_money), 0);
	std::cout << "Actual money: " << new_money << std::endl;

	std::cout << "Need money: ";
	std::cin >> new_money;
	
	//Меняем значение по адресу в памяти на наше значение new_money
	WriteProcessMemory(pHandle, (LPVOID)actual_money, &new_money, sizeof(new_money), 0);
	std::cout << "New money: " << new_money;

	return 0;
}