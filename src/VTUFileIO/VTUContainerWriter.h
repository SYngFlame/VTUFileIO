#ifndef VTUCONTAINERWRITER
#define VTUCONTAINERWRITER

#include <MessageHandler.h>

class QString;
class ptoKPart;
class QFile;
class bmeMesh;
class bmeElementClass;
class VTUDataContainer;
class gslMatrix;

class VTUContainerWriter
{

public:
	VTUDataContainer* VTKData;
	
	VTUContainerWriter();
	~VTUContainerWriter();

	int ReadVTKPart(ptoKPart part);
	int ReadVTKMesh(const bmeMesh* mesh, bool transform = false, gslMatrix* transMatrix = nullptr);
	VTUDataContainer* GetContainerPointer();
	int VTKExportODB();

	//virtual int WriteFormat();
	
};

#endif // !VTUCONTAINERWRITER