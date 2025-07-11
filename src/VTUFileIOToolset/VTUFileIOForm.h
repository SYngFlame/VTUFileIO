#ifndef VTUFileIOForm_h
#define VTUFileIOForm_h

// Begin local includes
#include <SAMCreateEditForm.h>

// Forward declarations
class SAMGuiObjectManager;

// Class definition
class VTUFileIOForm : public SAMForm
{
	Q_OBJECT
	friend class VTUFileIODB;
public:
	VTUFileIOForm(SAMGuiObjectManager* owner);

	~VTUFileIOForm();

protected:
	virtual SAMDialog* getFirstDialog();

};

#endif  // #ifdef VTUFileIOForm_h
