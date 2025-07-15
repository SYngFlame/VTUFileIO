/* -*- mode: c++ -*- */
#ifndef SAMVTUFileIOFragment_h
#define SAMVTUFileIOFragment_h

#include <VTUFileIOUtils.h>
#include <ptsKPartFragment.h>
#include <g3dVector.h>

#include <VTUFileManager.h>

class omuArguments;

// Class definition

class SAMVTUFileIOFragment : public ptsKPartFragment
{
private:
	VTUFileManager* fileManager;
public:
	SAMVTUFileIOFragment();
	virtual ~SAMVTUFileIOFragment();

	omuPrimitive* Copy() const;

	omuPrimitive* printAll(omuArguments& args);
	omuPrimitive* initManager(omuArguments& args);
};

#endif  // #ifdef SAMVTUFileIOFragment_h
