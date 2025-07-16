#pragma once

#include <ErrorType.h>

class QString;
class ptoKPart;
class QFile;

class VTUFileWriter
{
private:
	QFile* file;
	int VTKExportPart(const ptoKPart& part);
	static int matchElemType(const QString& typeLabel);

public:
	
	VTUFileWriter(QFile* file);
	VTUFileWriter();
	~VTUFileWriter();
};

