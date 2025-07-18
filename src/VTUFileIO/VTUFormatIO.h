#ifndef VTUFORMATIO 
#define VTUFORMATIO

#include <ErrorHandler.h>

class VTUDataContainer;
class QString;
class QFile;
class QTextStream;

enum State {
	NotStarted,         // 未开始
	HeaderWritten,      // 文件头已写入
	PointsWriting,      // 节点写入中
	PointsWritten,
	CellsWriting,       // 单元写入中
	CellsWritten,
	CellTypesWriting,   // 单元类型写入中
	CellTypesWritten,
	MaterialsWriting,   // 材料数据写入中
	FieldHeaderWritten, // FIELD块头已写入 (新增状态)
	FieldDataWriting,   // FIELD数据写入中 (新增状态)
	Finished            // 完成
};

class FormatWriter {
public:
	
	~FormatWriter();

protected:
	
	QFile* file;
	QTextStream* stream;

	State currentState;
	int nodesWritten;
	int cellsWritten;
	int materialsWritten;
	
	VTUDataContainer* data;

	// 字段写入相关状态
	int fieldDataWritten;    // 已写入的字段数据点数
	int currentNumTuples;    // 当前字段的总数据点数
	int currentNumComponents;// 当前字段的组件数
	int currentDataPerLine;  // 每行写入的数据点数

public:
	virtual int Write(const QString& path);
	State GetCurrentState() const;

	// 获取已写入节点数
	int GetNodesWritten() const;

	// 获取已写入单元数
	int GetCellsWritten() const;
};

/*
* -----------------------------------------------------------------------------
* VTU
*/

class VTUFormatWriter : public FormatWriter {
public:
	VTUFormatWriter(const QString& path, VTUDataContainer* VTKData);
	int Write(const QString& path);
};

/*
* -----------------------------------------------------------------------------
* VTKLegacy
*/

class VTKLegacyFormatWriter : public FormatWriter {
public:
	VTKLegacyFormatWriter(const QString& path, VTUDataContainer* VTKData);
	int Write(const QString& path);

	// 写入节点部分头
	State WritePointsHeader();

	// 写入一批节点坐标
	State WritePoints();

	// 写入单元部分头
	State WriteCellsHeader();

	// 写入一批单元数据
	State WriteCells();

	// 写入单元类型头
	State WriteCellTypesHeader();

	// 写入一批单元类型
	State WriteCellTypes();

	// 写入材料头
	State WriteMaterialsHeader();

	// 写入一批材料ID
	State WriteMaterials();

	// 开始FIELD块 (新增函数)
	State BeginField();

	// 写入字段头 (新增函数)
	State WriteFieldHeader();

	// 写入字段数据 (分批写入)
	State WriteFieldData();

	// 写入完整字段 (一次性写入)
	State WriteField(const QString& name, int numComponents, int numTuples,
		const QString& dataType, float* values);

	// 结束写入
	void End();

	
};

#endif //!VTUFORMATIO 
