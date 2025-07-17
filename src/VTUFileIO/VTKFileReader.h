#pragma once

#include <VTUDataContainer.h>
#include <ErrorHandler.h>
#include <QFile>
#include <QTextStream>
#include <QVector>


// Ç°ÏòÉùÃ÷
class VTUDataContainer;

class VTKFileReader {
public:
	explicit VTKFileReader(QFile* file);
	int ReadVTK();
	VTUDataContainer& GetDataContainer();

private:
	QFile* m_file;
	VTUDataContainer m_dataContainer;

	int ParseHeader(QTextStream& in);
	int ParsePoints(QTextStream& in, int numPoints);
	int ParseCells(QTextStream& in, int numCells);
};