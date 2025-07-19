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

	// д��ڵ㲿��ͷ
	FormatWriter::State WritePointsHeader();

	// д��һ���ڵ�����
	FormatWriter::State WritePoints();

	// д�뵥Ԫ����ͷ
	FormatWriter::State WriteCellsHeader();

	// д��һ����Ԫ����
	FormatWriter::State WriteCells();

	// д�뵥Ԫ����ͷ
	FormatWriter::State WriteCellTypesHeader();

	// д��һ����Ԫ����
	FormatWriter::State WriteCellTypes();

	// д�����ͷ
	FormatWriter::State WriteMaterialsHeader();

	// д��һ������ID
	FormatWriter::State WriteMaterials();

	// ��ʼFIELD�� (��������)
	FormatWriter::State BeginField();

	// д���ֶ�ͷ (��������)
	FormatWriter::State WriteFieldHeader();

	// д���ֶ����� (����д��)
	FormatWriter::State WriteFieldData();

	// д�������ֶ� (һ����д��)
	FormatWriter::State WriteField(const QString& name, int numComponents, int numTuples,
		const QString& dataType, float* values);

};

class VTKLegacyFormatReader : public FormatReader {
public:
	VTKLegacyFormatReader(const QString& path, VTUDataContainer* VTKData);

	int Read();

	// ����ڵ�����
	int ReadPoints(int numPoints);

	// ����һ����Ԫ����
	int ReadCells(int numCells);

	int ReadCellTypes(int numTypes);

};

#endif //!VTKLEGACYFORMATIO 
