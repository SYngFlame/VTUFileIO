#include "VTUContainerWriter.h"

#include <ptoKPart.h> 
#include <ftrFeatureList.h>
#include <visKSceneManager.h>
#include <VTUDataContainer.h>

#include <gslVector.h>

#include <bmeMesh.h> 
#include <bmeElementClass.h>
#include <bmeElementClassList.h>
#include <shpShape.h>

#include <qfile.h>

VTUContainerWriter::VTUContainerWriter() {
	this->VTKData = new VTUDataContainer;
}

VTUContainerWriter::~VTUContainerWriter() {

}

int VTUContainerWriter::ReadVTKPart(ptoKPart part) {
	ftrFeatureList* ftrlist = part.GetFeatureList();
	if (!(ftrlist->MeshExists(bdoDefaultInstId)))
		return ERRORTYPE_NOTEXIST;

	return ReadVTKMesh(ftrlist->ConstGetMesh(bdoDefaultInstId));
}
int VTUContainerWriter::ReadVTKMesh(const bmeMesh* mesh, bool transform, gslMatrix* transMatrix) {
	if (!(mesh->NumNodes()))
		return ERRORTYPE_WRONG_NODE_DATA;

	const bmeNodeData& nodeData = mesh->NodeData();
	utiCoordCont3D nodeContainer = nodeData.CoordContainer();
	cowListInt nodeList;
	nodeData.GetUserNodeLabels(nodeList);
	
	if (transform)
	{
		gslVector translation(0, 0, 0);
		gslPoint rotateBase(0, 0, 0);
		gslVector dir(0, 0, 0);
		double x(0), y(0), z(0), radian(0);
		transMatrix->GetTranslation(translation);
		transMatrix->GetAxisRotation(rotateBase, dir, radian);
		double c = cos(radian);
		double s = sin(radian);
		for (int n = 0; n < nodeList.Length(); ++n) {
			float x, y, z;
			nodeContainer.GetCoord(n, x, y, z);

			gslPoint origin(x, y, z);
			origin = origin + translation;
			gslVector p = origin - rotateBase;

			gslVector cross = dir.CrossProduct(p);
			double dot = dir.DotProduct(p);
			origin = rotateBase + p * c + cross * s + (dir)*dot * (1 - c);
			VTKData->InsertNextPoint(n, origin.GetX(), origin.GetY(), origin.GetZ());
		}
	}
	else
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
			int* dataSet = (int*)malloc(length * sizeof(int));
			if (dataSet == nullptr)
				return ERRORTYPE_MEMORY_ALLOC_FAILED;

			if (conn == nullptr) return ERRORTYPE_WRONG_ELEMENT_DATA;
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