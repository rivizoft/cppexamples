#include <iostream>
#include "Memory.h"

#define oPlayer 0xCFAA3C
#define oHealth 0x100
#define oTeam	0xF4
#define oEntityList 0x4D0D0A4
#define oGlowIndex 0xA40C
#define oGlowObjManager 0x524D518

Memory memory;
MemModule clientBase;

//������� ��� ����������� �����))
void wallhack()
{
	while (true) // ������� ����������� ����
	{
		Sleep(10); // ������� 10 ��, ����� �� ������� ��������� ��� 100

		DWORD glowObj = memory.read<DWORD>(clientBase.dwAddress + oGlowObjManager); // ������� ������ glowObj �� �������� ������
		DWORD myTeam = memory.read<DWORD>(memory.read<DWORD>(clientBase.dwAddress + oPlayer) + oTeam); // ������� ������ ���������

		for (int x = 0; x < 32; x++) // ��� ��
		{
			DWORD player = memory.read<DWORD>(clientBase.dwAddress + oEntityList + x * 0x10); // ������� �����
			if (player == 0)
				continue;

			bool dormant = memory.read<bool>(player + 0xED); // ���������
			if (dormant)
				continue;

			DWORD team = memory.read<DWORD>(player + oTeam); // �������
			if (team != 2 && team != 3)
				continue;

			DWORD currentGlowIndex = memory.read<DWORD>(player + oGlowIndex); // ������� ������ ������

			if (team != myTeam) // ���� ����� �� �������
			{
				// ������ ��� ������� �������
				memory.write<float>(glowObj + currentGlowIndex * 0x38 + 0x4, 255); // red
				memory.write<float>(glowObj + currentGlowIndex * 0x38 + 0x8, 0); // green
				memory.write<float>(glowObj + currentGlowIndex * 0x38 + 0xC, 0); // blue
				memory.write<float>(glowObj + currentGlowIndex * 0x38 + 0x10, 255);
				memory.write<bool>(glowObj + currentGlowIndex * 0x38 + 0x24, true);
				memory.write<bool>(glowObj + currentGlowIndex * 0x38 + 0x25, false);
			}
			else // ���� ����� �������
			{
				// ������ ��� ������� �����
				memory.write<float>(glowObj + currentGlowIndex * 0x38 + 0x4, 0); // red
				memory.write<float>(glowObj + currentGlowIndex * 0x38 + 0x8, 0); // green
				memory.write<float>(glowObj + currentGlowIndex * 0x38 + 0xC, 255); // blue
				memory.write<float>(glowObj + currentGlowIndex * 0x38 + 0x10, 255);
				memory.write<bool>(glowObj + currentGlowIndex * 0x38 + 0x24, true);
				memory.write<bool>(glowObj + currentGlowIndex * 0x38 + 0x25, false);
			}
		}
	}
}

int main() 
{
	//���� �������
	bool success = memory.search("csgo.exe", PROCESS_ALL_ACCESS);

	//���� ������� �� ������, ��������� ������
	if (!success) {
		std::cout << "process not found!";
		return 1;
	}
	
	clientBase = memory.getModule("client_panorama.dll"); // ���� ������ �� ��

	std::cout << "clientBase " << clientBase.dwAddress << std::endl; //������� �����
	
	while (true)
	{
		// ������ ������ ������ ������ - ��������� ����� + ������ 0xCFAA3C
		DWORD player = memory.read<DWORD>(clientBase.dwAddress + oPlayer);
		printf("player: 0x%X\n", player);
		// ���������� ����� ������ + ������ �������� 0x100
		DWORD health = memory.read<DWORD>(player + oHealth);
		printf("health: %d\n", health);
		// ����� ������ + ������ ����� ������� 0xF4
		DWORD team = memory.read<DWORD>(player + oTeam);
		printf("team: %d\n", team);

		Sleep(1000);
		system("cls");
	}
	memory.exit();
	system("pause");
	return 0;
}