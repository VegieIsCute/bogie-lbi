namespace Bypass
{
	bool Console(const char* Title)
	{
		if (!VirtualProtect(FreeConsole, 1, PAGE_EXECUTE_READWRITE, new unsigned long))
			return false;
		*reinterpret_cast<unsigned int*>(FreeConsole) = 0xC3;
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
		SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 50, 20, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		ShowWindow(GetConsoleWindow(), 1);
		SetConsoleTitleA(Title);
		return true;
	}

	bool Retcheck()
	{
		unsigned long Old = 0;
		void* Retcheck = reinterpret_cast<void*>(Rebase(ADDRESS_RetcheckJMP));

		if (!VirtualProtect(Retcheck, 8, PAGE_EXECUTE_READWRITE, &Old))
			return false;
		*reinterpret_cast<unsigned long long*>(Retcheck) = 0xC35D00000028C481;
		if (!VirtualProtect(Retcheck, 8, Old, &Old))
			return false;
		return true;
	}
}