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

    // 获取主菜单栏
    QMenuBar* menuBar = mw->getMenubar();
    if (!menuBar) {
        qDebug() << "Menu bar not found";
        return;
    }

    // 查找 File 菜单
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

    // 查找 Import 子菜单
    QMenu* importMenu = findSubmenu(fileMenu, "Import");
    if (importMenu) {
        // 在 Import 菜单中添加 VTU 导入选项
        QAction* importVTUAction = new QAction("VTU", importMenu);
        importMenu->addAction(importVTUAction);
        qDebug() << "Added VTU import option to Import menu";
    }
    else {
        qDebug() << "Import submenu not found";
    }

    // 查找 Export 子菜单
    QMenu* exportMenu = findSubmenu(fileMenu, "Export");
    if (exportMenu) {
        // 在 Export 菜单中添加 VTU 导出选项
        QAction* exportVTUAction = new QAction("VTU", exportMenu);
        exportMenu->addAction(exportVTUAction);
        qDebug() << "Added VTU export option to Export menu";
    }
    else {
        qDebug() << "Export submenu not found";
    }

    // 注册模块工具集（如果需要）
    if (mw->getModule("Part")) {
        mw->getModule("Part")->registerToolset(
            new VTUFileIOToolsetGui(),
            GUI_IN_TOOLBAR  // 只在工具栏显示，不在菜单栏
        );
    }

    if (mw->getModule("Visualization")) {
        mw->getModule("Visualization")->registerToolset(
            new VTUFileIOToolsetGui(),
            GUI_IN_TOOLBAR  // 只在工具栏显示，不在菜单栏
        );
    }
}

// 辅助函数：在父菜单中查找子菜单
QMenu* VTUFileIOToolsetPlugin::findSubmenu(QMenu* parentMenu, const QString& name)
{
    if (!parentMenu) return nullptr;

    // 遍历父菜单的所有动作
    for (QAction* action : parentMenu->actions()) {
        // 检查动作是否有子菜单
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
        // 创建自定义工具集并注册 
        partModule->registerToolset(new VTUFileIOToolsetGui, GUI_IN_MENUBAR | GUI_IN_TOOLBAR);

        // 触发File菜单添加按钮
        toolset->initFileMenu();
    }

    // 获取 File 工具集的单例实例
    ubiFileToolsetGui& fileToolset = ubiFileToolsetGui::Instance();
    SAMMenu* fileMenu = nullptr;

    foreach(QAction * action, mw->menuBar()->actions()) {
        if (action->text() == "File") {
            fileMenu = qobject_cast<SAMMenu*>(action->menu());
            break;
        }
    }

    // 创建新的子菜单 "VTU File"
    QMenu* vtuSubmenu = new QMenu("VTU File", fileMenu);

    // 创建文件操作相关动作
    QAction* importAction = new QAction("Import VTU", vtuSubmenu);
    QAction* exportAction = new QAction("Export VTU", vtuSubmenu);

    // 添加到子菜单
    vtuSubmenu->addAction(importAction);
    vtuSubmenu->addAction(exportAction);

    // 在 File 菜单中添加分隔符和子菜单
    fileMenu->addSeparator();
    fileMenu->addMenu(vtuSubmenu);

    qDebug() << "Added VTU File submenu to File menu";

    // 可选：注册其他模块的工具集
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

    // 注册自定义工具集
    partModule->registerToolset(new VTUFileIOToolsetGui,
        GUI_IN_MENUBAR | GUI_IN_TOOLBAR);

    // 获取所有工具集并输出名称
    QObjectList allToolsets = partModule->getToolsets();
    qDebug() << "Total toolsets in Part module:" << allToolsets.size();

    foreach(QObject * toolObj, allToolsets) {
        // 转换为SAMToolsetGui指针（安全转换）
        SAMToolsetGui* toolset = qobject_cast<SAMToolsetGui*>(toolObj);
        if (toolset) {
            qDebug() << "Toolset name:" << toolset->getToolsetName();
        }
        else {
            qDebug() << "Unknown toolset type";
        }
    }

    // （可选）通过名称获取特定工具集
    SAMToolsetGui* targetToolset = partModule->i_getToolset("VTUFileIOToolset");
    if (targetToolset) {
        qDebug() << "Found target toolset:" << targetToolset->getToolsetName();
    }
}
*/