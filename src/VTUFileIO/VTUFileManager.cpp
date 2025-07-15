#include "VTUFileManager.h"

#include <ptoKPart.h> 
#include <ftrFeatureList.h>
#include <visKSceneManager.h>

#include <basMdb.h>
#include <basBasis.h>
#include <basNewModel.h>
#include <ptoKUtils.h>
#include <bmeMesh.h> 
#include <bmeElementClass.h>
#include <bmeElementClassList.h>
#include <sesKSessionState.h>

#include <qfile.h>

VTUFileManager::VTUFileManager() {
	
}

VTUFileManager::~VTUFileManager() {
}

TargetList::TargetList() {
	targetPath = "";
	type = VTKLegacy;
	withOdb = false;
	displayMode = omu_NONE;
}

const ptoKPartRepository& VTUFileManager::GetModelParts() {

	basBasis* bas = basBasis::Instance();

	this->mdb = bas->Fetch();
	return ptoKConstGetPartRepos(mdb, target.targetModel);
}

/*
Read in mdb for extract nodes and elements and path to output VTK files
*/
int VTUFileManager::Init(const QString& path, const QString& display, const QString& modelName, const QString& partName) {
	
	this->target.targetPath = path;
	this->target.displayMode = omuPrimType::ConverStringToType(display);
	this->target.targetModel = modelName;
	this->target.targetPart = partName;
	return 0;
};

int VTUFileManager::WriteTarget() {
	QFile f(target.targetPath);
	if (f.exists()) {
		//TODO:Warning box
	}
	f.open(QIODevice::WriteOnly | QIODevice::Truncate);
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
	return 0;
}
int VTUFileManager::ReadTarget() {
	return 0;
}
///*
//* Everything normal if return 0;
//* If mdb not exist , return -1.
//*/
//int VTUFileManager::Ready() {
//	if (SAMmodels.isEmpty()||SAMparts.isEmpty()) 
//		return ERRORTYPE_NOTEXIST;
//	return 0;
//}

int VTUFileManager::writeSinglePart() {
	const ptoKPartRepository& parts = GetModelParts();
	if (parts.Size() == 0)
		return ERRORTYPE_NOTEXIST;
	return VTKExportPart(parts.ConstGet(target.targetPart))
}

int VTUFileManager::writeAllParts() {
	const ptoKPartRepository& parts = GetModelParts();
	if (parts.Size() == 0)
		return ERRORTYPE_NOTEXIST;
	int status = 0;
	for (int i; i < parts.Size(); ++i) {
		status &= VTKExportPart(parts.ConstGet(i));
	}
	return status;
}

int VTUFileManager::writeODB() {
	return 0;
}
