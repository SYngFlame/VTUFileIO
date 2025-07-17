#include <VTUFormatIO.h>

#include <VTUDataContainer.h>

#include <qstring.h>
#include <QtXml/qxml.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qfileinfo.h>

FormatWriter::~FormatWriter() {
	file->close();
	delete(file);
	delete(stream);
}

int FormatWriter::Write(const VTUDataContainer& data, const QString& path) {
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

VTUFormatWriter::VTUFormatWriter(const QString& path, const VTUDataContainer& VTKData) {
	QString targetPath = path;
	if (QFileInfo(path).suffix() != "vtu") targetPath = path + ".vtu";

	QFile* file = new QFile(path);
	if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
		delete file;
		file = nullptr;
	}
	else QTextStream* stream = new QTextStream(file);
	stream->setRealNumberPrecision(8);
	stream->setRealNumberNotation(QTextStream::ScientificNotation);

}

int VTUFormatWriter::Write(const VTUDataContainer& data, const QString& path) {
	QString targetPath = path;
	if (QFileInfo(path).suffix() == "vtu") targetPath = path + ".vtu";
	return 0;
}

/*
* -----------------------------------------------------------------------------
* VTKLegacy
*/

VTKLegacyFormatWriter::VTKLegacyFormatWriter(const QString& path, const VTUDataContainer& VTKData) {
	QString targetPath = path;
	if (QFileInfo(path).suffix() != "vtk") targetPath = path + ".vtk";

	QFile* file = new QFile(path);
	if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
		delete file;
		file = nullptr;
	}
	else QTextStream* stream = new QTextStream(file);
	stream->setRealNumberPrecision(8);
	stream->setRealNumberNotation(QTextStream::ScientificNotation);

}

int VTKLegacyFormatWriter::Write(const VTUDataContainer& data, const QString& path) {

	if(file)
	*stream << "# vtk DataFile Version 3.0\n";
	*stream << "SAMModel Output" << "\n";
	*stream << "ASCII\n";
	*stream << "DATASET UNSTRUCTURED_GRID\n";

	currentState = HeaderWritten;
	currentState = WritePointsHeader();



	return 0;
}

State VTKLegacyFormatWriter::WritePointsHeader() {
	if (currentState != HeaderWritten) {
		return currentState; // ״̬����ȷ
	}

	*stream << "POINTS " << data->points.size() << " float\n";
	nodesWritten = 0;
	return PointsWriting;
}

State VTKLegacyFormatWriter::WritePoints() {
	if (currentState != PointsWriting) {
		return currentState; // ״̬����ȷ
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
	if (currentState != PointsWriting) {
		return currentState;
	}

	*stream << "\nCELLS " << data->elems.size() << " " << data->elemVertices << "\n";
	currentState = CellsWriting;
	cellsWritten = 0;
	return CellsWriting;
}

State VTKLegacyFormatWriter::WriteCells() {
	if (currentState != CellsWriting) {
		return currentState; // ״̬����ȷ
	}

	// ����ÿ����Ԫ
	int index = 0;
	for (int i = 0; i < data->elems.size(); i++) {
		// ��ȡ��Ԫ�ڵ���
		int numNodes = VTUElementHandler::GetArrayLength(data->elems[i].type);
		*stream << numNodes;

		// д��ڵ�����
		for (int j = 0; j < numNodes; j++) {
			*stream << " " << data->elems[i].dataSet[index++];
		}
		*stream << "\n";
	}

	cellsWritten += data->elems.size();
	return CellsWritten;
}

State VTKLegacyFormatWriter::WriteCellTypesHeader() {
	if (currentState != CellsWriting) {
		return currentState; // ��������ɵ�Ԫд��
	}

	*stream << "\nCELL_TYPES " << data->elems.size() << "\n";

	return CellTypesWriting;
}

State VTKLegacyFormatWriter::WriteCellTypes() {
	if (currentState != CellTypesWriting) {
		return currentState; // ״̬����ȷ
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

	//// ����Ƿ񳬹���������
	//if (fieldDataWritten + numValues > currentNumTuples * currentNumComponents) {
	//	qWarning() << "Attempted to write too much field data:"
	//		<< numValues << "values when only"
	//		<< (currentNumTuples * currentNumComponents - fieldDataWritten)
	//		<< "remaining";
	//	return currentState;
	//}

	//int valuesWritten = 0;
	//while (valuesWritten < numValues) {
	//	// ���㵱ǰ��ʣ��ռ�
	//	int spaceInLine = currentDataPerLine - (fieldDataWritten % currentDataPerLine);
	//	int valuesToWrite = qMin(numValues - valuesWritten, spaceInLine);

	//	for (int i = 0; i < valuesToWrite; i++) {
	//		*stream << values[valuesWritten + i] << " ";
	//	}

	//	valuesWritten += valuesToWrite;
	//	fieldDataWritten += valuesToWrite;

	//	// ����Ƿ���Ҫ����
	//	if (fieldDataWritten % currentDataPerLine == 0) {
	//		*stream << "\n";
	//	}
	//}

	//// ���������ֶ�д��
	//if (fieldDataWritten >= currentNumTuples * currentNumComponents) {
	//	*stream << "\n\n"; // �ֶν������������зָ�
	//	currentState = FieldHeaderWritten; // �ص��ֶ�ͷ״̬
	//}

	return FieldDataWriting;
}

State VTKLegacyFormatWriter::WriteField(const QString& name, int numComponents, int numTuples,
	const QString& dataType, float* values)
{
	// ʹ���½ӿ�һ�������
	/*if (!WriteFieldHeader(name, numComponents, numTuples, dataType)) {
		return currentState;
	}
	return WriteFieldData(values, numTuples * numComponents);*/
	return FieldDataWriting;
}

void VTKLegacyFormatWriter::End() {
	if (stream) {
		if (currentState == FieldDataWriting) {
			// ����ֶ�δ��ɣ��ֶ���ӻ���
			*stream << "\n\n";
		}
	}
	currentState = Finished;
}