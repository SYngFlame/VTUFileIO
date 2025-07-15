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
#include <SAMFileDialog.h>
#include <SAMBoolKeyword.h>
#include <cmdGCommandDeliveryRole.h>


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
	SAMMenuCommand* SaveCmd = new SAMMenuCommand(this, testMenu, tr("&Save as VTK"));
	testMenu->addAction(SaveCmd);
	connect(printCmd, SIGNAL(triggered(bool)), this, SLOT(PrintMsg()));
	connect(SaveCmd, SIGNAL(triggered(bool)), this, SLOT(SaveDialog()));
}

void VTUFileIOToolsetGui::createToolboxItems()
{
	// todo
}

void VTUFileIOToolsetGui::PrintMsg() {
	VTUFileIOForm* aVTUFileIOForm = new VTUFileIOForm(this);
	aVTUFileIOForm->onCmdActivate(this, 0, 0);
}

void VTUFileIOToolsetGui::SaveDialog() {
	QString path;
	SAMFileDialog* fileDialog = new SAMFileDialog(this, "Select existing directory for VTK files", 0);
	fileDialog->selectFile(path);

	omuArguments args;
	args.Put(path);

	cmdGCommandDeliveryRole::Instance().SendCommand("import VTUFileIO");
	omuMethodCall mc("mdb.models['Model-1'].parts['Part-1']", "initManager", args);
	QString cmd;
	cmd.append(mc);
	cmdGCommandDeliveryRole::Instance().SendCommand(cmd);
	cmdGCommandDeliveryRole::Instance().SendCommand("session.viewports['Viewport: 1'].view.fitView()");
}