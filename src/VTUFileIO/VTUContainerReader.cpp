#include "VTUContainerReader.h"

#include <ptoKUtils.h>
#include <ptoKPart.h> 
#include <smgSceneManagerRole.h>
#include <ftrFeatureList.h>
#include <visKSceneManager.h>
#include <ptsKMeshFactory.h>
#include <bmeMesh.h> 
#include <omeMesh.h>
#include <mesUtils.h>
#include <bmeElementClass.h>
#include <bmeElementClassList.h>

#include <basBasis.h>

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
int VTUContainerReader::ConstructNewPart(const QString& modelName, QString& partName, int& partID) {

	bdoTheory theory;
	theory.analysis = bdo_DeformableBody_Analysis;
	theory.space = bdo_3D_Space;
	theory.type = bdoType_MeshPart;

	basMdb mdb(basBasis::Instance()->Fetch());
	basModelMap& mdoelMap = mdb.GetModels();
	basNewModel& model = mdoelMap.Get(modelName);
	ptoKPartRepository& parts = dynamic_cast<ptoKPartRepository&>(model.GetPart());

	if (parts.IsMember(partName)) {
		for (int i = 1; i < 10; ++i) {
			if (parts.IsMember(partName + QString("-%1").arg(i))) continue;
			else 
			{
				partName = partName + QString("-%1").arg(i);
				break;
			}
		}
		return ERRORTYPE_NOTEXIST;
	}

	ptoKPart part(theory, partName);
	partID = parts.NextID();
	part.SetId(partID);

	parts.Insert(partName, part);
	basBasis::Instance()->Replace(mdb);

	/* Created a part */

	cowListInt nodeLabels;
	utiCoordCont3D nodeCoords;
	for (int i = 0; i < VTKData->points.size(); ++i) {
		nodeLabels.Append(i + 1);
		nodeCoords.Append(VTKData->points[i].x, VTKData->points[i].y, VTKData->points[i].z);
	}
	
	/* Created nodes and cells*/

	int numElemCls;
	bmeElementClass** classes = NULL;
	int err = ConstructElemClasses(&classes, &numElemCls);
	if (err) 
		return ERRORTYPE_WRONG_ELEMENT_DATA;

	ptoKPart part0 = parts.Get(partName);

	bmeMesh* mesh = new omeMesh(bdoDefaultInstId, VTKData->points.size(), nodeCoords, numElemCls, classes);
	mesh->GetNodeData().SetUserNodeLabels(nodeLabels);
	mesSetMesh(*(part0.GetFeatureList()), bdoDefaultInstId, mesh);

	/*for (int i = 0; i < numElemCls; ++i) {
		delete classes[i];
	}
	free(classes);*/

	return 0;
}

int VTUContainerReader::ConstructElemClasses(bmeElementClass*** classes, int* numCls) {
	QVector<bmeElementClass*> clsVec;
	QVector<int> connVec;
	QVector<int> labels;

	int elemNumPerCls = 0;
	QString nowType = "";
	int size = VTKData->elems.size();
	for (int i = 0; i < size; ++i) {
		QString type = VTUElementHandler::GetSAMTypeByVTKType(VTKData->elems[i].type);
		if (type == "") return ERRORTYPE_WRONG_ELEMENT_DATA;
		if (type != nowType || i == size -1) {
			if (nowType != "") {
				int* conn = (int*)malloc(connVec.size() * sizeof(int));
				int* usrlabel = (int*)malloc(elemNumPerCls * sizeof(int));
				VTUHeap.push_back(conn);
				VTUHeap.push_back(usrlabel);
				for (int j = 0; j < connVec.size(); ++j) conn[j] = connVec[j];
				for (int j = 0; j < elemNumPerCls; ++j) usrlabel[j] = labels[j];
				bmeElementClass* cls = bmeElementClass::ConstructObject(elemNumPerCls, nowType, conn);
				VTUFree.push_back(cls);
				cls->SetUserElementLabel(usrlabel);
				clsVec.push_back(cls);
				elemNumPerCls = 0;
				connVec.clear();
				labels.clear();
			}
			nowType = type;
		}
		if (VTUElementHandler::IsCube(VTKData->elems[i].type)) {
			connVec.push_back(VTKData->elems[i].dataSet[0]);
			connVec.push_back(VTKData->elems[i].dataSet[1]);
			connVec.push_back(VTKData->elems[i].dataSet[3]);
			connVec.push_back(VTKData->elems[i].dataSet[2]);
			connVec.push_back(VTKData->elems[i].dataSet[4]);
			connVec.push_back(VTKData->elems[i].dataSet[5]);
			connVec.push_back(VTKData->elems[i].dataSet[7]);
			connVec.push_back(VTKData->elems[i].dataSet[6]);
		}
		else {
			for (int k = 0; k < VTUElementHandler::GetArrayLengthByEnum(VTKData->elems[i].type); ++k)
			{
				connVec.push_back(VTKData->elems[i].dataSet[k]);
			}
		}
		labels.push_back(i + 1);
		++elemNumPerCls;
	}

	if (clsVec.size() > 0) {
		*classes = (bmeElementClass**)malloc(sizeof(bmeElementClass*) * clsVec.size());
		VTUHeap.push_back((int*)*classes);
		if (classes == NULL)
			return ERRORTYPE_MEMORY_ALLOC_FAILED;
		for (int k = 0; k < clsVec.size(); ++k) {
			(*classes)[k] = clsVec[k];
		}
		*numCls =  clsVec.size();
	}

	//TODO: DO those codes work?
	smgSceneManagerRole& role = smgSceneManagerRole::TheSceneManagerRole();
	role.UpdateDisplay(smg_Part, true);
	role.Refresh();
	return 0;
}

void VTUContainerReader::ReleaseMemory() {
	//先释放自由存储区new分配的内存
	for (int i = 0; i < VTUFree.size(); ++i) {
		if (VTUFree[i] != NULL)
			delete VTUFree[i];
	}
	//释放堆内存
	for (int i = 0; i < VTUHeap.size(); ++i) {
		if (VTUHeap[i] != NULL)
			free(VTUHeap[i]);
	}
	VTUFree.clear();
	VTUHeap.clear();
}

VTUDataContainer* VTUContainerReader::GetContainerPointer() {
	return VTKData;
}