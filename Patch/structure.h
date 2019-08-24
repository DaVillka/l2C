#pragma pack(push, 1)
struct NetworkPacket
{
    unsigned char id, _padding1, exid, _padding2;
    unsigned short size, _padding3;
    unsigned char* data;
};
#pragma pack(pop)