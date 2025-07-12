#include <SAMVTUFileIOFragment.h>
#include <ptoKPart.h>
#include <gdyScene.h>
#include <gdyEditor.h>
#include <cowList.T>

#include <ptoKPart.h> 
#include <ftrFeatureList.h>
#include <basMdb.h>
#include <basBasis.h>
#include <basNewModel.h>
#include <ptoKUtils.h>
#include <bmeMesh.h> 

static omuInterfaceObj::methodTable SAMVTUFileIOFMethods[] =
{
	{"printAll", (omuInterfaceObj::methodFunc)&SAMVTUFileIOFragment::printAll},
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
}
SAMVTUFileIOFragment::~SAMVTUFileIOFragment()
{
	// todo
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
		for (int p = 1; p <= parts.Size(); ++p) {
			QString partname = parts.GetKey(p);
			qDebug(qPrintable(partname));
			ptoKPart part = parts.ConstGet(p);

			ftrFeatureList* flpart = part.GetFeatureList();
			const bmeMesh* objectMesh = flpart->ConstGetMesh(bdoDefaultInstId);

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
		}
	}
	return 0;
}