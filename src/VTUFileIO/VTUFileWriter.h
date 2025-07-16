#pragma once

#include <ErrorHandler.h>
#include <VTUDataContainer.h>

class QString;
class ptoKPart;
class QFile;
class bmeElementClass;
class VTUDataContainer;

class VTUFileWriter
{

private:
	VTUDataContainer VTKData;

protected:
	QFile* file;

public:
	int GetVTKPart(const ptoKPart& part);
	int VTKExportODB();
	//virtual int WriteFormat();
	VTUFileWriter(QFile* file);
	VTUFileWriter();
	~VTUFileWriter();
};

