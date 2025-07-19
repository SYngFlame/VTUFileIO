#ifndef FORMATIO 
#define FORMATIO

#include <MessageHandler.h>

class VTUDataContainer;
class QString;
class QFile;
class QTextStream;

class FormatWriter {
public:
	enum State{
		NotInitialized,         // 未初始化
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

	FormatWriter();
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

public:
	virtual int Write();
	FormatWriter::State GetCurrentState() const;

	// 获取已写入节点数
	int GetNodesWritten() const;

	// 获取已写入单元数
	int GetCellsWritten() const;
};

class FormatReader {
public:
	
	FormatReader();
	~FormatReader();

protected:
	
	QFile* file;
	QTextStream* stream;

	int status;
	int nodesRead;
	int cellsRead;
	int materialsRead;
	
	VTUDataContainer* data;

	// 字段写入相关状态
	int fieldDataRead;    // 已写入的字段数据点数
	int currentNumTuples;    // 当前字段的总数据点数
	int currentNumComponents;// 当前字段的组件数
	int currentDataPerLine;  // 每行写入的数据点数

public:
	virtual int Read();

	// 获取已写入节点数
	int GetNodesRead() const;

	// 获取已写入单元数
	int GetCellsRead() const;
};

#endif //FORMATIO