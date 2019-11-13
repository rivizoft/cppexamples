#include "Memory.h"
#include <TlHelp32.h>
#include <comdef.h>

// pName - �������� ��������, dwAccess - ��� ����������
// ����� ������� - ����� ����� � ��������� � ����
bool Memory::search(const char* pName, DWORD dwAccess)
{
	// �������� ������ ���������� ���������
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		
	// ��� ������, ������� ������ �������
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	// ���� ��� ������� �� �����
	do 
	{
		if (!strcmp(pe32.szExeFile, pName))
		{
			_pId = pe32.th32ProcessID;						// ���� �������, �� ���������� id ��������
			CloseHandle(handle);							
			_process = OpenProcess(dwAccess, false, _pId);	// ���������� � ��� ��������� �������
			return true;									// �������, ��� ������� ������
		}
	} while (Process32Next(handle, &pe32)); // ��� ������� ��������� ��������� ��� ���������� ��������

	return false; // ���� �������� � ������, ���� ������� �� ������
}

// pModule - �������� ������
// ����� ������� ������� �������� �� ������� ������ ������ � �������� ����� �������� � ������
MemModule Memory::getModule(const char* pModule)
{
	// �������� ������ ���������� �������
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _pId);

	// ��� ������ ��� ������
	MODULEENTRY32 me32;
	me32.dwSize = sizeof(me32);

	//���� ��� ������
	(Module32Next(handle, &me32));
	do
	{
		if (!strcmp(me32.szModule, pModule))
		{
			CloseHandle(handle);
			// ���� �������, ���������� memModule
			return MemModule 
			{ 
				reinterpret_cast<DWORD>(me32.hModule), 
				me32.modBaseSize 
			};
		}
	} while (Module32Next(handle, &me32));

	return MemModule { 0, 0 };
}

// ������� �� ��������
void Memory::exit()
{
	CloseHandle(_process);
}

