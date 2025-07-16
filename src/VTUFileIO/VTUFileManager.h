#pragma once

#include <ErrorType.h>

#include <QtPlugin>
#include <qvector.h>
#include <ptoKPartRepository.h>

class VTUFileWriter;


enum omuObjectToDisplayTypeEnm;
enum VTKType {
	VTKLegacy,
	VTU
};

struct TargetList{
	QString targetPath;
	QString targetModel;
	QString targetPart;
	VTKType type;
	omuObjectToDisplayTypeEnm displayMode;

	bool withOdb;
	TargetList();
};

class VTUFileManager
{
private:
	TargetList target;
	VTUFileWriter* writer;

	static const ptoKPartRepository& GetModelParts(const QString& model);
	int VTUFileManager::writeSinglePart();
	int VTUFileManager::writeAllParts();
	int VTUFileManager::writeODB();

public:
	VTUFileManager();
	virtual ~VTUFileManager();
	//int Ready();

	int Init(const QString& targetPath, const QString& display, const QString& modelName, const QString& partName);
	int WriteTarget();
	int ReadTarget();
};

