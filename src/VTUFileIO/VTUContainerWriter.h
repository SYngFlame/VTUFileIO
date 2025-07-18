#pragma once

#include <ErrorHandler.h>

class QString;
class ptoKPart;
class QFile;
class bmeElementClass;
class VTUDataContainer;

class VTUContainerWriter
{

public:
	VTUDataContainer* VTKData;

public:
	int GetVTKPart(const ptoKPart& part);
	VTUDataContainer* GetContainerPointer();
	int VTKExportODB();

	//virtual int WriteFormat();
	VTUContainerWriter();
	~VTUContainerWriter();
};