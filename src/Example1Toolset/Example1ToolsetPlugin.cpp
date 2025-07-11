#include <Example1ToolsetPlugin.h>
#include <Example1ToolsetGui.h>

#include <SAMApp.h>
#include <SAMMainWindow.h>
#include <SAMModuleGui.h>

Example1ToolsetPlugin::Example1ToolsetPlugin()
{

}

Example1ToolsetPlugin::~Example1ToolsetPlugin()
{

}

void Example1ToolsetPlugin::registerToolset()
{
	//todo
	SAMApp* app = SAMApp::getSAMApp();
	SAMMainWindow* mw = app->getSAMMainWindow();
	if (mw->getModule("Part"))
	{
		mw->getModule("Part")->registerToolset(&Example1ToolsetGui::Instance(), GUI_IN_MENUBAR | GUI_IN_TOOLBAR);
	}

}