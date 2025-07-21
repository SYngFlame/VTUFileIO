#ifndef VTUFILEMANAGER
#define VTUFILEMANAGER

#include <ptoKPartRepository.h>
#include <basShortcut.h>
#include <QtPlugin>

class VTUContainerWriter;
class VTUContainerReader;
class FormatWriter;
class FormatReader;
class QString;

enum omuObjectToDisplayTypeEnm;
enum VTKType {
	VTKLegacy,
	VTU
};

struct TargetList{
	const wchar_t* targetPath;
	const wchar_t* targetModel;
	const wchar_t* targetPart;
	int targetPartID;
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
	VTUContainerReader* reader;
	FormatWriter* fileWriter;
	FormatReader* fileReader;

	static const cowListString& GetAssemblyParts(const QString& model);
	static ptoKPartRepository& GetModelParts(const QString& model);
	static const ptoKPartRepository& ConstGetModelParts(const QString& model);
	int VTUFileManager::writeSinglePart();
	int VTUFileManager::writeAllParts();
	int VTUFileManager::writeODB();

public:
	VTUFileManager();
	virtual ~VTUFileManager();

	void Init(const QString& targetPath, const int& display, const QString& modelName, const QString& partName);
	void Init(const QString& targetPath, const QString& modelName);
	int WriteCache();
	int WriteFile();
	int ReadToCache();
	int ReadToSAM();
	void SyncSAM(basNewModelShortcut& modelShortcut);
};

#endif // !VTUFILEMANAGER