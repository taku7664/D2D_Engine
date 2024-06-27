#pragma once

// ����� ���� ����ü
struct
{

	HANDLE m_hConsole;
	FILE* m_fCout;

	bool IsActive() { return m_hConsole != nullptr; }

	// �ܼ�â�� ����մϴ�.
	bool Get_Console()
	{
		if (!AllocConsole())
		{
			return false;
		}
		else
		{
			SetConsoleTitle(TEXT("Debug Console"));
			m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			_wfreopen_s(&m_fCout, L"CONOUT$", L"w", stdout);
			Log("Get_Console : Ok");
			return true;
		}
	}

	// �ܼ�â�� �ݽ��ϴ�.
	bool Close_Console()
	{
		if (m_fCout)
		{
			fclose(m_fCout);
			m_fCout = nullptr;
		}
		if (FreeConsole())
		{
			m_hConsole = nullptr;
			return true;
		}
		else
			return false;
	}
	// �ܼ��� ����ϴ�.
	void Clear()
	{
		system("cls");
	}
	// �ܼ� â�� ���ڸ� ����մϴ�.
	bool Log(const char* _log)
	{
		if (printf_s(_log) <= 0) return false;
		else
		{
			printf_s("\n");
			return true;
		}
	}
	bool Log(std::string _log)
	{
		if (printf_s(_log.c_str()) <= 0) return false;
		else
		{
			printf_s("\n");
			return true;
		}
	}
	bool Log(std::wstring _log)
	{
		if (wprintf_s(_log.c_str()) <= 0) return false;
		else
		{
			printf_s("\n");
			return true;
		}
	}
}Debug;