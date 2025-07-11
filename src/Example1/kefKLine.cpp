#include <kefKLine.h>
#include <kefKSymbolFactory.h>

#include <sesKSessionState.h>


#include <gslMatrix.h>

#include <kefCEngineeringFeatures.h>

#include <gdrRenderer.h>

#include <gdyEditor.h>
#include <gdyDisplayRep.h>
#include <gdyScene.h>
#include <dgpKScene.h>
#include <g3dPoint.h>
#include <g3dMarker.h>

#include <smgSceneManagerRole.h>

#include <ftrFeature.h>
#include <ftrEvaluatedRep.h>
#include <ftrPrimaryObject.h>

#include <nexDynamicCast.h>


kefKLine::kefKLine()
	: gdyNonPageGeomEditor(),
	showEOs(false),
	staleSymbolListMap(false),
	timeStamp(0.0),
	type_atom("kefKLine"),
	_geomVertexXYZs(cowList<cowList<g3dVector>>()),
	_colors(cowListString()),
	_segID(cowListInt()),
	_maxSegID(0)
{
	// do nothing
}

kefKLine::~kefKLine()
{
	// do nothing
}

gdyGeomEditor* kefKLine::Copy() const
{
	return new kefKLine(*this);
}

void kefKLine::Load(const gdyDisplayRep* r, g3dSphere* extent)
{
	timeStamp = 0.0;
}

void kefKLine::Unload()
{
	timeStamp = 0.0;
}

void kefKLine::Draft(gdrRenderer& r) const
{
	Draw(r, false);
}

void kefKLine::Paint(gdrRenderer& r) const
{
	Draw(r, true);
}

void kefKLine::ASelect(gdrASelector& as) const
{
	// do nothing
}

void kefKLine::Highlight(gdrRenderer& r) const
{
	// todo
}

void kefKLine::SetHighlightedInertia(const QString& springName)
{
	if (!springName.isEmpty())
		highlightedInertias.Append(springName);
}

void kefKLine::HighlightInertia(const QString& springName)
{
	// todo
}

void kefKLine::UnhighlightAll()
{
	// todo
}

void kefKLine::UpdateDisplayOptions(const sesCDisplayOptions& options)
{

}

void kefKLine::setObject(const cowList<cowList<g3dVector>>& vertexXYZ, const cowListString& color)
{
	if (vertexXYZ.Length() != color.Length())
		return ;

	for (int i = 0; i < vertexXYZ.Length(); i++)
	{
		_geomVertexXYZs.Append(vertexXYZ[i]);
		_colors.Append(color[i]);
		_segID.Append(_maxSegID++);
	}

}

void kefKLine::addObject(const cowList<cowList<g3dVector>>& vertexXYZ, const cowListString & color)
{
	if (vertexXYZ.Length() != color.Length())
		return;

	for (int i = 0; i < vertexXYZ.Length(); i++)
	{
		_geomVertexXYZs.Append(vertexXYZ[i]);
		_colors.Append(color[i]);
		_segID.Append(_maxSegID++);
	}
	
}

void kefKLine::createOneObject(int & SegID, const cowList<g3dVector>& vertexXYZ, const QString & color)
{
	int objectIndex = -1;
	if (!_segID.IsEmpty())
		objectIndex = _segID.FindMember(SegID);
	
	// modify a object
	if (objectIndex >= 0)
	{
		_geomVertexXYZs.Get(objectIndex) = vertexXYZ;
		_colors.Get(objectIndex) = color;
	}
	// create a new object
	else
	{
		_geomVertexXYZs.Append(vertexXYZ);
		_colors.Append(color);
		SegID = _maxSegID++;
		_segID.Append(SegID);
	}
	
}

void kefKLine::deleteOneObject(const int & SegID)
{
	int objectIndex = -1;
	objectIndex = _segID.FindMember(SegID);
	if (objectIndex < 0)
		return;

	_geomVertexXYZs.RemoveIndex(objectIndex);
	_colors.RemoveIndex(objectIndex);
	_segID.RemoveIndex(objectIndex);
	
}



void kefKLine::RebuildSymbolListMap()
{

}

void kefKLine::Draw(gdrRenderer& drafter, bool paintMode) const
{
	drafter.DepthTest(false);

	g3dPoint pnt;
	g3dColor sColor(1.0, 0.0, 0, 1.0);
	g3dVector normal(1.0f, 0.0f, 1.0f);
	drafter.Color(sColor);
	drafter.Normal(normal);

	for (int i = 0; i < _geomVertexXYZs.Length(); i++)
	{
		if (_geomVertexXYZs[i].Length() == 1)
			drafter.Begin(g3d_Points);
		else if (_geomVertexXYZs[i].Length() == 2)
			drafter.Begin(g3d_Lines);
		else if (_geomVertexXYZs[i].Length() == 3)
			drafter.Begin(g3d_Tris);
		else if (_geomVertexXYZs[i].Length() == 4)
			drafter.Begin(g3d_Quads);
		else if (_geomVertexXYZs[i].Length() > 4)
			drafter.Begin(g3d_Polygon);
		
		for (int j = 0; j < _geomVertexXYZs[i].Length(); j++)
		{
			pnt.Set(_geomVertexXYZs[i][j].GetX(), _geomVertexXYZs[i][j].GetY(), _geomVertexXYZs[i][j].GetZ(), 1.0f);
			drafter.Vertex(pnt);
		}

		drafter.End();
	}

}

void kefKLine::CreateSymbols(
	bool repopulate,
	const ftrPrimaryObject* po,
	const QString& instanceName,
	const gslMatrix& transform
)
{

}


