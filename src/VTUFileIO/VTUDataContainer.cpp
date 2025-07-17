#include <VTUDataContainer.h>
#include <ErrorHandler.h>
#include <qstring.h>

VTUDataContainer::~VTUDataContainer() {
	for (int i = 0; i < elems.size(); ++i) {
		if (elems[i].dataSet != NULL) free(elems[i].dataSet);
	}
}

VTUDataContainer::VTUDataContainer() {
	elemVertices = 0;
}

void VTUDataContainer::InsertNextPoint(int index, float x, float y, float z) {
	points.push_back({ x,y,z });
	Index2PositionMap.insert(index ,points.size() - 1);
}

int VTUDataContainer::InsertNextElement(const QString& label, int* dataSet){
	Element e;
	if (e.type = VTUElementHandler::ConvertToVTKType(label) || (e.dataSet = dataSet) == NULL)
		//TODO:ConvertToVTKType(const QString& label)
		return ERRORTYPE_WRONGELEMENTDATA;
	else elems.push_back(e);
	elemVertices += VTUElementHandler::GetArrayLength(e.type);
	return 0;
}