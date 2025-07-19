#include <VTKLegacyFormatIO.h>

#include <VTUDataContainer.h>

#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qfileinfo.h>

/*
* VTULegacyFormatWriter
* Write data in format of .vtk unstructured grid
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
}

int VTKLegacyFormatWriter::Write() {

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

FormatWriter::State VTKLegacyFormatWriter::WritePointsHeader() {
	if (currentState != HeaderWritten) {
		return currentState; // 状态不正确
	}

	*stream << "POINTS " << data->points.size() << " float";
	nodesWritten = 0;
	return PointsWriting;
}

FormatWriter::State VTKLegacyFormatWriter::WritePoints() {
	if (currentState != PointsWriting) {
		return currentState; // 状态不正确
	}

	for (int i = 0; i < data->points.size(); i++) {
		float x = data->points[i].x;
		float y = data->points[i].y;
		float z = data->points[i].z;
		if (i % 3 == 0)
			*stream << "\n";
		else
			*stream << " ";
		*stream << x << " " << y << " " << z;
		
	}

	nodesWritten += data->points.size();
	return PointsWritten;
}

FormatWriter::State VTKLegacyFormatWriter::WriteCellsHeader() {
	if (currentState != PointsWritten) {
		return currentState;
	}

	*stream << "\nCELLS " << data->elems.size() << " " << data->elemVertices << '\n';
	cellsWritten = 0;

	return CellsWriting;
}

FormatWriter::State VTKLegacyFormatWriter::WriteCells() {
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

			*stream << ' ' << data->elems[i].dataSet[j];
		}

		*stream << '\n';
	}

	cellsWritten += data->elems.size();
	return CellsWritten;
}

FormatWriter::State VTKLegacyFormatWriter::WriteCellTypesHeader() {
	if (currentState != CellsWritten) {
		return currentState; // 必须先完成单元写入
	}

	*stream << "\nCELL_TYPES " << data->elems.size() << '\n';

	return CellTypesWriting;
}

FormatWriter::State VTKLegacyFormatWriter::WriteCellTypes() {
	if (currentState != CellTypesWriting) {
		return currentState; // 状态不正确
	}

	for (int i = 0; i < data->elems.size(); i++) {
		*stream << data->elems[i].type << '\n';
	}

	return CellTypesWritten;
}

FormatWriter::State VTKLegacyFormatWriter::WriteMaterialsHeader() {
	return MaterialsWriting;
}

FormatWriter::State VTKLegacyFormatWriter::WriteMaterials() {

	return MaterialsWriting;
}

FormatWriter::State VTKLegacyFormatWriter::BeginField() {
	if (currentState != MaterialsWriting) {
		return currentState;
	}

	//*stream << "FIELD " << fieldName << " " << numFields << "\n";
	return FieldHeaderWritten;
}

FormatWriter::State VTKLegacyFormatWriter::WriteFieldHeader()
{
	if (currentState != FieldHeaderWritten) {
		return currentState;
	}

	//*stream << name << " " << numComponents << " " << numTuples << " " << dataType << "\n";
	fieldDataWritten = 0;

	return FieldDataWriting;
}

FormatWriter::State VTKLegacyFormatWriter::WriteFieldData() {
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

FormatWriter::State VTKLegacyFormatWriter::WriteField(const QString& name, int numComponents, int numTuples,
	const QString& dataType, float* values)
{
	// 使用新接口一次性完成
	/*if (!WriteFieldHeader(name, numComponents, numTuples, dataType)) {
		return currentState;
	}
	return WriteFieldData(values, numTuples * numComponents);*/
	return FieldDataWriting;
}

//void VTKLegacyFormatWriter::End() {
//	if (stream) {
//		if (currentState == FieldDataWriting) {
//			// 如果字段未完成，手动添加换行
//			*stream << "\n\n";
//		}
//	}
//	currentState = Finished;
//}

/*
* VTKLegacyFormatReader
* Read in .vtk unstructured grid files
*/

VTKLegacyFormatReader::VTKLegacyFormatReader(const QString& path, VTUDataContainer* VTKData) {
	this->data = VTKData;
	QString targetPath = path;
	if (QFileInfo(path).suffix() != "vtk") return;

	file = new QFile(targetPath);
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
		file = NULL;
		return;
	}
	stream = new QTextStream(file);
	nodesRead = 0;
	cellsRead = 0;
}

