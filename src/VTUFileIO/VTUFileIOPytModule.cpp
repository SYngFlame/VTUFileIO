#include <omuArguments.h>
#include <omuPrimNumber.h>

#include <cmdCWIP.h>
#include <VTUFileIOPytModule.h>

static omuInterfaceObj::methodTable VTUFileIOPytModuleMethods[] =
{ 
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
