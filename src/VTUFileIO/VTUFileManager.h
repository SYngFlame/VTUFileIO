#pragma once

#include <ErrorHandler.h>

#include <QtPlugin>
#include <ptoKPartRepository.h>

class VTUFileWriter;


enum omuObjectToDisplayTypeEnm;
enum VTKType {
	VTKLegacy,
	VTU
};

struct TargetList{
	const wchar_t* targetPath;
	const wchar_t* targetModel;
	const wchar_t* targetPart;
	VTKType type;
	int displayMode;//int type of omuObjectToDisplayTypeEnm

	bool withOdb;
	TargetList();
	QString TargetList::TargetModel();
	QString TargetList::TargetPart();
	QString TargetList::TargetPath();
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

	int Init(const QString& targetPath, const int& display, const QString& modelName, const QString& partName);
	int WriteCache();
	int ReadTarget();
};

