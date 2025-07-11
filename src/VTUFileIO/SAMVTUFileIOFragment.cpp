#include <SAMVTUFileIOFragment.h>
#include <ptoKPart.h>
#include <bmeMesh.h>
#include <omeMesh.h>
#include <mesUtils.h>
#include <bmeElementClass.h>
#include <shpShape.h>
#include <bmgUtils.h>
#include <samMdbDrawable.h>
#include <samModelDrawable.h>
#include <samPartDrawable.h>
#include <gdyScene.h>
#include <gdyEditor.h>
#include <cowList.T>

static omuInterfaceObj::methodTable SAMVTUFileIOFMethods[] =
{
	{"drawExample", (omuInterfaceObj::methodFunc)&SAMVTUFileIOFragment::drawExample},
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

omuPrimitive* SAMVTUFileIOFragment::drawExample(omuArguments& args)
{
	double p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z;
	args.Begin();
	args.Get(p1x);
	args.Get(p1y);
	args.Get(p1z);
	args.Get(p2x);
	args.Get(p2y);
	args.Get(p2z);
	args.Get(p3x);
	args.Get(p3y);
	args.Get(p3z);
	args.End();

	g3dVector startPoint, midPoint, endPoint;
	startPoint.Set(p1x, p1y, p1z);
	midPoint.Set(p2x, p2y, p2z);
	endPoint.Set(p3x, p3y, p3z);

	g3dVector curveP[2];
	curveP[0] = startPoint;
	
	double t = 1.0 / 360;
	for (int segID = 0; segID < 360; ++segID) {
		double tt = t * segID;
		curveP[!(segID & 1)] = pow(1 - tt, 2) * startPoint + 2 * tt * (1 - tt) * midPoint + pow(tt, 2) * endPoint;
		DrawLine(segID, curveP[segID & 1], curveP[!(segID & 1)]);

	}
	return 0;
}

void SAMVTUFileIOFragment::DrawLine(int& segID, g3dVector startPoint, g3dVector endPoint)
{
	cowList<g3dVector> vertexXYZ;
	QString color("red");
	vertexXYZ.Clear();
	vertexXYZ.Append(startPoint);
	vertexXYZ.Append(endPoint);

	gdyScene* scn = gdyScene::GetCurrentScene(true);
	gdyEditor* edit = scn->Editor();
	kefKLine* drawLine = static_cast<kefKLine*>(edit->GetGeomEditorByType("kefKLine"));
	if (!drawLine)
	{
		edit->AddGeomEditor(new kefKLine);
		drawLine = static_cast<kefKLine*>(edit->GetGeomEditorByType("kefKLine"));
	}

	drawLine->createOneObject(segID, vertexXYZ, color);
	scn->ExposeVP();// updata

}
