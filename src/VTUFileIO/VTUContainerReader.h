#ifndef VTUCONTAINERREADER
#define VTUCONTAINERREADER

#include <ptoKPartRepository.h>
#include <MessageHandler.h>

class QString;
class bmeElementClass;
class VTUDataContainer;
class ptoKPart;

class VTUContainerReader
{

private:
	VTUDataContainer* VTKData;
	ptoKPart* targetPart;

public:
	VTUContainerReader(VTUDataContainer* container);
	~VTUContainerReader();
	
	int ConstructNewPart(ptoKPartRepository& parts, const QString& partName);
	int ConstructElemClasses(bmeElementClass**& classes);
	

	VTUDataContainer* GetContainerPointer();

	//virtual int WriteFormat();
	
};

#endif // !VTUCONTAINERREADER