#include <SAMVTUFileIOFragment.h>

//#include <gdyScene.h>
//#include <gdyEditor.h>
//#include <cowList.T>

#include <ptoKPartRepository.h>
#include <ptoKUtils.h>
#include <ptoKPart.h> 
#include <ftrFeatureList.h>
#include <basMdb.h>
#include <basBasis.h>
#include <basNewModel.h>

#include <bmeMesh.h> 
#include <bmeElementClass.h>
#include <bmeElementClassList.h>

#include <MessageHandler.h>


//下面的头文件是为了print后处理结果添加的
#include<odbOdbRepository.h>
#include<odbmesh.h>
#include<odaOdbFragment.h>
#include <odbPartRepository.h>  // 包含odbPartRepository的完整定义
#include <QDebug>
#include <QStringList>
#include <ddbMesh.h>
#include <iterator>
#include <cowbtree.h>
#include <ddbNode.h>
#include <ddbElementData.h>
#include <ddbElementClass.h>

#include <odbStep.h>
#include <odbStepRepository.h>
#include <ddbStep.h>
#include <ddbDdbStep.h>
#include <ddbDdbStepContainer.h>
#include <odbFrame.h>
#include <ddbFrameContainer.h>
#include <odbFieldValue.h>
#include <odbFieldValueData.h>
#include <odbFieldValueList.h>
#include <FEDdbFrame.h>
#include <ddbFieldContainer.h>
#include <odbFieldOutputRepository.h>
#include <ddbField.h>

static omuInterfaceObj::methodTable SAMVTUFileIOFMethods[] =
{
	{"printAll", (omuInterfaceObj::methodFunc)&SAMVTUFileIOFragment::printAll},
	{"initWriteManager",(omuInterfaceObj::methodFunc)&SAMVTUFileIOFragment::initWriteManager},
	{"initReadManager",(omuInterfaceObj::methodFunc)&SAMVTUFileIOFragment::initReadManager},
	{ 0, 0 }
};

static omuInterfaceObj::memberTable SAMVTUFileIOFMembers[] =
{
	{ 0, 0, 0 }
};

SAMVTUFileIOFragment::SAMVTUFileIOFragment()
	: ptsKModelFragment()
{
	omuInterfaceObj::DescribeType("SAMVTUFileIOFragment", SAMVTUFileIOFMethods, SAMVTUFileIOFMembers);
	fileManager = NULL;
}
SAMVTUFileIOFragment::~SAMVTUFileIOFragment()
{
	if (fileManager != NULL) delete(fileManager);
}

omuPrimitive* SAMVTUFileIOFragment::Copy() const
{
	return new SAMVTUFileIOFragment(*this);
}


omuPrimitive* SAMVTUFileIOFragment::printAll(omuArguments& args)
{
    // 打开ODB文件并确保读取基础数据
    odbOdb& odb = odbOdbRepository::Instance().get("E:/internship/Utils/zhen/bin/Debug/test.h5");
    //odb.Read();            // 确保读取基础数据
    odb.ReadStepCon();     // 加载步骤容器信息
    qDebug() << "ODB file opened successfully. Analysis Title:" << odb.analysisTitle();

    // 1. 按名称查找Step-1
    odbStepRepository& stepsRep = odb.steps();
    if (!stepsRep.isMember("Step-1")) {
        qDebug() << "Error: Step-1 not found in ODB";
        return nullptr;
    }

    // 获取Step-1
    odbStep& step = stepsRep["Step-1"];
	//step.Read();
    // 使用更安全的方式获取帧数量
    int frameCount = 0;
    try {
        // 使用constGet方法避免潜在问题
        const odbSequenceFrame& frames = step.frames(); 
        frameCount = frames.size();
		odbFrame& frame = frames.get(0);
    }

    catch (...) {
        qDebug() << "Warning: Failed to access frames container";
    }

    qDebug() << "\nStep:" << step.name()
        << "| Description:" << step.description()
        << "| Domain:" << (step.domain() == odbEnum::TIME ? "TIME" : "UNKNOWN")
        << "| Frames:" << frameCount;

    // 2. 使用更安全的方式获取Frame-0
    odbFrame* pFrame = nullptr;
    try {
        // 使用frames()方法获取帧引用
        pFrame = &step.frames(0);
    }
    catch (...) {
        qDebug() << "Error: Failed to access frame 0";
        return nullptr;
    }

    if (!pFrame) {
        qDebug() << "Error: Frame 0 is null";
        return nullptr;
    }

    odbFrame& frame = *pFrame;


    // 3. 获取场输出
    const odbFieldOutputRepository& fieldOutputs = frame.fieldOutputs();
    if (!fieldOutputs.isMember("U")) {
        qDebug() << "Error: Field output 'U' not found";
        return nullptr;
    }


	const odbSequenceString fieldOutput = fieldOutputs.getFieldOutputNames();
	//qDebug() << "\nfieldOutput:" << fieldOutput;
	

    
    qDebug() << "\nProcessing complete! Successfully read Step data?";
    return nullptr;
}
omuPrimitive* SAMVTUFileIOFragment::initWriteManager(omuArguments& args) {

	QString path;
	int display;
	QString modelName;
	QString partName;
	args.Begin();
	args.Get(path);
	args.Get(display);
	args.Get(modelName);
	args.Get(partName);
	args.End();

	int status = 0;
	fileManager = new VTUFileManager;
	if (fileManager != NULL)
	{
		fileManager->Init(path, display, modelName, partName);
		if (!(status |= fileManager->WriteCache())) {
			fileManager->WriteFile();
		}
		delete fileManager;
	}
	else status |= ERRORTYPE_MEMORY_ALLOC_FAILED;
	MessageHandler::ReportExportErr(status);
	
	return 0;
}

omuPrimitive* SAMVTUFileIOFragment::initReadManager(omuArguments& args) {

	QString path;
	QString modelName;

	args.Begin();
	args.Get(path);
	args.Get(modelName);
	args.End();

	int status = 0;
	fileManager = new VTUFileManager;
	if (fileManager != NULL)
	{
		fileManager->Init(path, modelName);
		if (!(status |= fileManager->ReadToCache())) {
			status |= fileManager->ReadToSAM();
			fileManager->SyncSAM(modelShortcut);
		}
		delete fileManager;
	}
	else status |= ERRORTYPE_MEMORY_ALLOC_FAILED;

	//TODO:Complete error report
	MessageHandler::ReportImportErr(status);
	return 0;
}