#include "VTUElementHandler.h"
#include <qstring.h>

int VTUElementHandler::ConvertToVTKType(const QString& typeLabel) {
	if (typeLabel == "B31") return VTK_LINE;
	if (typeLabel == "T3D2") return VTK_LINE;
	if (typeLabel == "S3") return VTK_TRIANGLE;
	if (typeLabel == "S4R") return VTK_QUAD;
	return 0;
}
int VTUElementHandler::GetArrayLength(const QString& typeLabel) {
	if (typeLabel == "B31") return 2;
	if (typeLabel == "T3D2") return 2;
	if (typeLabel == "S3") return 3;
	if (typeLabel == "S4R") return 4;
	return 0;
}
int VTUElementHandler::GetArrayLength(const int& typeEnum) {
	switch(typeEnum){
		case VTK_LINE: 
			return 2;
		case VTK_TRIANGLE: 
			return 3;
		case VTK_QUAD:
			return 4;
	}
	return 0;
}