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

int VTUFileWriter::VTKExportPart(const ptoKPart& part) {
	ftrFeatureList ftrlist = part.ConstGetFeatureList();
	if (!(ftrlist.MeshExists(bdoDefaultInstId)))
		return ERRORTYPE_NOTEXIST;

	bmeMesh* mesh = ftrlist.GetMesh(bdoDefaultInstId);
	if (!(mesh->NumNodes())) return ERRORTYPE_NOTEXIST;

	const bmeNodeData& nodeData = mesh->NodeData();
	utiCoordCont3D nodeContainer = nodeData.CoordContainer();
	cowListInt nodeList;
	
	for (int n = 0; n < nodeList.Length(); ++n) {
		float x, y, z;
		nodeContainer.GetCoord(n, x, y, z);
		points->InsertNextPoint(x, y, z);
	}

	const bmeElementData& elemData = mesh->ElementData();
	const bmeElementClassList& elemClasses = elemData.ConstGetClasses();

	int connectivityIndex = 0;
	int* typeList = (int*)malloc(elemClasses.Size() * sizeof(int));
	if (typeList == NULL) return ERRORTYPE_NOTEXIST;

	for (int l = 0; l < elemClasses.Size(); ++l) {
		const bmeElementClass& elemclass = elemClasses.ConstGet(l);
		int index = elemclass.ClassIndex();
		switch(matchElemType(elemclass.ElemTypeLabel())) {
			case 0x01: {
				vtkNew<vtkLine> line;
				line->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[0]));
				line->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[1]));
				cellArray->InsertNextCell(line);
				typeList[l] = VTK_LINE;
				break;
			}
			case 0x03: {
				vtkNew<vtkTriangle> triangle;
				triangle->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[0]));
				triangle->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[1]));
				triangle->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[2]));
				cellArray->InsertNextCell(triangle);
				typeList[l] = VTK_TRIANGLE;
				break;
			}
			case 0x04: {
				vtkNew<vtkQuad> Quad;
				Quad->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[0]));
				Quad->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[1]));
				Quad->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[2]));
				Quad->GetPointIds()->SetId(connectivityIndex++, nodeData.GetMeshNodeIndex(elemclass.Connectivity()[3]));
				cellArray->InsertNextCell(Quad);
				typeList[l] = VTK_QUAD;
				break;
			}
			default:{
				break;
			}
		}
		
	}

	return 0;
}

int VTUFileWriter::matchElemType(const QString& typeLabel) {
	if (typeLabel == "B31") return 0x01;
	if (typeLabel == "T3D2") return 0x01;
	if (typeLabel == "S3") return 0x03;
	if (typeLabel == "S4R") return 0x04;
}