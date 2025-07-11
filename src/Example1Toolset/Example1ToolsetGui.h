/* -*- mode: c++ -*- */
#ifndef Example1ToolsetGui_h
#define Example1ToolsetGui_h

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



class Example1Form;

//
// Class definition
//

class Example1ToolsetGui : public SAMToolsetGui, public omiSingleton<Example1ToolsetGui>
{
    Q_OBJECT
    friend class omiSingleton<Example1ToolsetGui>;
public:

    // Constructor and destructor:
    Example1ToolsetGui();
    ~Example1ToolsetGui();

private:
    // Copy constructor and assignment operator
    Example1ToolsetGui(const Example1ToolsetGui&);

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