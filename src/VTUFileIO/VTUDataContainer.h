#include <qvector.h>
#include <qmap.h>
#include <VTUElementHandler.h>

class shpShape;

struct Point {
	float x;
	float y;
	float z;
};
struct Element {
	VTUElementHandler::VTKType type;
	int* dataSet;
};

class QString;

class VTUDataContainer {
public:

	QVector<Point> points;
	QVector<Element> elems;
	QMap<int, int> Index2PositionMap;

	int elemVertices;

	void InsertNextPoint(int index, float x, float y, float z);
	int InsertNextElement(VTUElementHandler::VTKType type, int* dataSet);
	void CorrectSAMCubeData();

	VTUDataContainer();
	~VTUDataContainer();
};