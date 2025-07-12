/* -*- mode: c++ -*- */
#ifndef VTUFileIOPytModule_h
#define VTUFileIOPytModule_h

// Forward declarations

// Includes

// Begin local includes

#include <ptsKPartFragment.h>
#include <pyoModule.h>

// Class definition

class VTUFileIOPytModule : public pyoModule
{
public:

	VTUFileIOPytModule();
	virtual ~VTUFileIOPytModule();
	
	virtual void DefineConstants();

private:

	VTUFileIOPytModule(const VTUFileIOPytModule&);
	VTUFileIOPytModule& operator=(const VTUFileIOPytModule&);
};

#endif  // #ifdef shipPytModule_h