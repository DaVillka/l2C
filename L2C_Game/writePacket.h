#pragma once
#include <Windows.h>
class WritePacket
{
public:
	void writeC(int id);
	void writeD(DWORD);
	void writeB(byte *, int);
	void writeB(byte);
	void writeS(wchar_t*);
	void writeF(double);
	void writeQ(unsigned __int64);
	void writeH(WORD);
	byte SendPacketBuffer[20480];
	unsigned int size;
};

void WritePacket::writeC(int id)
{
	memcpy(SendPacketBuffer+size, &id, 1);
	size++;
}
void WritePacket::writeD(DWORD id)
{
	memcpy(SendPacketBuffer+size, &id, sizeof(DWORD));
	size+=sizeof(DWORD);
}
void WritePacket::writeB(byte* id, int sizeByte)
{
	for (int i = 0; i < sizeByte; i++)
	{
		memcpy(SendPacketBuffer+size, &id[i], sizeof(byte));
		size+=sizeof(byte);
	}
}
void WritePacket::writeS(wchar_t* wstr)
{
	int len = wcslen(wstr) * 2 + 2;
	memcpy(SendPacketBuffer + size, wstr, len);
	size+=len;
}
void WritePacket::writeF(double id)
{
	memcpy(SendPacketBuffer+size, &id, sizeof(double));
	size+=sizeof(double);
}
void WritePacket::writeQ(unsigned __int64 id)
{
	memcpy(SendPacketBuffer+size, &id, sizeof(unsigned __int64));
	size+=sizeof(unsigned __int64);
}
void WritePacket::writeH(WORD id)
{
	byte* byt = (byte*)&id;
	memcpy(SendPacketBuffer+size, &byt[0], 1);
	size++;
	memcpy(SendPacketBuffer+size, &byt[1], 1);
	size++;
}