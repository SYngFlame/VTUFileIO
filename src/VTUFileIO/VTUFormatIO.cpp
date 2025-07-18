#include <VTUFormatIO.h>

#include <VTUDataContainer.h>

#include <qstring.h>
#include <QtXml/qxml.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qfileinfo.h>

FormatWriter::~FormatWriter() {
	if (file != NULL) {
		file->close();
		delete(file);
	}
	if(stream != NULL) delete(stream);
}

int FormatWriter::Write(const QString& path) {
	return 0;
}

State FormatWriter::GetCurrentState() const {
	return currentState;
}

int FormatWriter::GetNodesWritten() const {
	return nodesWritten;
}

int FormatWriter::GetCellsWritten() const {
	return cellsWritten;
}

/*
* -----------------------------------------------------------------------------
* VTU
*/

VTUFormatWriter::VTUFormatWriter(const QString& path, VTUDataContainer* VTKData) {

	this->data = VTKData;

	QString targetPath = path;
	if (QFileInfo(path).suffix() != "vtu") targetPath = path + ".vtu";

	QFile* file = new QFile(targetPath);
	if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
		delete file;
		file = nullptr;
	}
	else QTextStream* stream = new QTextStream(file);
	stream->setRealNumberPrecision(8);
	stream->setRealNumberNotation(QTextStream::ScientificNotation);

}

int VTUFormatWriter::Write(const QString& path) {
	QString targetPath = path;
	if (QFileInfo(path).suffix() == "vtu") targetPath = path + ".vtu";
	return 0;
}

/*
* -----------------------------------------------------------------------------
* VTKLegacy
*/

VTKLegacyFormatWriter::VTKLegacyFormatWriter(const QString& path, VTUDataContainer* VTKData) {

	this->data = VTKData;
	QString targetPath = path;
	if (QFileInfo(path).suffix() != "vtk") targetPath = path + ".vtk";

	file = new QFile(targetPath);
	if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
		file = NULL;
		return;
	}
	stream = new QTextStream(file);
	stream->setRealNumberPrecision(8);
	stream->setRealNumberNotation(QTextStream::SmartNotation);
	stream->setNumberFlags(!QTextStream::ForcePoint);

}

int VTKLegacyFormatWriter::Write(const QString& path) {

	if (!file) return ERRORTYPE_NOTEXIST;
	*stream << "# vtk DataFile Version 3.0\n";
	*stream << "SAMModel Output" << "\n";
	*stream << "ASCII\n";
	*stream << "DATASET UNSTRUCTURED_GRID\n";
	*stream << flush;

	currentState = HeaderWritten;
	currentState = WritePointsHeader();
	*stream << flush;

	currentState = WritePoints();
	*stream << flush;

	currentState = WriteCellsHeader();
	*stream << flush;

	currentState = WriteCells();
	*stream << flush;

	currentState = WriteCellTypesHeader();
	*stream << flush;

	currentState = WriteCellTypes();
	*stream << flush;

	return 0;
}

State VTKLegacyFormatWriter::WritePointsHeader() {
	if (currentState != HeaderWritten) {
		return currentState; // 状态不正确
	}

	*stream << "POINTS " << data->points.size() << " float\n";
	nodesWritten = 0;
	return PointsWriting;
}

State VTKLegacyFormatWriter::WritePoints() {
	if (currentState != PointsWriting) {
		return currentState; // 状态不正确
	}

	for (int i = 0; i < data->points.size(); i++) {
		float x = data->points[i].x;
		float y = data->points[i].y;
		float z = data->points[i].z;
		*stream << x << " " << y << " " << z << "\n";
	}

	nodesWritten += data->points.size();
	return PointsWritten;
}

State VTKLegacyFormatWriter::WriteCellsHeader() {
	if (currentState != PointsWritten) {
		return currentState;
	}

	*stream << "\nCELLS " << data->elems.size() << " " << data->elemVertices << "\n";
	cellsWritten = 0;

	return CellsWriting;
}

