#include <VTUFileIOToolsetPlugin.h>
#include <VTUFileIOToolsetGui.h>

#include <SAMApp.h>
#include <SAMMainWindow.h>
#include <SAMModuleGui.h>
#include <qdebug.h>
#include <ubiFileToolsetGui.h>
#include <qmenubar.h>
#include <qmenu.h>


#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
VTUFileIOToolsetPlugin::VTUFileIOToolsetPlugin()
{

}

VTUFileIOToolsetPlugin::~VTUFileIOToolsetPlugin()
{

}

void VTUFileIOToolsetPlugin::registerToolset()
{
    SAMApp* app = SAMApp::getSAMApp();
    SAMMainWindow* mw = app->getSAMMainWindow();
    if (!mw) {
        qDebug() << "Main window not found";
        return;
    }

    // ��ȡ���˵���
    QMenuBar* menuBar = mw->getMenubar();
    if (!menuBar) {
        qDebug() << "Menu bar not found";
        return;
    }

    // ���� File �˵�
    QMenu* fileMenu = nullptr;
    for (QAction* action : menuBar->actions()) {
        if (action->text().contains("File", Qt::CaseInsensitive)) {
            fileMenu = action->menu();
            break;
        }
    }

    if (!fileMenu) {
        qDebug() << "File menu not found";
        return;
    }

    // ���� Import �Ӳ˵�
    QMenu* importMenu = findSubmenu(fileMenu, "Import");
    if (importMenu) {
        // �� Import �˵������ VTU ����ѡ��
        QAction* importVTUAction = new QAction("VTU", importMenu);
        importMenu->addAction(importVTUAction);
        qDebug() << "Added VTU import option to Import menu";
    }
    else {
        qDebug() << "Import submenu not found";
    }

    // ���� Export �Ӳ˵�
    QMenu* exportMenu = findSubmenu(fileMenu, "Export");
    if (exportMenu) {
        // �� Export �˵������ VTU ����ѡ��
        QAction* exportVTUAction = new QAction("VTU", exportMenu);
        exportMenu->addAction(exportVTUAction);
        qDebug() << "Added VTU export option to Export menu";
    }
    else {
        qDebug() << "Export submenu not found";
    }

    // ע��ģ�鹤�߼��������Ҫ��
    if (mw->getModule("Part")) {
        mw->getModule("Part")->registerToolset(
            new VTUFileIOToolsetGui(),
            GUI_IN_TOOLBAR  // ֻ�ڹ�������ʾ�����ڲ˵���
        );
    }

    if (mw->getModule("Visualization")) {
        mw->getModule("Visualization")->registerToolset(
            new VTUFileIOToolsetGui(),
            GUI_IN_TOOLBAR  // ֻ�ڹ�������ʾ�����ڲ˵���
        );
    }
}

// �����������ڸ��˵��в����Ӳ˵�
QMenu* VTUFileIOToolsetPlugin::findSubmenu(QMenu* parentMenu, const QString& name)
{
    if (!parentMenu) return nullptr;

    // �������˵������ж���
    for (QAction* action : parentMenu->actions()) {
        // ��鶯���Ƿ����Ӳ˵�
        if (action->menu() && action->text().contains(name, Qt::CaseInsensitive)) {
            return action->menu();
        }
    }

    return nullptr;
}

