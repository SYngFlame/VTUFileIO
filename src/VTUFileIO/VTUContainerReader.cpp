#include "VTUContainerReader.h"

#include <ptoKUtils.h>
#include <ptoKPart.h> 

#include <ftrFeatureList.h>
#include <visKSceneManager.h>
#include <ptsKMeshFactory.h>
#include <bmeMesh.h> 
#include <bmeElementClass.h>
#include <bmeElementClassList.h>

#include <VTUDataContainer.h>
#include <MessageHandler.h>

#include <qhash.h>

VTUContainerReader::VTUContainerReader(VTUDataContainer *container) {
	this->VTKData = container;
}

VTUContainerReader::~VTUContainerReader() {
}

/*
* Construct a new part and insert data from the container, then put the part under the model's part tree.
* Input the part tree and target part name.
*/
int VTUContainerReader::ConstructNewPart(ptoKPartRepository& parts, const QString& partName) {
	QString targetPartName;
	if (parts.IsMember(partName)) {
		for (int i = 0; i < 10; ++i) {
			if (parts.IsMember(partName + QString("-%1").arg(i))) continue;
			else targetPartName = partName + QString("-%1").arg(i);
		}
	}

	bdoTheory theory;
	theory.analysis = bdo_DeformableBody_Analysis;
	theory.space = bdo_3D_Space;
	theory.type = bdoType_MeshPart;

	ptoKPart* part = new ptoKPart(theory, targetPartName);
	if (part == NULL) return ERRORTYPE_MEMORY_ALLOC_FAILED;

	cowListInt nodeLabels;
	utiCoordCont3D nodeCoords;
	for (int i = 0; i < VTKData->points.size(); ++i) {
		nodeLabels.Append(i);
		nodeCoords.Append(VTKData->points[i].x, VTKData->points[i].y, VTKData->points[i].z);
	}
	
	int numElemCls;
	bmeElementClass** classes;
	numElemCls = ConstructElemClasses(classes);

	if (numElemCls == 0) return ERRORTYPE_WRONG_ELEMENT_DATA;
	
	if (ptsKMeshFactory::FromInputFile(*part, VTKData->points.size(), nodeLabels, nodeCoords, numElemCls, classes) ||
		parts.Insert(partName, *part))
		return ERRORTYPE_SAM_ACTION_FAILED;
	else
		return 0;

}

int VTUContainerReader::ConstructElemClasses(bmeElementClass**& classes) {
	QVector<bmeElementClass*> clsVec;
	QVector<int> connVec;

	int numPerCls = 0;
	QString nowType = "";
	for (int i = 0; i < VTKData->elems.size(); ++i) {
		QString type = VTUElementHandler::GetSAMTypeByVTKType(VTKData->elems[i].type);
		if (type == "") return ERRORTYPE_WRONG_ELEMENT_DATA;
		if (type != nowType) {
			if (nowType != "") {
				int* conn = (int*)malloc(connVec.size() * sizeof(int));
				for (int j = 0; i < connVec.size(); ++i) conn[i] = connVec[i];
				bmeElementClass* nowCls = new bmeElementClass(numPerCls, nowType, conn);
				clsVec.push_back(nowCls);
				connVec.clear();
			}
			nowType = type;
		}
		for (int k = 0; k < VTUElementHandler::GetArrayLengthByEnum(VTKData->elems[i].type); ++k) 
			connVec.push_back(VTKData->elems[i].dataSet[k]);
	}

	if (clsVec.size() != 0) {
		classes = (bmeElementClass**)malloc(sizeof(bmeElementClass*) * clsVec.size());
		for (int k = 0; k < clsVec.size(); ++k) {
			classes[k] = clsVec[k];
		}
	}
}

VTUDataContainer* VTUContainerReader::GetContainerPointer() {
	return VTKData;
}