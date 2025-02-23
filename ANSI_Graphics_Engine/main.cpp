﻿#include "core/window/ansi_window.h"

int main()
{
	int result{ -1 };	// stores result of main()

	// If Init & Run + Finished SUCCESSFULLY -> result = SUCCESS
	if (ansi::Core::CreateInstance() && ansi::Core::GetWindow()->Run()) {
		result = 0;	
	}

	//int* a = new int(); // Memory Leak on Purpose
	ansi::Core::DeleteInstance();

	return result;
}