#include <omuArguments.h>
#include <omuPrimNumber.h>

#include <cmdCWIP.h>
#include <Example1PytModule.h>

static omuInterfaceObj::methodTable Example1PytModuleMethods[] =
{ 
	{"calcArea", (omuInterfaceObj::methodFunc)&Example1PytModule::calcArea},
	{0, 0} 
};

Example1PytModule::Example1PytModule()
	: pyoModule("Example1", Example1PytModuleMethods, pyoModule::NO_IMPORT)
{
	//第一个参数与项目输出的库名称相同
}




Example1PytModule::~Example1PytModule()
{
	// do nothing
}

void Example1PytModule::DefineConstants()
{
	// do nothing
}

omuPrimitive* Example1PytModule::calcArea(omuArguments& args)
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