State VTKLegacyFormatWriter::WriteCells() {
	if (currentState != CellsWriting) {
		return currentState; // 状态不正确
	}

	// 遍历每个单元
	for (int i = 0; i < data->elems.size(); i++) {
		// 获取单元节点数
		int numNodes = VTUElementHandler::GetArrayLengthByEnum(data->elems[i].type);
		*stream << numNodes;

		// 写入节点索引
		for (int j = 0; j < numNodes; j++) {
			*stream << " " << data->elems[i].dataSet[j];
		}
		*stream << "\n";
	}

	cellsWritten += data->elems.size();
	return CellsWritten;
}

State VTKLegacyFormatWriter::WriteCellTypesHeader() {
	if (currentState != CellsWritten) {
		return currentState; // 必须先完成单元写入
	}

	*stream << "\nCELL_TYPES " << data->elems.size() << "\n";

	return CellTypesWriting;
}

State VTKLegacyFormatWriter::WriteCellTypes() {
	if (currentState != CellTypesWriting) {
		return currentState; // 状态不正确
	}

	for (int i = 0; i < data->elems.size(); i++) {
		*stream << data->elems[i].type << "\n";
	}

	return CellTypesWritten;
}

State VTKLegacyFormatWriter::WriteMaterialsHeader() {
	return MaterialsWriting;
}

State VTKLegacyFormatWriter::WriteMaterials() {

	return MaterialsWriting;
}

State VTKLegacyFormatWriter::BeginField() {
	if (currentState != MaterialsWriting) {
		return currentState;
	}

	//*stream << "FIELD " << fieldName << " " << numFields << "\n";
	return FieldHeaderWritten;
}

State VTKLegacyFormatWriter::WriteFieldHeader()
{
	if (currentState != FieldHeaderWritten) {
		return currentState;
	}

	//*stream << name << " " << numComponents << " " << numTuples << " " << dataType << "\n";
	fieldDataWritten = 0;

	return FieldDataWriting;
}

State VTKLegacyFormatWriter::WriteFieldData() {
	//if (currentState != FieldDataWriting) {
	//	return currentState;
	//}

	//// 检查是否超过总数据量
	//if (fieldDataWritten + numValues > currentNumTuples * currentNumComponents) {
	//	qWarning() << "Attempted to write too much field data:"
	//		<< numValues << "values when only"
	//		<< (currentNumTuples * currentNumComponents - fieldDataWritten)
	//		<< "remaining";
	//	return currentState;
	//}

	//int valuesWritten = 0;
	//while (valuesWritten < numValues) {
	//	// 计算当前行剩余空间
	//	int spaceInLine = currentDataPerLine - (fieldDataWritten % currentDataPerLine);
	//	int valuesToWrite = qMin(numValues - valuesWritten, spaceInLine);

	//	for (int i = 0; i < valuesToWrite; i++) {
	//		*stream << values[valuesWritten + i] << " ";
	//	}

	//	valuesWritten += valuesToWrite;
	//	fieldDataWritten += valuesToWrite;

	//	// 检查是否需要换行
	//	if (fieldDataWritten % currentDataPerLine == 0) {
	//		*stream << "\n";
	//	}
	//}

	//// 如果已完成字段写入
	//if (fieldDataWritten >= currentNumTuples * currentNumComponents) {
	//	*stream << "\n\n"; // 字段结束，两个换行分隔
	//	currentState = FieldHeaderWritten; // 回到字段头状态
	//}

	return FieldDataWriting;
}

State VTKLegacyFormatWriter::WriteField(const QString& name, int numComponents, int numTuples,
	const QString& dataType, float* values)
{
	// 使用新接口一次性完成
	/*if (!WriteFieldHeader(name, numComponents, numTuples, dataType)) {
		return currentState;
	}
	return WriteFieldData(values, numTuples * numComponents);*/
	return FieldDataWriting;
}

void VTKLegacyFormatWriter::End() {
	if (stream) {
		if (currentState == FieldDataWriting) {
			// 如果字段未完成，手动添加换行
			*stream << "\n\n";
		}
	}
	currentState = Finished;
}