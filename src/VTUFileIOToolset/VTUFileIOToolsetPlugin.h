#ifndef VTUFileIOToolsetPlugin_h
#define VTUFileIOToolsetPlugin_h

#include <QtPlugin>
#include <SAMToolsetGuiInterface.h>
#include <QMenu>
#include <QObject>

class VTUFileIOToolsetPlugin : public QObject, SAMToolsetGuiInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID SAMToolsetGuiPlugin_iid)
	Q_INTERFACES(SAMToolsetGuiInterface)
public:
	VTUFileIOToolsetPlugin();
	virtual ~VTUFileIOToolsetPlugin();

public:
	virtual void registerToolset();

private:
	// 辅助函数：在菜单中查找子菜单
	QMenu* findSubmenu(QMenu* parentMenu, const QString& name);
/*
private slots:
	void onImportVTU();
	void onExportVTU();
};
*/

#endif
