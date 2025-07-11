/* -*- mode: c++ -*- */
#ifndef VTUFileIOToolsetGui_h
#define VTUFileIOToolsetGui_h

//
// Includes
//

// Begin local includes

#include <SAMToolsetGui.h>
#include <omiSingleton.h>
#include <omiSingleton.T>

#include <mmgGRemoteModeInstaller.h>
#include <mmgGModeInstaller.h>
#include <mgnGModeFactory.h>
#include <omuPrimType.h>



class VTUFileIOForm;

//
// Class definition
//

class VTUFileIOToolsetGui : public SAMToolsetGui, public omiSingleton<VTUFileIOToolsetGui>
{
    Q_OBJECT
    friend class omiSingleton<VTUFileIOToolsetGui>;
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
    void ExampleUi();
};

#endif