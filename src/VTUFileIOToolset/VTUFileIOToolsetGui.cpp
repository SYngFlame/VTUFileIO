#include <VTUFileIOToolsetGui.h>
#include <VTUFileIOForm.h>
#include <VTUFileIODb.h>
#include <VTUFileIOCommand.h>

#include <SAMApp.h>
#include <SAMMenuPane.h>
#include <SAMMainWindow.h>
#include <qmenubar.h>
#include <SAMMenuCommand.h>
#include <SAMMainWindow.h>

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
	//SAMMenuCommand* printCmd = new SAMMenuCommand(this, testMenu, tr("&PrintModelInfo"));
	//testMenu->addAction(printCmd);
	//connect(printCmd, SIGNAL(triggered(bool)), this, SLOT(PrintMsg()));

	//auto fileMenu = ubiFileToolsetGui::Instance();

	//SAMMenu* fileMenu = new SAMMenu(this, tr("&VTK"));
	
	auto app = SAMApp::getSAMApp();
	auto mw = app->getSAMMainWindow();
	auto menuBar = mw->getMenubar();
	auto childs = menuBar->actions();

	SAMMenu* fileMenu = NULL;
	SAMMenu* importMenu = NULL;
	SAMMenu* exportMenu = NULL;

	for (QAction* action : menuBar->actions()) {
		if (action->text().contains("File", Qt::CaseInsensitive)) {
			fileMenu = (SAMMenu*)action->menu();
			break;
		}
	}
	if (fileMenu == NULL) return;
	for (QAction* action : fileMenu->actions()) {
		if (action->text().contains("Import", Qt::CaseInsensitive)) {
			importMenu = (SAMMenu*)action->menu();
			qDebug() << "VTUFileIO: Import Menu detected.";
		}
		if (action->text().contains("Export", Qt::CaseInsensitive)) {
			exportMenu = (SAMMenu*)action->menu();
			qDebug() << "VTUFileIO: Export Menu detected.";
		}
	}
	if (exportMenu == NULL) return;
	if (importMenu == NULL) return;

	SAMMenuCommand* SaveVTKCmd = new SAMMenuCommand(this, exportMenu, tr("&VTK Legacy.."));
	exportMenu->addAction(SaveVTKCmd);
	qDebug() << "VTUFileIO: Export Menu injected.";

	//SAMMenuCommand* SaveCmd = new SAMMenuCommand(this, fileMenu, tr("&VTU.."));
	//fileMenu->addAction(SaveVTUCmd);

	SAMMenuCommand* ImportCmd = new SAMMenuCommand(this, importMenu, tr("&Import VTK Part"));
	importMenu->addAction(ImportCmd);
	qDebug() << "VTUFileIO: Import Menu injected.";

	connect(SaveVTKCmd, SIGNAL(triggered(bool)), this, SLOT(SaveDialog()));
	connect(ImportCmd, SIGNAL(triggered(bool)), this, SLOT(OpenDialog()));
}

void VTUFileIOToolsetGui::createToolboxItems()
{
	// todo
}

void VTUFileIOToolsetGui::PrintMsg() {
	VTUFileIOCommand::CommitPrint();
}

void VTUFileIOToolsetGui::SaveDialog() {
	
	fileDialog = new SAMFileDialog("Select existing directory for VTK files", 0);
	fileDialog->setFileMode(QFileDialog::AnyFile);
	fileDialog->setAcceptMode(QFileDialog::AcceptSave);
	//fileDialog->setNameFilters(QStringList("VTK XML Unstructured Grid(*.vtu)"));
	fileDialog->setNameFilters(QStringList("VTK Legacy(*.vtk)"));

	QObject::connect(fileDialog, SIGNAL(onFileSelected(const QString&)), this, SLOT(OnSave(const QString&)));
	fileDialog->show();
}

void VTUFileIOToolsetGui::OnSave(const QString& path) {
	VTUFileIOCommand::CommitSave(path);
	//delete fileDialog;
	fileDialog = NULL;
}

void VTUFileIOToolsetGui::OpenDialog() {

	fileDialog = new SAMFileDialog("Select existing directory for VTK files", 0);
	fileDialog->setFileMode(QFileDialog::AnyFile);
	fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
	//fileDialog->setNameFilters(QStringList("VTK XML Unstructured Grid(*.vtu)"));
	fileDialog->setNameFilters(QStringList("VTK Legacy(*.vtk)"));

	QObject::connect(fileDialog, SIGNAL(onFileSelected(const QString&)), this, SLOT(OnOpen(const QString&)));
	fileDialog->show();
}

void VTUFileIOToolsetGui::OnOpen(const QString& path) {
	VTUFileIOCommand::CommitOpen(path);
	// TODO: Whether to delete fileDialog?
	// delete fileDialog;
	fileDialog = NULL;
}