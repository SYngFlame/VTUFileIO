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

int VTUDataContainer::InsertNextElement(const QString& label, int* dataSet){
	Element e;
	if (e.type = VTUElementHandler::ConvertToVTKType(label) || (e.dataSet = dataSet) == NULL)
		//TODO:ConvertToVTKType(const QString& label)
		return ERRORTYPE_WRONGELEMENTDATA;
	else elems.push_back(e);
	return 0;
}