#include "globalhandler.h"
class RecvClientPacket
{
	
public:
	bool RequestAutchLogin(byte* packet);
	bool RequestServerList(byte* packet);
	bool RequestGGAutch   (byte* packet);
	DWORD _loginOk1;
	DWORD _loginOk2;
private:
	int sizeP;
};

bool RecvClientPacket::RequestAutchLogin(byte* packet)
{
	//mask->cSS...кака
	sizeP = 1;
	wchar_t login[255] = L"";
	wchar_t passw[255] = L"";
	

	swprintf_s(login, 255, L"%ls", packet+sizeP);
	sizeP+=(wcslen(login)*2+2);
	swprintf(passw, L"%ls", packet+sizeP);

	wprintf(L"login: %ls | Passw: %ls\n", login, passw);
	//if (wcslen(login) != 0 && wcslen(passw)) return true;
	return true;
}
bool RecvClientPacket::RequestServerList(byte* packet)
{
	//cddc
	sizeP = 1;
	DWORD key1 = *(DWORD*)(packet + sizeP);sizeP+=4;
	DWORD key2 = *(DWORD*)(packet + sizeP);
	if (_loginOk1 == key1 && _loginOk2 == key2) return true;
	return false;
}
bool RecvClientPacket::RequestGGAutch   (byte* packet)
{
	return true;
}