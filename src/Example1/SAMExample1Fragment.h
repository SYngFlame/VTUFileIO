/* -*- mode: c++ -*- */
#ifndef SAMExample1Fragment_h
#define SAMExample1Fragment_h

#include <Example1Utils.h>
#include <ptsKPartFragment.h>
#include <g3dVector.h>
#include <kefKLine.h>

class omuArguments;

// Class definition

class SAMExample1Fragment : public ptsKPartFragment
{
public:
	SAMExample1Fragment();
	virtual ~SAMExample1Fragment();

	omuPrimitive* Copy() const;

	omuPrimitive* drawExample(omuArguments& args);

	void DrawLine(int& segID, g3dVector startPoint, g3dVector endPoint);
};

#endif  // #ifdef SAMExample1Fragment_h
