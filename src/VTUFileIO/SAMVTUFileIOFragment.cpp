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
	basBasis* bas = basBasis::Instance();
	basMdb mdb = bas->Fetch();
	basModelMap modelsMap = mdb.GetModels();
	cowListString modelList = modelsMap.Keys();

	for (int i = 0; i < modelList.Length(); ++i) {
		QString s = modelList.Get(i);
		qDebug(qPrintable(s));
		const ptoKPartRepository& parts = ptoKConstGetPartRepos(mdb, s);
		if (parts.IsEmpty()) return 0;
		for (int p = 1; p <= parts.Size(); ++p) {
			QString partname = parts.GetKey(p);
			qDebug(qPrintable(partname));
			
			ptoKPart part = parts.ConstGet(p);
			ftrFeatureList* flpart = part.GetFeatureList();

			if (!flpart->MeshExists(bdoDefaultInstId)) continue;

			const bmeMesh* objectMesh = flpart->ConstGetMesh(bdoDefaultInstId);
			if (!objectMesh->NumNodes()) return 0;
			const bmeNodeData& nodeData = objectMesh->NodeData();
			utiCoordCont3D nodeContainer = nodeData.CoordContainer();
			cowListInt nodeList;
			nodeData.GetUserNodeLabels(nodeList);
			for (int n = 0; n < nodeList.Length(); ++n) {
				int userLabel = nodeList.ConstGet(n);
				float x, y, z;
				nodeContainer.GetCoord(nodeData.GetMeshNodeIndex(userLabel), x, y, z);

				QString pointMsg = QString("Node Label %1 (%2 ,%3, %4)").
						arg(userLabel).
						arg(x, 8, 'f', 2, ' ').
						arg(y, 8, 'f', 2, ' ').
						arg(z, 8, 'f', 2, ' ');
				qDebug(qPrintable(pointMsg));
			}

			const bmeElementData& elemData = objectMesh->ElementData();
			const bmeElementClassList& elemClasses = elemData.ConstGetClasses();
			for (int l = 0; l < elemClasses.Size(); ++l) {
				const bmeElementClass& elemclass = elemClasses.ConstGet(l);
				int index = elemclass.ClassIndex();
				QString s_index = QString("element %1 class %2").arg(l).arg(index);
				qDebug(qPrintable(s_index));
				qDebug(qPrintable(elemclass.ElemTypeLabel()));
			}
		}
	}
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
	fileManager = new VTUFileManager;
	if (fileManager != NULL)
	{
		status = fileManager->Init(path, display, modelName, partName);
		if (!(status |= fileManager->WriteCache())) {
			fileManager->WriteFile();
		}
		delete fileManager;
	}
	else status |= ERRORTYPE_MEMORYALLOCFAILED;
	ErrorHandler::ReportExportErr(status);
	
	return 0;
}