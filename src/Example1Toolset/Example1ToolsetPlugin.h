#ifndef Example1ToolsetPlugin_h
#define Example1ToolsetPlugin_h

#include <QtPlugin>
#include <SAMToolsetGuiInterface.h>



class Example1ToolsetPlugin : public QObject, SAMToolsetGuiInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID SAMToolsetGuiPlugin_iid)
	Q_INTERFACES(SAMToolsetGuiInterface)
public:
	Example1ToolsetPlugin();
	virtual ~Example1ToolsetPlugin();

public:
	virtual void registerToolset();
};


#endif
