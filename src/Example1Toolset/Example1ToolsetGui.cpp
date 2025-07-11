#include <Example1ToolsetGui.h>
#include <Example1Form.h>
#include <Example1Db.h>

#include <rgnGRegionToolsetGui.h>
#include <SAMMenuPane.h>
#include <SAMMenuCommand.h>


#include <cmdKCommandDeliveryRole.h>
#include <omuArguments.h>
#include <omuMethodCall.h>
#include <omuPrimExpr.h>



Example1ToolsetGui::Example1ToolsetGui()
	: SAMToolsetGui("Test"),
	omiSingleton<Example1ToolsetGui>()
{
	createMenuItems();
	createToolboxItems();
}

Example1ToolsetGui::~Example1ToolsetGui()
{

}

void Example1ToolsetGui::activate()
{
	// todo
	SAMToolsetGui::activate();
}

void Example1ToolsetGui::deactivate()
{
	// todo
	SAMToolsetGui::deactivate();
}

void Example1ToolsetGui::createMenuItems()
{
	//todo
	SAMMenu* testMenu = new SAMMenu(this, tr("&Curve"));

	SAMMenuCommand* example1Cmd = new SAMMenuCommand(this, testMenu, tr("&BezierCurve"));
	testMenu->addAction(example1Cmd);
	connect(example1Cmd, SIGNAL(triggered(bool)), this, SLOT(ExampleUi()));
}

void Example1ToolsetGui::createToolboxItems()
{
	// todo
}

void Example1ToolsetGui::ExampleUi() {
	Example1Form* aExample1Form = new Example1Form(this);
	aExample1Form->onCmdActivate(this, 0, 0);
}