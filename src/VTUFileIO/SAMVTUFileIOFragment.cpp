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


//�����ͷ�ļ���Ϊ��print��������ӵ�
#include<odbOdbRepository.h>
#include<odbmesh.h>
#include<odaOdbFragment.h>
#include <odbPartRepository.h>  // ����odbPartRepository����������
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
    // ��ODB�ļ���ȷ����ȡ��������
    odbOdb& odb = odbOdbRepository::Instance().get("E:/internship/Utils/zhen/bin/Debug/test.h5");
    //odb.Read();            // ȷ����ȡ��������
    odb.ReadStepCon();     // ���ز���������Ϣ
    qDebug() << "ODB file opened successfully. Analysis Title:" << odb.analysisTitle();

    // 1. �����Ʋ���Step-1
    odbStepRepository& stepsRep = odb.steps();
    if (!stepsRep.isMember("Step-1")) {
        qDebug() << "Error: Step-1 not found in ODB";
        return nullptr;
    }

    // ��ȡStep-1
    odbStep& step = stepsRep["Step-1"];
	//step.Read();
    // ʹ�ø���ȫ�ķ�ʽ��ȡ֡����
    int frameCount = 0;
    try {
        // ʹ��constGet��������Ǳ������
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

    // 2. ʹ�ø���ȫ�ķ�ʽ��ȡFrame-0
    odbFrame* pFrame = nullptr;
    try {
        // ʹ��frames()������ȡ֡����
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


    // 3. ��ȡ�����
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