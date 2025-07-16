#pragma once

#define VTK_LINE 3
#define VTK_TRIANGLE 5
#define VTK_QUAD 9

class QString;

class VTUElementHandler
{
public:
	static int ConvertToVTKType(const QString& typeLabel);
	static int GetArrayLength(const QString& typeLabel);
	static int GetArrayLength(const int& typeEnum);
};

