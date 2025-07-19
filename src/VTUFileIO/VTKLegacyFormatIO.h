#ifndef VTKLEGACYFORMATIO 
#define VTKLEGACYFORMATIO

#include <MessageHandler.h>
#include <FormatIO.h>

class VTUDataContainer;
class QString;
class QFile;
class QTextStream;

class VTKLegacyFormatWriter : public FormatWriter {
public:
	VTKLegacyFormatWriter(const QString& path, VTUDataContainer* VTKData);

	int Write();

	// 写入节点部分头
	FormatWriter::State WritePointsHeader();

	// 写入一批节点坐标
	FormatWriter::State WritePoints();

	// 写入单元部分头
	FormatWriter::State WriteCellsHeader();

	// 写入一批单元数据
	FormatWriter::State WriteCells();

	// 写入单元类型头
	FormatWriter::State WriteCellTypesHeader();

	// 写入一批单元类型
	FormatWriter::State WriteCellTypes();

	// 写入材料头
	FormatWriter::State WriteMaterialsHeader();

	// 写入一批材料ID
	FormatWriter::State WriteMaterials();

	// 开始FIELD块 (新增函数)
	FormatWriter::State BeginField();

	// 写入字段头 (新增函数)
	FormatWriter::State WriteFieldHeader();

	// 写入字段数据 (分批写入)
	FormatWriter::State WriteFieldData();

	// 写入完整字段 (一次性写入)
	FormatWriter::State WriteField(const QString& name, int numComponents, int numTuples,
		const QString& dataType, float* values);

};

class VTKLegacyFormatReader : public FormatReader {
public:
	VTKLegacyFormatReader(const QString& path, VTUDataContainer* VTKData);

	int Read();

	// 读入节点坐标
	int ReadPoints(int numPoints);

	// 读入一批单元数据
	int ReadCells(int numCells);

	int ReadCellTypes(int numTypes);

};

#endif //!VTKLEGACYFORMATIO 
