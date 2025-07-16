#include "VTUFileManager.h"

#include <ptoKUtils.h>
#include <ptoKPartRepository.h>
#include <ptoKPart.h> 
#include <ftrFeatureList.h>

#include <basMdb.h>
#include <basBasis.h>
#include <basNewModel.h>
#include <omuPrimType.h>
#include <FEOdb.h>

#include <VTUFileWriter.h>
#include <qfile.h>

VTUFileManager::VTUFileManager() {
}

VTUFileManager::~VTUFileManager() {
}

TargetList::TargetList() {
	targetPath = NULL;
	targetPart = NULL;
	targetModel = NULL;
	type = VTKLegacy;
	withOdb = false;
	displayMode = omu_NONE;
}

const ptoKPartRepository& VTUFileManager::GetModelParts(const QString& model) {

	basBasis* bas = basBasis::Instance();

	basMdb mdb = bas->Fetch();
	return ptoKConstGetPartRepos(mdb, model);
}

/*
Read in mdb for extract nodes and elements and path to output VTK files
*/
int VTUFileManager::Init(const QString& path, const int& display, const QString& modelName, const QString& partName) {
	
	this->target.targetPath = reinterpret_cast<const wchar_t*>(path.utf16());
	this->target.displayMode = display;
	this->target.targetModel = reinterpret_cast<const wchar_t*>(modelName.utf16());
	this->target.targetPart = reinterpret_cast<const wchar_t*>(partName.utf16());
	return 0;
};

int VTUFileManager::WriteCache() {
	
	writer = new VTUFileWriter();
	switch (target.displayMode) {
		case omu_PART: {
			return writeSinglePart();
		}
		case omu_ASSEMBLY: {
			return writeAllParts();
		}
		case omu_ODB: {
			return writeODB();
		}
	}
	return ERRORTYPE_WRONGSCENE;
}

int VTUFileManager::ReadTarget() {
	return 0;
}

int VTUFileManager::writeSinglePart() {
	const ptoKPartRepository parts = GetModelParts(target.TargetModel());
	if (parts.IsEmpty())
		return ERRORTYPE_NOTEXIST;
	return writer->GetVTKPart(parts.ConstGet(target.TargetPart()));
}

int VTUFileManager::writeAllParts() {
	const ptoKPartRepository& parts = GetModelParts(target.TargetModel());
	if (parts.IsEmpty())
		return ERRORTYPE_NOTEXIST;
	int status = 0;
	for (int i = 1; i <= parts.Size(); ++i) {
		status &= writer->GetVTKPart(parts.ConstGet(i));
	}
	return status;
}

int VTUFileManager::writeODB() {
	//FEOdb::get
	
	return writer->VTKExportODB();
}

QString TargetList::TargetModel() {
	return QString::fromWCharArray(targetModel);
}

QString TargetList::TargetPart() {
	return QString::fromWCharArray(targetPart);
}

QString TargetList::TargetPath() {
	return QString::fromWCharArray(targetPath);
}