/* -*- mode: c++ -*- */
#ifndef Example1PytModule_h
#define Example1PytModule_h

// Forward declarations

// Includes

// Begin local includes

#include <ptsKPartFragment.h>
#include <pyoModule.h>

// Class definition

class Example1PytModule : public pyoModule
{
public:

	Example1PytModule();
	virtual ~Example1PytModule();
	
	virtual void DefineConstants();

public:
	
	omuPrimitive* calcArea(omuArguments& args);

private:

	Example1PytModule(const Example1PytModule&);
	Example1PytModule& operator=(const Example1PytModule&);
};

#endif  // #ifdef shipPytModule_h