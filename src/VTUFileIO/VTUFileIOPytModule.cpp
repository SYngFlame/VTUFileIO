#include <omuArguments.h>
#include <omuPrimNumber.h>

#include <cmdCWIP.h>
#include <VTUFileIOPytModule.h>

static omuInterfaceObj::methodTable VTUFileIOPytModuleMethods[] =
{ 
	{"calcArea", (omuInterfaceObj::methodFunc)&VTUFileIOPytModule::calcArea},
	{0, 0} 
};

VTUFileIOPytModule::VTUFileIOPytModule()
	: pyoModule("VTUFileIO", VTUFileIOPytModuleMethods, pyoModule::NO_IMPORT)
{
	//��һ����������Ŀ����Ŀ�������ͬ
}




VTUFileIOPytModule::~VTUFileIOPytModule()
{
	// do nothing
}

void VTUFileIOPytModule::DefineConstants()
{
	// do nothing
}

omuPrimitive* VTUFileIOPytModule::calcArea(omuArguments& args)
{
	double length, width;
	args.Begin();
	args.Get(length);
	args.Get(width);
	args.End();

	double area;
	area = length * width;

	return new omuPrimNumber(area);
}
