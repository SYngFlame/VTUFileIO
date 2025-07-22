/* -*- mode: c++ -*- */
#ifndef VTUFileIOToolsetGui_h
#define VTUFileIOToolsetGui_h

//
// Includes
//

// Begin local includes

#include <SAMToolsetGui.h>

#include <mmgGRemoteModeInstaller.h>
#include <mmgGModeInstaller.h>
#include <mgnGModeFactory.h>
#include <omuPrimType.h>


class SAMFileDialog;
class VTUFileIOForm;
class basBasis;

//

class VTUFileIOToolsetGui : public SAMToolsetGui
{
    Q_OBJECT
public:

    // Constructor and destructor:
    VTUFileIOToolsetGui();
    ~VTUFileIOToolsetGui();
    // 添加公共方法供插件调用
    void importVTU();
    void exportVTU();

private:
    // Copy constructor and assignment operator
    VTUFileIOToolsetGui(const VTUFileIOToolsetGui&);

protected:
    /// Activates modes when switching into derived module.
    virtual void activate();

    /// Deactivates modes when switching out of derived module.
    virtual void deactivate();

    /// Creates the module's menu items.
    virtual void createMenuItems();

    /// Creates the module's toolbox.
    virtual void createToolboxItems();

    
private slots:
    void PrintMsg();

    void SaveDialog();
    void OnSave(const QString& path);

    void OpenDialog();
    void OnOpen(const QString& path);

    void onImport(const QString& path);
    void onExport(const QString& path);
private:
    SAMFileDialog* fileDialog = nullptr;
};

#endif