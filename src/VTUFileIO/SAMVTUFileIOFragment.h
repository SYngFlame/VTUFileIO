/* -*- mode: c++ -*- */
#ifndef SAMVTUFileIOFragment_h
#define SAMVTUFileIOFragment_h

#include <VTUFileIOUtils.h>
#include <ptsKPartFragment.h>
#include <g3dVector.h>
#include <kefKLine.h>

class omuArguments;

// Class definition

class SAMVTUFileIOFragment : public ptsKPartFragment
{
public:
	SAMVTUFileIOFragment();
	virtual ~SAMVTUFileIOFragment();

	omuPrimitive* Copy() const;

	omuPrimitive* printAll(omuArguments& args);
};

#endif  // #ifdef SAMVTUFileIOFragment_h
