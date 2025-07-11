#include <Example1Form.h>
#include <Example1DB.h>


Example1Form::Example1Form(SAMGuiObjectManager* owner)
	: SAMForm(owner)
{
}

/// Destructor.
Example1Form::~Example1Form()
{

}

SAMDialog* Example1Form::getFirstDialog()
{
	return new Example1DB(this);
}