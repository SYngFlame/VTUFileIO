#include "VTUFileManager.h"

#include <ptoKPart.h> 
#include <ftrFeatureList.h>

#include <basBasis.h>
#include <basNewModel.h>
#include <ptoKUtils.h>
#include <bmeMesh.h> 
#include <bmeElementClass.h>
#include <bmeElementClassList.h>

VTUFileManager::VTUFileManager() {
	mdb = NULL;
}

VTUFileManager::~VTUFileManager() {

}

/*
Read in mdb for extract nodes and elements
*/
int VTUFileManager::Init(basMdb* mdb, const QString& path) {
	this->mdb = mdb;
	this->VTKPath = path;

	if (mdb == NULL) 
		return ERRORTYPE_NOTEXIST;

	basModelMap modelsMap = mdb->GetModels();
	cowListString modelList = modelsMap.Keys();
	QVector<QString> model_parts;
	
	for (int i = 0; i < modelList.Length(); ++i) {
		QString modelname = modelList.Get(i);
		SAMmodels.append(modelname);
		model_parts = QVector<QString>(modelList.Length());
		const ptoKPartRepository& parts = ptoKConstGetPartRepos(*mdb, modelname);

		//TODO:Protection while parts not exist.

		for (int p = 1; p <= parts.Size(); ++p) {
			QString partname = parts.GetKey(p);
			model_parts.append(partname);
		}
		SAMparts.append(model_parts);
	}
	return 0;
};

/*
* Everything normal if return 0;
* If mdb not exist , return -1.
*/
int VTUFileManager::isReady() {
	if (mdb == NULL||
		SAMmodels.isEmpty()||
		SAMparts.isEmpty()
		) 
		return ERRORTYPE_NOTEXIST;
	return 0;
}