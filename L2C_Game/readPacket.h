#pragma once
#include <Windows.h>
class ReadPacket
{
public:
	byte packetRecv[1024];int sizeRecv;int sizeP;
	void readC(int id);
	DWORD readD();
	void readB(byte *, int);
	void readB(byte);
	void readS(wchar_t*);
	void readF(double);
	void readQ(unsigned __int64);
	void readH(WORD);

	bool wstrstr(wchar_t*, wchar_t*);
};

bool ReadPacket::wstrstr(wchar_t* str, wchar_t* command)
{
	if (wcslen(str) != wcslen(command)) return false;
	for (unsigned int i = 0; i < wcslen(command); i++)
		if (str[i] != command[i]) return false;	
	return true;
}

DWORD ReadPacket::readD()
{
	Sleep(1);
	if (sizeP > sizeRecv || sizeRecv < 1) printf("WARNING: readD, Packet->%02X\n", packetRecv[0]);
	DWORD eventy = 0;
	for (unsigned int i = sizeP, b = 0; i < sizeof(DWORD)+sizeP; i++, b++)	
		memset((char*)&eventy+b, packetRecv[i], sizeof(packetRecv[i]));
	sizeP+=sizeof(DWORD);
	return eventy;
}
void  ReadPacket::readS(wchar_t* str )
{
	wchar_t name[255];
	swprintf_s(name, 255, L"%ls", packetRecv+sizeP);
	sizeP+=(wcslen(name)*2+2);
	for (unsigned int i = 0; i < wcslen(name)*2+2; i++)
	{
		str[i] = name[i];
	}
	//memcpy(&str, name, wcslen(name));
	///swprintf_s(str, 255, L"%ls", name);
	//printf("Name: %ls | Name: %ls | SizeP: %d | SizeA: %d | SizeB: %d\n", name, str, sizeP, wcslen(name), wcslen(str));
}