int VTKLegacyFormatReader::Read() {

	if (!file) return ERRORTYPE_NOTEXIST;

	if (stream->atEnd()) return ERRORTYPE_FILE_READ_FAILED;
	QString versionLine = stream->readLine();
	if (!versionLine.startsWith("# vtk DataFile Version")) {
		return ERRORTYPE_FILE_READ_FAILED;
	}

	// Comment line (skip)
	if (stream->atEnd()) return ERRORTYPE_FILE_READ_FAILED;

	stream->readLine();

	// Format (only ASCII supported)
	if (stream->atEnd()) return ERRORTYPE_FILE_READ_FAILED;
	QString format = stream->readLine().trimmed();
	if (format != "ASCII") {
		return ERRORTYPE_FILE_READ_FAILED;
	}

	// Dataset type
	if (stream->atEnd()) return ERRORTYPE_FILE_READ_FAILED;
	QString dataset = stream->readLine().trimmed();
	if (!dataset.startsWith("DATASET UNSTRUCTURED_GRID")) {
		return ERRORTYPE_FILE_READ_FAILED;
	}

	status |= 1;

	while (!stream->atEnd()) {
		QString line = stream->readLine().trimmed();

		if (line.startsWith("POINTS")) {
			QStringList parts = line.split(' ', QString::SkipEmptyParts);
			if (parts.size() < 2) return ERRORTYPE_WRONG_NODE_DATA;
			bool ok;
			int numPoints = parts[1].toInt(&ok);
			if (!ok) return ERRORTYPE_WRONG_NODE_DATA;

			if (parts[2] == "float" || parts[2] == "double" || parts[2] == "int" || parts[2] == "long")
			status |= ReadPoints(numPoints);
		}
		else if (line.startsWith("CELLS")) {
			QStringList parts = line.split(' ', QString::SkipEmptyParts);
			if (parts.size() < 2) return ERRORTYPE_WRONG_ELEMENT_DATA;
			bool ok;
			int numCells = parts[1].toInt(&ok);
			if (!ok) return ERRORTYPE_WRONG_ELEMENT_DATA;
			status |= ReadCells(numCells);

		}
		else if (line.startsWith("CELL_TYPES")) {
			QStringList parts = line.split(' ', QString::SkipEmptyParts);
			if (parts.size() < 2) continue;
			bool ok;
			int numTypes = parts[1].toInt(&ok);
			if (!ok) continue;
			status |= ReadCellTypes(numTypes);
		}
	}

	//state |= ReadMaterials();
	if (status & 1 || status & 2) return 0;
	else return ERRORTYPE_FILE_READ_FAILED;
}

int VTKLegacyFormatReader::ReadPoints(int numPoints) {
	for (int i = 0; i < numPoints; ++i) {
		if (stream->atEnd()) return ERRORTYPE_WRONG_NODE_DATA;

		QString line = stream->readLine().trimmed();
		QStringList coords = line.split(' ', QString::SkipEmptyParts);
		if (coords.size() < 3) return ERRORTYPE_WRONG_NODE_DATA;

		bool ok;
		float x = coords[0].toFloat(&ok);
		if (!ok) return ERRORTYPE_WRONG_NODE_DATA;

		float y = coords[1].toFloat(&ok);
		if (!ok) return ERRORTYPE_WRONG_NODE_DATA;

		float z = coords[2].toFloat(&ok);
		if (!ok) return ERRORTYPE_WRONG_NODE_DATA;

		data->InsertNextPoint(i, x, y, z);

		++nodesRead;
	}
	return 1;
}

int VTKLegacyFormatReader::ReadCells(int numCells) {

	data->elems.resize(numCells);

	for (int i = 0; i < numCells; ++i) {

		if (stream->atEnd()) return ERRORTYPE_WRONG_ELEMENT_DATA;
		QString line = stream->readLine().trimmed();
		QStringList tokens = line.split(' ', QString::SkipEmptyParts);
		if (tokens.isEmpty()) continue;
		bool ok;
		int count = tokens[0].toInt(&ok);
		if (!ok || tokens.size() < count + 1) {
			return ERRORTYPE_WRONG_ELEMENT_DATA;
		}
		
		// Copy element connectivity
		int* conn = (int*)malloc(sizeof(int) * count);
		if (!conn) return ERRORTYPE_MEMORY_ALLOC_FAILED;
		for (int j = 0; j < count; ++j) {
			conn[j] = tokens[j + 1].toInt(&ok);
			if (!ok) {
				free(conn);
				return ERRORTYPE_WRONG_ELEMENT_DATA;
			}
		}
		// Add to data container
		data->elems[i].dataSet = conn;
		++cellsRead;
	}
	return 1 << 1;
}

int VTKLegacyFormatReader::ReadCellTypes(int numTypes) {
	data->elems.resize(numTypes);
	for (int i = 0; i < numTypes; ++i) {

		if (stream->atEnd()) return ERRORTYPE_WRONG_ELEMENT_DATA;
		QString line = stream->readLine();
		if (line.isEmpty()) continue;
		bool ok;
		
		if (line.size() >  1) {
			return ERRORTYPE_WRONG_ELEMENT_DATA;
		}

		// Add to data container
		data->elems[i].type = (VTUElementHandler::VTKType)line.toInt(&ok);
	}
	return 1 << 2;
}