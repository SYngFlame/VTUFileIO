#include <VTUFileIOToolsetGui.h>
#include <VTUFileIOForm.h>
#include <VTUFileIODb.h>
#include <VTUFileIOCommand.h>

#include <rgnGRegionToolsetGui.h>
#include <SAMMenuPane.h>
#include <SAMMenuCommand.h>

#include <cmdGCommandDeliveryRole.h>
#include <SAMFileDialog.h>

#include <ubiFileToolsetGui.h>


VTUFileIOToolsetGui::VTUFileIOToolsetGui()
	: SAMToolsetGui("Test")
{
	createMenuItems();
	createToolboxItems();
	VTUFileIOCommand::CommitLoad();

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
	SAMMenu* testMenu = new SAMMenu(this, tr("&VTKTest"));
	SAMMenuCommand* printCmd = new SAMMenuCommand(this, testMenu, tr("&PrintModelInfo"));
	testMenu->addAction(printCmd);

	SAMMenu* fileMenu = ubiFileToolsetGui::Instance().findChild<SAMMenu*>("fileMenu", Qt::FindChildrenRecursively);
	if (fileMenu == NULL) {
		qDebug("Menu not found.");
		return;
	}

	SAMMenu* ExportMenu = fileMenu->findChild<SAMMenu*>("Export", Qt::FindDirectChildrenOnly);
	SAMMenu* ImportMenu = fileMenu->findChild<SAMMenu*>("Import", Qt::FindDirectChildrenOnly);

	SAMMenuCommand* SaveCmd = new SAMMenuCommand(this, fileMenu, tr("&VTU/VTK Legacy.."));
	SAMMenuCommand* ImportCmd = new SAMMenuCommand(this, fileMenu, tr("&VTK part"));

	
	fileMenu->addAction(SaveCmd);
	fileMenu->addAction(ImportCmd);
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
	//fileDialog->setNameFilters(QStringList("VTK XML Unstructured Grid(*.vtu)"));
	fileDialog->setNameFilters(QStringList("VTK Legacy(*.vtk)"));

	QObject::connect(fileDialog, SIGNAL(onFileSelected(const QString&)), this, SLOT(OnSave(const QString&)));
	fileDialog->show();
}

void VTUFileIOToolsetGui::OnSave(const QString& path) {
	VTUFileIOCommand::CommitSave(path);
}