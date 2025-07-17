#include <VTUDataContainer.h>
#include <ErrorHandler.h>
#include <qstring.h>

VTUDataContainer::~VTUDataContainer() {
	for (int i = 0; i < elems.size(); ++i) {
		if (elems[i].dataSet != NULL) free(elems[i].dataSet);
	}
}

VTUDataContainer::VTUDataContainer() {

}

void VTUDataContainer::InsertNextPoint(float x, float y, float z) {
	points.push_back({ x,y,z });
}

int VTUDataContainer::InsertNextElement(const QString& label, int* dataSet) {
	if (dataSet == nullptr) {
		return ERRORTYPE_WRONGELEMENTDATA;
	}

	int type = VTUElementHandler::ConvertToVTKType(label);
	if (type == 0) {
		free(dataSet);
		return ERRORTYPE_WRONGELEMENTDATA;
	}

	Element e;
	e.type = type;
	e.dataSet = dataSet;
	elems.push_back(e);
	return 0;
}