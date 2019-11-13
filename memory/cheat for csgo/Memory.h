#include <Windows.h>

struct MemModule
{
	DWORD dwAddress;
	DWORD dwSize;
};

class Memory
{
public: 
	bool search(const char* pName, DWORD dwAccess);
	MemModule getModule(const char* pModule);

	template<typename T>
	T read(const DWORD address)
	{
		T read;
		ReadProcessMemory(_process, LPVOID(address), &read, sizeof(T), 0);
		return read;
	}

	template<typename T>
	void write(const DWORD address, const T value)
	{
		WriteProcessMemory(_process, LPVOID(address), &value, sizeof(T), 0);
	}

	void exit();

private: 
	HANDLE _process;
	DWORD _pId;
};

