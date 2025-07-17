#pragma once

#include <ErrorHandler.h>

#include <QtPlugin>
#include <ptoKPartRepository.h>

class VTUContainerWriter;
class FormatWriter;

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
	VTUContainerWriter* writer;
	FormatWriter* fileWriter;

	static const cowListString& GetAssemblyParts(const QString& model);
	static const ptoKPartRepository& GetModelParts(const QString& model);
	int VTUFileManager::writeSinglePart();
	int VTUFileManager::writeAllParts();
	int VTUFileManager::writeODB();

public:
	VTUFileManager();
	virtual ~VTUFileManager();

	int Init(const QString& targetPath, const int& display, const QString& modelName, const QString& partName);
	int WriteCache();
	int WriteFile();
	int ReadTarget();
};

