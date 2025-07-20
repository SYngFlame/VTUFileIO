#ifndef VTUCONTAINERREADER
#define VTUCONTAINERREADER

#include <ptoKPartRepository.h>
#include <MessageHandler.h>
#include <qvector.h>

class QString;
class bmeElementClass;
class VTUDataContainer;
class ptoKPart;

class VTUContainerReader
{

private:
	VTUDataContainer* VTKData;
	QVector<int*> VTUHeap;
	QVector<bmeElementClass*> VTUFree;

public:
	VTUContainerReader(VTUDataContainer* container);
	~VTUContainerReader();
	
	int ConstructNewPart(const QString& modelName, QString& partName, int& partID);
	int ConstructElemClasses(bmeElementClass*** classes, int* numCls);
	void ReleaseMemory();
	

	VTUDataContainer* GetContainerPointer();

	//virtual int WriteFormat();
	
};

#endif // !VTUCONTAINERREADER