#ifndef VTUCONTAINERWRITER
#define VTUCONTAINERWRITER

#include <MessageHandler.h>

class QString;
class ptoKPart;
class QFile;
class bmeElementClass;
class VTUDataContainer;

class VTUContainerWriter
{

public:
	VTUDataContainer* VTKData;
	
	VTUContainerWriter();
	~VTUContainerWriter();

	int GetVTKPart(ptoKPart part);
	VTUDataContainer* GetContainerPointer();
	int VTKExportODB();

	//virtual int WriteFormat();
	
};

#endif // !VTUCONTAINERWRITER