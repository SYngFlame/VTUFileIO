#include <iniPythonModuleRegistrar.h>
#include <VTUFileIOPytModule.h>
#include <SAMVTUFileIOFragment.h>
#include <omuAtom.h>

static VTUFileIOPytModule* VTUFileIOPytModulePtr = 0;
static SAMVTUFileIOFragment* SAMVTUFileIOFragmentPtr = 0;
static int VTUFileIOReferenceCount = 0;

void VTUFileIOInitialize(int& count)
{
	if (!VTUFileIOReferenceCount++)
	{
		VTUFileIOPytModulePtr = new VTUFileIOPytModule;
		SAMVTUFileIOFragmentPtr = new SAMVTUFileIOFragment;
		omuAtom::CreateAtom("kefKLine");
		++count;
	}
}

void VTUFileIOFinalize(int& count)
{
	if (!--VTUFileIOReferenceCount)
	{
		if (VTUFileIOPytModulePtr)
		{
			delete VTUFileIOPytModulePtr;
			VTUFileIOPytModulePtr = 0;

			delete SAMVTUFileIOFragmentPtr;
			SAMVTUFileIOFragmentPtr = 0;
		}

		--count;
	}
}

extern "C" void initVTUFileIO(void)
{
	iniPythonModuleRegistrar::Instance().Register(VTUFileIOInitialize, VTUFileIOFinalize);
}

void SAMVTUFileIO_initialize()
{
}