/*
void VTUFileIOToolsetPlugin::registerToolset()
{
    //todo
    SAMApp* app = SAMApp::getSAMApp();
    SAMMainWindow* mw = app->getSAMMainWindow();
    if (mw->getModule("Part"))
    {
        mw->getModule("Part")->registerToolset(new VTUFileIOToolsetGui, GUI_IN_MENUBAR | GUI_IN_TOOLBAR);
    }
    auto n = mw->getNumModules();
    qDebug() << " mw->getNumModules();: menu"<< n;
}
*/
/*
void VTUFileIOToolsetPlugin::registerToolset()
{

    SAMApp* app = SAMApp::getSAMApp();
    SAMMainWindow* mw = app->getSAMMainWindow();
    if (!mw) return;

    SAMModuleGui* partModule = mw->getModule("Part");
    if (partModule) {
        // �����Զ��幤�߼���ע�� 
        partModule->registerToolset(new VTUFileIOToolsetGui, GUI_IN_MENUBAR | GUI_IN_TOOLBAR);

        // ����File�˵���Ӱ�ť
        toolset->initFileMenu();
    }

    // ��ȡ File ���߼��ĵ���ʵ��
    ubiFileToolsetGui& fileToolset = ubiFileToolsetGui::Instance();
    SAMMenu* fileMenu = nullptr;

    foreach(QAction * action, mw->menuBar()->actions()) {
        if (action->text() == "File") {
            fileMenu = qobject_cast<SAMMenu*>(action->menu());
            break;
        }
    }

    // �����µ��Ӳ˵� "VTU File"
    QMenu* vtuSubmenu = new QMenu("VTU File", fileMenu);

    // �����ļ�������ض���
    QAction* importAction = new QAction("Import VTU", vtuSubmenu);
    QAction* exportAction = new QAction("Export VTU", vtuSubmenu);

    // ��ӵ��Ӳ˵�
    vtuSubmenu->addAction(importAction);
    vtuSubmenu->addAction(exportAction);

    // �� File �˵�����ӷָ������Ӳ˵�
    fileMenu->addSeparator();
    fileMenu->addMenu(vtuSubmenu);

    qDebug() << "Added VTU File submenu to File menu";

    // ��ѡ��ע������ģ��Ĺ��߼�
    SAMApp* app = SAMApp::getSAMApp();
    SAMMainWindow* mw = app->getSAMMainWindow();

    if (mw->getModule("Visualization")) {
        mw->getModule("Visualization")->registerToolset(
            new VTUFileIOToolsetGui(),
            GUI_IN_MENUBAR | GUI_IN_TOOLBAR
        );
    }
}
*/
/*
void VTUFileIOToolsetPlugin::registerToolset()
{
	//todo
	SAMApp* app = SAMApp::getSAMApp();
	SAMMainWindow* mw = app->getSAMMainWindow();

	SAMModuleGui* partModule = mw->getModule("Part");

	//partModule->registerToolset(new VTUFileIOToolsetGui, GUI_IN_MENUBAR | GUI_IN_TOOLBAR);

	QObjectList allToolsets = partModule->getToolsets();
	auto FToolSet = allToolsets[0];

	FToolSetGUI = 
	SAMToolsetGui* i_getToolset(
		const QString & name	    ///< Name of toolset to be retrieved.
	) const;
}
*/

/*
void VTUFileIOToolsetPlugin::registerToolset()
{
    SAMApp* app = SAMApp::getSAMApp();
    SAMMainWindow* mw = app->getSAMMainWindow();
    if (!mw) return;

    SAMModuleGui* partModule = mw->getModule("Part");
    if (!partModule) {
        qDebug() << "Part module not found";
        return;
    }

    // ע���Զ��幤�߼�
    partModule->registerToolset(new VTUFileIOToolsetGui,
        GUI_IN_MENUBAR | GUI_IN_TOOLBAR);

    // ��ȡ���й��߼����������
    QObjectList allToolsets = partModule->getToolsets();
    qDebug() << "Total toolsets in Part module:" << allToolsets.size();

    foreach(QObject * toolObj, allToolsets) {
        // ת��ΪSAMToolsetGuiָ�루��ȫת����
        SAMToolsetGui* toolset = qobject_cast<SAMToolsetGui*>(toolObj);
        if (toolset) {
            qDebug() << "Toolset name:" << toolset->getToolsetName();
        }
        else {
            qDebug() << "Unknown toolset type";
        }
    }

    // ����ѡ��ͨ�����ƻ�ȡ�ض����߼�
    SAMToolsetGui* targetToolset = partModule->i_getToolset("VTUFileIOToolset");
    if (targetToolset) {
        qDebug() << "Found target toolset:" << targetToolset->getToolsetName();
    }
}
*/