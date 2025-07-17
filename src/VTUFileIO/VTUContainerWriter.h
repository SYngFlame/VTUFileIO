#pragma once

#include <ErrorHandler.h>
#include <VTUDataContainer.h>

class QString;
class ptoKPart;
class QFile;
class bmeElementClass;
class VTUDataContainer;

class VTUContainerWriter
{

private:
	VTUDataContainer VTKData;

protected:
	QFile* file;

public:
	int GetVTKPart(const ptoKPart& part);
	const VTUDataContainer& GetContainer();
	int VTKExportODB();

	//virtual int WriteFormat();
	VTUContainerWriter(QFile* file);
	VTUContainerWriter();
	~VTUContainerWriter();
};

