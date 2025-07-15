#include <VTUFileIOToolsetGui.h>
#include <VTUFileIOForm.h>
#include <VTUFileIODb.h>
#include <VTUFileIOCommand.h>

#include <rgnGRegionToolsetGui.h>
#include <SAMMenuPane.h>
#include <SAMMenuCommand.h>

#include <SAMFileDialog.h>

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
	VTUFileIOCommand::CommitPrint();
}

void VTUFileIOToolsetGui::SaveDialog() {
	
	SAMFileDialog* fileDialog = new SAMFileDialog("Select existing directory for VTK files", 0);
	fileDialog->setFileMode(QFileDialog::AnyFile);
	fileDialog->setAcceptMode(QFileDialog::AcceptSave);
	fileDialog->setNameFilters(QStringList("VTK Legacy"));

	QObject::connect(fileDialog, SIGNAL(SAMFileDialog::onFileSelected), NULL, SLOT(VTUFileIOCommand::CommitSave));
	fileDialog->show();
}