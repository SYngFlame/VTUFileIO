#include <SAMVTUFileIOFragment.h>

#include <gdyScene.h>
#include <gdyEditor.h>
#include <cowList.T>

#include <ptoKUtils.h>
#include <ptoKPart.h> 
#include <ftrFeatureList.h>
#include <basMdb.h>
#include <basBasis.h>
#include <basNewModel.h>

#include <bmeMesh.h> 
#include <bmeElementClass.h>
#include <bmeElementClassList.h>

#include <ErrorHandler.h>

#include <QFile> // ���QFileͷ�ļ�
#include <QTextStream> // ���QTextStreamͷ�ļ�
#include <VTUDataContainer.h> // ���VTUDataContainerͷ�ļ�
#include <VTKFileReader.h> // ���VTKFileReaderͷ�ļ�
#include <QDebug>  // ��Ӵ���

static omuInterfaceObj::methodTable SAMVTUFileIOFMethods[] =
{
	{"printAll", (omuInterfaceObj::methodFunc)&SAMVTUFileIOFragment::printAll},
	{"initManager",(omuInterfaceObj::methodFunc)&SAMVTUFileIOFragment::initManager},
	{ 0, 0 }
};

static omuInterfaceObj::memberTable SAMVTUFileIOFMembers[] =
{
	{ 0, 0, 0 }
};

SAMVTUFileIOFragment::SAMVTUFileIOFragment()
	: ptsKPartFragment()
{
	omuInterfaceObj::DescribeType("SAMVTUFileIOFragment", SAMVTUFileIOFMethods, SAMVTUFileIOFMembers);
	fileManager = NULL;
}
SAMVTUFileIOFragment::~SAMVTUFileIOFragment()
{
	if (fileManager != NULL) free(fileManager);
}

omuPrimitive* SAMVTUFileIOFragment::Copy() const
{
	return new SAMVTUFileIOFragment(*this);
}

omuPrimitive* SAMVTUFileIOFragment::printAll(omuArguments& args)
{
	// ���Զ�ȡVTK�ļ� (��ʱ����)
	QFile vtkFile("C:/Users/charlatan/Desktop/AAA/simple_line.vtk"); // �޸�Ϊ��Ĳ����ļ�·��
	if (!vtkFile.exists()) {
		qDebug() << "Test VTK file not found!";
		return 0;
	}

	VTKFileReader reader(&vtkFile);
	int error = reader.ReadVTK();
	if (error) {
		qDebug() << "Error reading VTK file:" << error;
		ErrorHandler::ReportErr(error);
		return 0;
	}

	VTUDataContainer& data = reader.GetDataContainer();

	// ��ӡ�ڵ���Ϣ
	qDebug() << "===== Nodes =====";
	for (int i = 0; i < data.points.size(); ++i) {
		const Point& p = data.points[i];
		qDebug() << "Node" << i << ": (" << p.x << ", " << p.y << ", " << p.z << ")";
	}

	// ��ӡ��Ԫ��Ϣ
	qDebug() << "===== Elements =====";
	for (int i = 0; i < data.elems.size(); ++i) {
		const Element& e = data.elems[i];
		QString elemType;
		switch (e.type) {
		case 3: elemType = "B31/LINE"; break;
		case 5: elemType = "S3/TRI"; break;
		case 9: elemType = "S4R/QUAD"; break;
		default: elemType = "Unknown";
		}

		QString connStr = "Connections: ";
		// ע�⣺��������ʹ��Element����������ȡ�ڵ���
		int numNodes = VTUElementHandler::GetArrayLength(e.type);
		for (int j = 0; j < numNodes; ++j) {
			connStr += QString::number(e.dataSet[j]) + " ";
		}

		qDebug() << "Element" << i << ": Type:" << elemType << "-" << connStr;
	}

	// ��ʱ���: ��ӡͳ����Ϣ
	qDebug() << "===== Summary =====";
	qDebug() << "Total Nodes:" << data.points.size();
	qDebug() << "Total Elements:" << data.elems.size();

	return 0;
}


omuPrimitive* SAMVTUFileIOFragment::initManager(omuArguments& args) {

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
	fileManager = (VTUFileManager*)malloc(sizeof(VTUFileManager));
	if (fileManager != NULL)
	{
		status = fileManager->Init(path, display, modelName, partName);
		if (!(status = fileManager->WriteCache())) {
			//fileManager->WriteFile();

		}
	}
	else status &= ERRORTYPE_MEMORYALLOCFAILED;
	ErrorHandler::ReportErr(status);
	return 0;
}