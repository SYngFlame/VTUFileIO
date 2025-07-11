#ifndef VTUFileIOToolsetPlugin_h
#define VTUFileIOToolsetPlugin_h

#include <QtPlugin>
#include <SAMToolsetGuiInterface.h>



class VTUFileIOToolsetPlugin : public QObject, SAMToolsetGuiInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID SAMToolsetGuiPlugin_iid)
	Q_INTERFACES(SAMToolsetGuiInterface)
public:
	VTUFileIOToolsetPlugin();
	virtual ~VTUFileIOToolsetPlugin();

public:
	virtual void registerToolset();
};


#endif
