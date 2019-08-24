#include "global.h"


#define BEA_ENGINE_STATIC
#define BEA_USE_STDCALL
#include "BeaEngine\BeaEngine.h"

#pragma comment (lib, "BeaEngine\\BeaEngine.lib")


class HookHelper
{
public:
	inline static unsigned int CalculateJump_X86(unsigned char* from, unsigned char* to) {
		return 0 -(from - to) - 5;}

	inline static void ChangeProtection(void* ptr, size_t size, DWORD& protection)
	{
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, GetCurrentProcessId());
		VirtualProtectEx(hProc, ptr, size, protection, &protection);
		CloseHandle(hProc);

	}

	inline static void* Alloc(size_t size, DWORD protection)
	{
		return VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT, protection);
	}

	static void HookFunction(unsigned char* origFuncPtr, unsigned char* hookFuncPtr); 
	static void HookFunctionWithTrampoline(unsigned char* origFuncPtr, unsigned char* hookFuncPtr, unsigned char*& trampoline);
};
/*
void HookHelper::HookFunction(unsigned char* origFuncPtr, unsigned char* hookFuncPtr)
{
	DISASM disasm = {0};
	disasm.EIP = reinterpret_cast<size_t> (origFuncPtr);

	unsigned char totalLen = 0;

	unsigned char jmp_bytes[5] = {0xE9};
	signed char delta = 0;

	while (totalLen < 5)
	{
		unsigned char currentLen = Disasm(&disasm);
		totalLen += currentLen;
		disasm.EIP += currentLen;
	}

	delta = totalLen - 5;

	(*(unsigned int*)(jmp_bytes + 1)) = HookHelper::CalculateJump_X86(origFuncPtr, hookFuncPtr);

	DWORD protection = PAGE_EXECUTE_READWRITE;
	HookHelper::ChangeProtection(origFuncPtr, totalLen + delta, protection);
	memcpy(origFuncPtr, jmp_bytes, 5);
	if (delta) memset(origFuncPtr, 0x90, delta);
	HookHelper::ChangeProtection(origFuncPtr, totalLen + delta, protection);
}*/

void HookHelper::HookFunctionWithTrampoline(unsigned char* origFuncPtr, unsigned char* hookFuncPtr, unsigned char*& trampoline)
{
	const int retBytw = 5;
	DISASM disasm = {0};
	disasm.EIP = reinterpret_cast<size_t> (origFuncPtr);

	unsigned char totalLen = 0;

	unsigned char jmp_bytes[retBytw] = {0xE9};
	signed char delta = 0;

	while (totalLen < retBytw)
	{
		unsigned char currentLen = Disasm(&disasm);
		totalLen += currentLen;
		disasm.EIP += currentLen;
	}
	delta = totalLen - retBytw;


	trampoline = reinterpret_cast<unsigned char*> (HookHelper::Alloc(totalLen + retBytw, PAGE_EXECUTE_READWRITE));
	(*(unsigned int*)(jmp_bytes + 1)) = HookHelper::CalculateJump_X86(trampoline + totalLen, origFuncPtr + retBytw + delta);
	memcpy(trampoline, origFuncPtr, totalLen);
	memcpy(trampoline + totalLen, jmp_bytes, retBytw);


	(*(unsigned int*)(jmp_bytes + 1)) = HookHelper::CalculateJump_X86(origFuncPtr, hookFuncPtr);
	DWORD protection = PAGE_EXECUTE_READWRITE;
	HookHelper::ChangeProtection(origFuncPtr, totalLen + delta, protection);
	memcpy(origFuncPtr, jmp_bytes, retBytw);
	if (delta) memset(origFuncPtr + retBytw, 0x90, delta);
	//HookHelper::ChangeProtection(origFuncPtr, totalLen + delta, protection);
}

/*
void HookHelper::HookFunctionWithTrampoline(unsigned char* origFuncPtr, unsigned char* hookFuncPtr)
{
	DISASM disasm = {0};
	disasm.EIP = reinterpret_cast<size_t> (origFuncPtr);

	unsigned char totalLen = 0;

	unsigned char jmp_bytes[5] = {0xE9};
	signed char delta = 0;

	while (totalLen < 5)
	{
		unsigned char currentLen = Disasm(&disasm);
		totalLen += currentLen;
		disasm.EIP += currentLen;
	}
	delta = totalLen - 5;

	(*(unsigned int*)(jmp_bytes + 1)) = HookHelper::CalculateJump_X86(origFuncPtr, hookFuncPtr);
	DWORD protection = PAGE_EXECUTE_READWRITE;
	HookHelper::ChangeProtection(origFuncPtr, totalLen + delta, protection);
	memcpy(origFuncPtr, jmp_bytes, 5);
	if (delta) memset(origFuncPtr + 5, 0x90, delta);
	HookHelper::ChangeProtection(origFuncPtr, totalLen + delta, protection);
	
}*/
