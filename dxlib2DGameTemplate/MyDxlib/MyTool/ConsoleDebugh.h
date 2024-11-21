#pragma once
#include "MyTool.h"
//STL.
#include <iostream>
#include <consoleapi.h>

namespace MyTool
{

	class ConsoleDebug
	{
	public:
		void Init()
		{
			AllocConsole();// コンソールを開く
			freopen_s(&out, "CON", "w", stdout); // stdout
			freopen_s(&in, "CON", "r", stdin);   // stdin
		}

	private:
		FILE* out = 0;
		FILE* in = 0;
	};

	void ConsoleDebug::Init() {

	}
}

