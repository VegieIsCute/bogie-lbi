namespace Colors
{
	std::string DarkBlue()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		return "";
	}
	std::string DarkGreen()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		return "";
	}
	std::string LightBlue()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		return "";
	}
	std::string DarkRed()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		return "";
	}
	std::string DarkPurple()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		return "";
	}
	std::string Orange()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		return "";
	}
	std::string Grey()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		return "";
	}
	std::string Aqua()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		return "";
	}
	std::string LightGreen()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		return "";
	}
	std::string LightAqua()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		return "";
	}
	std::string LightRed()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		return "";
	}
	std::string LightPurple()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		return "";
	}
	std::string Yellow()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		return "";
	}
	std::string White()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		return "";
	}
}

namespace Console
{
	char time_buffer[100];
	time_t ltime;
	struct tm* tmstruct;

	std::string GetTime()
	{
		time(&ltime);
		tmstruct = localtime(&ltime);
		strftime(time_buffer, sizeof(time_buffer), "%X", tmstruct);
		return time_buffer;
	}

	void PrintInfo(std::string Class, std::string Content)
	{

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 48);
		std::cout << " ";
		std::cout << Colors::White() << " [";
		std::cout << Colors::Grey() << GetTime();
		std::cout << Colors::White() << "] [";
		std::cout << Colors::LightAqua() << "INFO";
		std::cout << Colors::White() << "] [";
		std::cout << Colors::LightBlue() << Class;
		std::cout << Colors::White() << "]";
		std::cout << Colors::Grey() << " -> ";
		std::cout << Colors::Yellow() << Content << "\n";
	}
	void PrintWarn(std::string Class, std::string Content)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
		std::cout << " ";
		std::cout << Colors::White() << " [";
		std::cout << Colors::Grey() << GetTime();
		std::cout << Colors::White() << "] [";
		std::cout << Colors::Yellow() << "WARN";
		std::cout << Colors::White() << "] [";
		std::cout << Colors::LightBlue() << Class;
		std::cout << Colors::White() << "]";
		std::cout << Colors::Grey() << " -> ";
		std::cout << Colors::Yellow() << Content << "\n";
	}
	void PrintError(std::string Class, std::string Content)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);
		std::cout << " ";
		std::cout << Colors::White() << " [";
		std::cout << Colors::Grey() << GetTime();
		std::cout << Colors::White() << "] [";
		std::cout << Colors::LightRed() << "ERR";
		std::cout << Colors::White() << "]  [";
		std::cout << Colors::LightBlue() << Class;
		std::cout << Colors::White() << "]";
		std::cout << Colors::Grey() << " -> ";
		std::cout << Colors::Yellow() << Content << "\n";
	}
}