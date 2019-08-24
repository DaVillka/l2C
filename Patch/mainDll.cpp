#include "global.h"
#include "MyHookFunc.h"



DWORD WINAPI InitNew(LPVOID)
{
	ConsoleCreate();
	hEngine = LoadLibrary("Engine.dll");
	if (hEngine == NULL) printf("hEngine == NULL\n");
	hWs2_32 = LoadLibrary("WS2_32.dll");
	if (hWs2_32 == NULL) printf("hWs2_32 == NULL\n");

	UAddNetworkQueue = reinterpret_cast<UNetworkHandler_AddNetworkQueue>(GetProcAddress(hEngine, "?AddNetworkQueue@UNetworkHandler@@UAEHPAUNetworkPacket@@@Z")); 
	void** ServerPacketCountStart = (void**)GetProcAddress(hEngine, "?ServerPacketCountStart@UNetworkHandler@@UAEXXZ");
	USendMessageLogin = reinterpret_cast<UNetworkHandler_SendMessage>((DWORD)ServerPacketCountStart + 0x80/*0x520*/);
	USendMessageGame  = reinterpret_cast<UNetworkHandler_SendMessage>((DWORD)ServerPacketCountStart + 0x520);
	Init = reinterpret_cast<UNetworkHandler_Init>(GetProcAddress(hEngine, "?Init@UNetworkHandler@@UAEXHPAVUGameEngine@@@Z"));

	mysend = reinterpret_cast<my_sock>(GetProcAddress(hWs2_32, "send"));
	myrecv = reinterpret_cast<my_sock>(GetProcAddress(hWs2_32, "recv"));
	//myWSAStartup = reinterpret_cast<my_WSAStartup>(GetProcAddress(hWs2_32, "WSAStartup"));
	//mysocket = reinterpret_cast<my_socket>(GetProcAddress(hWs2_32, "socket"));
	myConnect = reinterpret_cast<my_connect>(GetProcAddress(hWs2_32, "connect"));
	RequestAuthLogin = reinterpret_cast<UNetworkHandler_RequestAuthLogin>(GetProcAddress(hEngine, "?RequestAuthLogin@UNetworkHandler@@UAEHPB_W0H@Z")); 
	Tick = reinterpret_cast<UNetworkHandler_Tick>(GetProcAddress(hEngine, "?Tick@UNetworkHandler@@UAEXM@Z")); 

	

	HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (Init), reinterpret_cast<unsigned char*> (&MyInit), trampoline[6]);
	//HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (mysocket), reinterpret_cast<unsigned char*> (&Hook_socket), trampoline[5]);
	//HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (myWSAStartup), reinterpret_cast<unsigned char*> (&Hook_WSAStartup), trampoline[4]);
	HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (myConnect), reinterpret_cast<unsigned char*> (&Hook_Connect), trampoline[7]);
	HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (myrecv), reinterpret_cast<unsigned char*> (&Hook_recv), trampoline[3]);
	//HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (mysend), reinterpret_cast<unsigned char*> (&Hook_send), trampoline[2]);
	HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (USendMessageLogin), reinterpret_cast<unsigned char*> (&SendMessage_hook), trampoline[0]);
	HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (USendMessageGame), reinterpret_cast<unsigned char*> (&SendMessage_hook), trampoline[0]);
	HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (UAddNetworkQueue), reinterpret_cast<unsigned char*> (&UNetworkHandler_AddNetworkQueue_hook), trampoline[1]);
	HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (RequestAuthLogin), reinterpret_cast<unsigned char*> (&UNetworkHandler_AuthLogin), trampoline[8]);
	//HookHelper::HookFunctionWithTrampoline(reinterpret_cast<unsigned char*> (Tick), reinterpret_cast<unsigned char*> (&UNetworkHandler_TickHook), trampoline[9]);
	return 0;
}



extern "C" __declspec(dllexport) int DirectXSetupGetVersion(void){return 0;}
BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
	if (DLL_PROCESS_ATTACH != ul_reason_for_call)
		return 1;
	DisableThreadLibraryCalls(hModule);
	hMod = hModule;
	CreateThread(0, 0, &InitNew, 0, 0, 0);
	return 1;
}