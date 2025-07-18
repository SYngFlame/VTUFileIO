#include "VTUElementHandler.h"
#include <qstring.h>

/*
* Query the enum VTK type of the element type label.
* Function query types in all dimensions when dimension = 0.
*/
VTUElementHandler::VTKType VTUElementHandler::SimplifiedConvertor(const QString& typeLabel, int dimension) {
	if (dimension == 1) return VTK_LINE;
	else
		return (dimension > 2 ? VTUElementHandler::SimplyConvertTo3DVTKType(typeLabel) : VTUElementHandler::SimplyConvertTo2DVTKType(typeLabel));
	

	//When dimension is 0, query all type
	VTKType type = SimplyConvertTo1DVTKType(typeLabel);
	if (type == VTK_NONE) {
		VTKType type = SimplyConvertTo2DVTKType(typeLabel);
		if (type == VTK_NONE) {
			return SimplyConvertTo3DVTKType(typeLabel);
		}
	}
	return type;
}

VTUElementHandler::VTKType VTUElementHandler::SimplyConvertTo1DVTKType(const QString& typeLabel) {

	if (typeLabel == "B31" || typeLabel == "B33" || typeLabel == "T3D2") return VTK_LINE;
	return VTK_NONE;
}

VTUElementHandler::VTKType VTUElementHandler::SimplyConvertTo2DVTKType(const QString& typeLabel) {

	if (typeLabel == "S4R" || typeLabel == "S4I" || typeLabel == "S4") return VTK_QUAD;
	if (typeLabel == "S3" || typeLabel == "S3R") return VTK_TRIANGLE;
	return VTK_NONE;
}

VTUElementHandler::VTKType VTUElementHandler::SimplyConvertTo3DVTKType(const QString& typeLabel) {

	if (typeLabel == "C3D8"|| typeLabel == "C3D8R") return VTK_VOXEL;

	return VTK_NONE;
}

VTUElementHandler::VTKType VTUElementHandler::ConvertTo1DVTKType(const QString& typeLabel) {

	if (typeLabel == "B31") return VTK_LINE;
	else return VTK_POLY_LINE;
}

bool VTUElementHandler::Check3DVTKType(VTUElementHandler::VTKType type) {

	if (type > 10) return true;

	else return false;
}

//Best avoide using this function because it querys all type.
int  VTUElementHandler::GetArrayLengthByLabel(const QString& typeLabel) {

	return GetArrayLengthByEnum(SimplifiedConvertor(typeLabel, 0));

}
int VTUElementHandler::GetArrayLengthByEnum(VTKType typeEnum) {
	switch(typeEnum){
		case VTK_LINE: 
			return 2;
		case VTK_TRIANGLE: 
			return 3;
		case VTK_QUAD:
			return 4;
		case VTK_VOXEL:
			return 8;
	}
	return 0;
}