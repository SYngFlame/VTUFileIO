/* -*- mode: c++ -*- */
#ifndef VTUFileIODB_h
#define VTUFileIODB_h

// Begin Local Includes
#include <SAMDataDialog.h>

// Forward declarations
class VTUFileIOForm;
class QLineEdit;
//
// Class definition
//

class VTUFileIODB : public SAMDataDialog
{
	Q_OBJECT
public:
	/// Constructor.
	VTUFileIODB(VTUFileIOForm* form);

	/// Destructor.
	~VTUFileIODB();

private:
	// Data members
	QLineEdit* startPointEdit;
	QLineEdit* midPointEdit;
	QLineEdit* endPointEdit;

private slots:
	void onCmdOk(int) override;

};

#endif