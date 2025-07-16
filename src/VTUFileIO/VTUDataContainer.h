#include <qvector.h>
#include <VTUElementHandler.h>
struct Point {
	float x;
	float y;
	float z;
};
struct Element {
	int type;
	int* dataSet;
};

class QString;

class VTUDataContainer {
public:

	QVector<Point> points;
	QVector<Element> elems;

	void VTUDataContainer::InsertNextPoint(float x, float y, float z);
	int VTUDataContainer::InsertNextElement(const QString& label, int* dataSet);

	VTUDataContainer();
	~VTUDataContainer();
};