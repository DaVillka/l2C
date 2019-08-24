#pragma once
#include <Windows.h>
class WritePacket
{
public:
	void writeC(int id);
	void writeD(DWORD);
	void writeB(byte *, int);
	void writeB(byte);
	void writeS(char*);
	void writeF(double);
	void writeQ(long);
	void writeH(WORD);
	byte SendPacketBuffer[10240];
	int size;
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

void WritePacket::writeS(char* str)
{
	//char byt[3] = "";
	//sprintf(byt, "%02X", id);
	//strcat(SendPacketBuffer, byt);
}
void WritePacket::writeF(double)
{
}
void WritePacket::writeQ(long)
{
}
void WritePacket::writeH(WORD id)
{
	byte* byt = (byte*)&id;
	memcpy(SendPacketBuffer+size, &byt[0], 1);
	size++;
	memcpy(SendPacketBuffer+size, &byt[1], 1);
	size++;
}