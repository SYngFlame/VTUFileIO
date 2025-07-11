/* -*- mode: c++ -*- */
#ifndef Example1DB_h
#define Example1DB_h

// Begin Local Includes
#include <SAMDataDialog.h>

// Forward declarations
class Example1Form;
class QLineEdit;
//
// Class definition
//

class Example1DB : public SAMDataDialog
{
	Q_OBJECT
public:
	/// Constructor.
	Example1DB(Example1Form* form);

	/// Destructor.
	~Example1DB();

private:
	// Data members
	QLineEdit* startPointEdit;
	QLineEdit* midPointEdit;
	QLineEdit* endPointEdit;

private slots:
	void onCmdOk(int) override;

};

#endif