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
		case VTK_PIXEL:case VTK_QUAD:
			return 4;
		case VTK_VOXEL:case VTK_HEXAHEDRON:
			return 8;
	}
	return 0;
}

/*
* Return QString type of SAM elements type label.
* For beams, return B31 when beamType=0, B33 when 1, T3D2 when 2.
* For cubes, return C3D8 when cubeType=0, C3D8R when 1.
* For quads, return S4 when quadType=0, S4I when 1, S4R when 2.
*/
QString VTUElementHandler::GetSAMTypeByVTKType(VTKType typeEnum, int beamType, int cubeType, int quadType) {
	switch (typeEnum)
	{
		case VTK_NONE:
			return "";
		case VTK_VERTEX:
			return "";
		case VTK_POLYVERTEX:
			return "";
		case VTK_LINE:
			return beamType ? (beamType ==1 ? "B33" : "T3D2") : "B31";
		case VTK_TRIANGLE:
			return "S3";
		case VTK_TRIANGLE_STRIP:
			return "";
		case VTK_POLYGON:
			return "";
		case VTK_PIXEL:case VTK_QUAD:
			return quadType ? (quadType == 1 ? "S4I" : "S4R") : "S4";
		case VTK_TETRA:
			return "";
		case VTK_VOXEL:
			return cubeType ? "C3D8R" : "C3D8";
		case VTK_HEXAHEDRON:
			return "";
		default:
			return "";
	}
}

bool VTUElementHandler::IsCube(VTKType typeEnum) {
	return (typeEnum == VTK_VOXEL) || (typeEnum == VTK_HEXAHEDRON);
}