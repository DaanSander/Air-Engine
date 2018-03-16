#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <stdio.h>
#define ASSERTION_ENABLED 1
#if ASSERTION_ENABLED
#define DebugBreak() {DebugBreak();}

#define ASSERT(expr) \
	if(expr) {} \
	else \
	{ \
	printf("Assertion: %s failed in: %s at line: %u", #expr , __FILE__ , __LINE__); \
	DebugBreak();}
#else 
#define ASSERT(expr)
#endif