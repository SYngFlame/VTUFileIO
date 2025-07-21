#include <VTUFileIOForm.h>
#include <VTUFileIODB.h>


VTUFileIOForm::VTUFileIOForm(SAMGuiObjectManager* owner)
	: SAMForm(owner)
{
}

/// Destructor.
VTUFileIOForm::~VTUFileIOForm()
{

}

SAMDialog* VTUFileIOForm::getFirstDialog()
{
	return new VTUFileIODB(this);
}