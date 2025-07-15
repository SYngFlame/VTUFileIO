#pragma once

#define TASK_EXPORT 0
#define TASK_IMPORT 1
#define ERRORTYPE_NOTEXIST -1
#define ERRORTYPE_FILEREADFAILED -2
#define ERRORTYPE_FILEWRITEFAILED -3

#include <QtPlugin>
#include <qvector.h>

#include <basMdb.h>

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
	basMdb mdb;
	TargetList target;

	const ptoKPartRepository& GetModelParts();
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

