/* -*- mode: c++ -*- */
#ifndef SAMVTUFileIOFragment_h
#define SAMVTUFileIOFragment_h

#include <VTUFileIOUtils.h>
#include <ptsKModelFragment.h>
#include <g3dVector.h>

#include <basShortcut.h>
#include <VTUFileManager.h>

class omuArguments;

// Class definition

class SAMVTUFileIOFragment : public ptsKModelFragment
{
private:
	VTUFileManager* fileManager;
public:
	SAMVTUFileIOFragment();
	virtual ~SAMVTUFileIOFragment();

	omuPrimitive* Copy() const;

	omuPrimitive* printAll(omuArguments& args);
	omuPrimitive* initWriteManager(omuArguments& args);
	omuPrimitive* initReadManager(omuArguments& args);
};

#endif  // #ifdef SAMVTUFileIOFragment_h
