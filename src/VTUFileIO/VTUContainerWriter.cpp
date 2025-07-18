#include "VTUContainerWriter.h"

#include <ptoKPart.h> 
#include <ftrFeatureList.h>
#include <visKSceneManager.h>
#include <VTUDataContainer.h>

#include <bmeMesh.h> 
#include <bmeElementClass.h>
#include <bmeElementClassList.h>
#include <shpShape.h>

#include <qfile.h>

VTUContainerWriter::VTUContainerWriter() {
	this->VTKData = new VTUDataContainer;
}

VTUContainerWriter::~VTUContainerWriter() {
	if(VTKData != NULL) delete(this->VTKData);
}

int VTUContainerWriter::GetVTKPart(const ptoKPart& part) {
	ftrFeatureList ftrlist = part.ConstGetFeatureList();
	if (!(ftrlist.MeshExists(bdoDefaultInstId)))
		return ERRORTYPE_NOTEXIST;

	bmeMesh* mesh = ftrlist.GetMesh(bdoDefaultInstId);
	if (!(mesh->NumNodes())) 
		return ERRORTYPE_WRONGNODEDATA;

	const bmeNodeData& nodeData = mesh->NodeData();
	utiCoordCont3D nodeContainer = nodeData.CoordContainer();
	cowListInt nodeList;
	nodeData.GetUserNodeLabels(nodeList);

	for (int n = 0; n < nodeList.Length(); ++n) {
		float x, y, z;
		nodeContainer.GetCoord(n, x, y, z);
		VTKData->InsertNextPoint(n, x, y, z);
	}

	int status = 0;
	const bmeElementData& elemData = mesh->ElementData();
	const bmeElementClassList& elemClasses = elemData.ConstGetClasses();
	int connectivityIndex = 0;
	for (int l = 0; l < elemClasses.Size(); ++l) {
		const bmeElementClass& elem = elemClasses.ConstGet(l);
		//TODO:Mutiple elements in a single class.Correct the visit function.
		const int* conn = elem.Connectivity();
		VTUElementHandler::VTKType type = VTUElementHandler::SimplifiedConvertor(elem.ElemTypeLabel(), elem.Shape()->NumGeometryDimensions());
		int length = VTUElementHandler::GetArrayLengthByEnum(type);
		for (int e = 0; e < elem.NumElements(); ++e) {
			int* dataSet = new int [length];
			if (dataSet == NULL) 
				return ERRORTYPE_MEMORYALLOCFAILED;
			
			if (conn == NULL) return ERRORTYPE_WRONGELEMENTDATA;
			for (int i = length * e; i < length * (e + 1); ++i) {
				dataSet[i % length] = VTKData->Index2PositionMap.value(conn[i]);
			}
			status |= VTKData->InsertNextElement(type, dataSet);
			
		}
	}

	return status;
}

VTUDataContainer* VTUContainerWriter::GetContainerPointer() {
	return VTKData;
}

int VTUContainerWriter::VTKExportODB() {
	return 0;
}