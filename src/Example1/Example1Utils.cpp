#include <iniPythonModuleRegistrar.h>
#include <Example1PytModule.h>
#include <SAMExample1Fragment.h>
#include <omuAtom.h>

static Example1PytModule* Example1PytModulePtr = 0;
static SAMExample1Fragment* SAMExample1FragmentPtr = 0;
static int Example1ReferenceCount = 0;

void Example1Initialize(int& count)
{
	if (!Example1ReferenceCount++)
	{
		Example1PytModulePtr = new Example1PytModule;
		SAMExample1FragmentPtr = new SAMExample1Fragment;
		omuAtom::CreateAtom("kefKLine");
		++count;
	}
}

void Example1Finalize(int& count)
{
	if (!--Example1ReferenceCount)
	{
		if (Example1PytModulePtr)
		{
			delete Example1PytModulePtr;
			Example1PytModulePtr = 0;

			delete SAMExample1FragmentPtr;
			SAMExample1FragmentPtr = 0;
		}

		--count;
	}
}

extern "C" void initExample1(void)
{
	iniPythonModuleRegistrar::Instance().Register(Example1Initialize, Example1Finalize);
}