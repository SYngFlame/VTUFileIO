#pragma once

class QString;

class VTUElementHandler
{
public:
	static enum VTKType {
		VTK_NONE,
		VTK_VERTEX,
		VTK_POLYVERTEX,
		VTK_LINE,
		VTK_POLY_LINE,
		VTK_TRIANGLE,
		VTK_TRIANGLE_STRIP,
		VTK_POLYGON,
		VTK_PIXEL,
		VTK_QUAD,
		VTK_TETRA,
		VTK_VOXEL,
		VTK_HEXAHEDRON
	};

public:
	static VTKType SimplifiedConvertor(const QString& typeLabel, int dimension);

	static VTKType ConvertTo1DVTKType(const QString& typeLabel);

	static VTKType SimplyConvertTo1DVTKType(const QString& typeLabel);
	static VTKType SimplyConvertTo2DVTKType(const QString& typeLabel);
	static VTKType SimplyConvertTo3DVTKType(const QString& typeLabel);

	static bool Check3DVTKType(VTUElementHandler::VTKType type);

	static int GetArrayLengthByLabel(const QString& typeLabel);
	static int GetArrayLengthByEnum(VTKType typeEnum);

	static QString GetSAMTypeByVTKType(VTKType typeEnum, int beamType = 0, int cubeType = 0, int quadType = 0);
};

