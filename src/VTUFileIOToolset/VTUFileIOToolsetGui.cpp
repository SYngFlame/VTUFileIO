#include <VTUFileIOToolsetGui.h>
#include <VTUFileIOForm.h>
#include <VTUFileIODb.h>

#include <rgnGRegionToolsetGui.h>
#include <SAMMenuPane.h>
#include <SAMMenuCommand.h>

#include <cmdKCommandDeliveryRole.h>
#include <omuArguments.h>
#include <omuMethodCall.h>
#include <omuPrimExpr.h>


VTUFileIOToolsetGui::VTUFileIOToolsetGui()
	: SAMToolsetGui("Test"),
	omiSingleton<VTUFileIOToolsetGui>()
{
	createMenuItems();
	createToolboxItems();
}

VTUFileIOToolsetGui::~VTUFileIOToolsetGui()
{

}

void VTUFileIOToolsetGui::activate()
{
	// todo
	SAMToolsetGui::activate();
}

void VTUFileIOToolsetGui::deactivate()
{
	// todo
	SAMToolsetGui::deactivate();
}

void VTUFileIOToolsetGui::createMenuItems()
{
	//todo
	SAMMenu* testMenu = new SAMMenu(this, tr("&VTK"));

	SAMMenuCommand* printCmd = new SAMMenuCommand(this, testMenu, tr("&PrintModelInfo"));
	testMenu->addAction(printCmd);
	connect(printCmd, SIGNAL(triggered(bool)), this, SLOT(PrintMsg()));
}

void VTUFileIOToolsetGui::createToolboxItems()
{
	// todo
}

void VTUFileIOToolsetGui::PrintMsg() {
	VTUFileIOForm* aVTUFileIOForm = new VTUFileIOForm(this);
	aVTUFileIOForm->onCmdActivate(this, 0, 0);
}