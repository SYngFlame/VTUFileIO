#include <VTUFileIOToolsetPlugin.h>
#include <VTUFileIOToolsetGui.h>

#include <SAMApp.h>
#include <SAMMainWindow.h>
#include <SAMModuleGui.h>

VTUFileIOToolsetPlugin::VTUFileIOToolsetPlugin()
{

}

VTUFileIOToolsetPlugin::~VTUFileIOToolsetPlugin()
{

}

void VTUFileIOToolsetPlugin::registerToolset()
{
	//todo
	SAMApp* app = SAMApp::getSAMApp();
	SAMMainWindow* mw = app->getSAMMainWindow();
	if (mw->getModule("Part"))
	{
		mw->getModule("Part")->registerToolset(new VTUFileIOToolsetGui, GUI_IN_MENUBAR | GUI_IN_TOOLBAR);
	}

}