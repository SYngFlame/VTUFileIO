#include "VTUFileWriter.h"

#include <ptoKPart.h> 
#include <ftrFeatureList.h>
#include <visKSceneManager.h>

#include <bmeMesh.h> 
#include <bmeElementClass.h>
#include <bmeElementClassList.h>

#include <qfile.h>

VTUFileWriter::VTUFileWriter() {
	
}

VTUFileWriter::~VTUFileWriter() {

}

VTUFileWriter::VTUFileWriter(QFile* file) : file(file){}

int VTUFileWriter::GetVTKPart(const ptoKPart& part) {
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
		VTKData.InsertNextPoint(x, y, z);
	}

	int status = 0;
	const bmeElementData& elemData = mesh->ElementData();
	const bmeElementClassList& elemClasses = elemData.ConstGetClasses();
	int connectivityIndex = 0;
	for (int l = 0; l < elemClasses.Size(); ++l) {
		const bmeElementClass& elem = elemClasses.ConstGet(l);
		//TODO:Mutiple elements in a single class.Correct the visit function.

		int length = VTUElementHandler::GetArrayLength(elem.ElemTypeLabel());
		for (int e = 0; e < elem.NumElements(); ++e) {
			int* dataSet = (int*)malloc(length * sizeof(int));
			if (dataSet == NULL) 
				return ERRORTYPE_MEMORYALLOCFAILED;
			const int* conn = elem.Connectivity();
			for (int i = length * e; i < length * (e + 1); ++i) {
				dataSet[i] = nodeData.GetMeshNodeIndex(conn[i]);
			}
			status &= VTKData.InsertNextElement(elem.ElemTypeLabel(), dataSet);
		}
	}

	return status;
}

int VTUFileWriter::VTKExportODB() {
	return 0;
}