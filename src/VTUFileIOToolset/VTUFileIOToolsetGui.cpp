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
	SAMMenu* testMenu = new SAMMenu(this, tr("&Curve"));

	SAMMenuCommand* example1Cmd = new SAMMenuCommand(this, testMenu, tr("&BezierCurve"));
	testMenu->addAction(example1Cmd);
	connect(example1Cmd, SIGNAL(triggered(bool)), this, SLOT(ExampleUi()));
}

void VTUFileIOToolsetGui::createToolboxItems()
{
	// todo
}

void VTUFileIOToolsetGui::ExampleUi() {
	VTUFileIOForm* aVTUFileIOForm = new VTUFileIOForm(this);
	aVTUFileIOForm->onCmdActivate(this, 0, 0);
}