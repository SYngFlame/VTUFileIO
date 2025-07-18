#include <VTUDataContainer.h>
#include <ErrorHandler.h>
#include <qstring.h>
#include <shpShape.h>

VTUDataContainer::~VTUDataContainer() {
	for (int i = 0; i < elems.size(); ++i) {
		if (elems[i].dataSet != NULL) delete [] elems[i].dataSet;
	}
}

VTUDataContainer::VTUDataContainer() {
	elemVertices = 0;
}

void VTUDataContainer::InsertNextPoint(int index, float x, float y, float z) {
	points.push_back({ x,y,z });
	Index2PositionMap.insert(index, points.size() - 1);
}

int VTUDataContainer::InsertNextElement(VTUElementHandler::VTKType type, int* dataSet){
	Element e;
	if (!(e.type = type) || (e.dataSet = dataSet) == NULL)
		return ERRORTYPE_WRONGELEMENTDATA;
	if (type == VTUElementHandler::VTK_VOXEL) {
		int temp;
		temp = dataSet[2];
		dataSet[2] = dataSet[3];
		dataSet[3] = temp;
		temp = dataSet[6];
		dataSet[6] = dataSet[7];
		dataSet[7] = temp;
	}
	elems.push_back(e);
	elemVertices += VTUElementHandler::GetArrayLengthByEnum(e.type) + 1;

	return 0;
}