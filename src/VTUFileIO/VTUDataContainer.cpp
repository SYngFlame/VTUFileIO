#include <VTUDataContainer.h>
#include <MessageHandler.h>
#include <qstring.h>
#include <shpShape.h>

VTUDataContainer::~VTUDataContainer() {
	int loop = elems.size();
	for (int i = 0; i < loop; ++i) {
		{
			if (elems[i].dataSet != nullptr) free(elems[i].dataSet);
			elems[i].dataSet = nullptr;
		}
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
	if (!(e.type = type) || (e.dataSet = dataSet) == nullptr)
		return ERRORTYPE_WRONG_ELEMENT_DATA;
	elems.push_back(e);
	elemVertices += VTUElementHandler::GetArrayLengthByEnum(e.type) + 1;

	return 0;
}

void VTUDataContainer::CorrectSAMCubeData() {
	for (int i = 0; i < elems.size(); ++i) {
		if (VTUElementHandler::IsCube(elems[i].type)) {
			int* dataSet = elems[i].dataSet;
			int temp;
			temp = dataSet[2];
			dataSet[2] = dataSet[3];
			dataSet[3] = temp;
			temp = dataSet[6];
			dataSet[6] = dataSet[7];
			dataSet[7] = temp;
		}
	}
}