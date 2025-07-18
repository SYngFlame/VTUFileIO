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



class VTUFileIOForm;
class basBasis;

//
// Class definition
//

class VTUFileIOToolsetGui : public SAMToolsetGui
{
    Q_OBJECT
public:

    // Constructor and destructor:
    VTUFileIOToolsetGui();
    ~VTUFileIOToolsetGui();

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

private:
    
private slots:
    void PrintMsg();
    void SaveDialog();
    void OnSave(const QString& path);
};

#endif