#ifndef VTUFORMATIO 
#define VTUFORMATIO

#include <ErrorHandler.h>

class VTUDataContainer;
class QString;
class QFile;
class QTextStream;

enum State {
	NotStarted,         // δ��ʼ
	HeaderWritten,      // �ļ�ͷ��д��
	PointsWriting,      // �ڵ�д����
	PointsWritten,
	CellsWriting,       // ��Ԫд����
	CellsWritten,
	CellTypesWriting,   // ��Ԫ����д����
	CellTypesWritten,
	MaterialsWriting,   // ��������д����
	FieldHeaderWritten, // FIELD��ͷ��д�� (����״̬)
	FieldDataWriting,   // FIELD����д���� (����״̬)
	Finished            // ���
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

	// �ֶ�д�����״̬
	int fieldDataWritten;    // ��д����ֶ����ݵ���
	int currentNumTuples;    // ��ǰ�ֶε������ݵ���
	int currentNumComponents;// ��ǰ�ֶε������
	int currentDataPerLine;  // ÿ��д������ݵ���

public:
	virtual int Write(const QString& path);
	State GetCurrentState() const;

	// ��ȡ��д��ڵ���
	int GetNodesWritten() const;

	// ��ȡ��д�뵥Ԫ��
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

	// д��ڵ㲿��ͷ
	State WritePointsHeader();

	// д��һ���ڵ�����
	State WritePoints();

	// д�뵥Ԫ����ͷ
	State WriteCellsHeader();

	// д��һ����Ԫ����
	State WriteCells();

	// д�뵥Ԫ����ͷ
	State WriteCellTypesHeader();

	// д��һ����Ԫ����
	State WriteCellTypes();

	// д�����ͷ
	State WriteMaterialsHeader();

	// д��һ������ID
	State WriteMaterials();

	// ��ʼFIELD�� (��������)
	State BeginField();

	// д���ֶ�ͷ (��������)
	State WriteFieldHeader();

	// д���ֶ����� (����д��)
	State WriteFieldData();

	// д�������ֶ� (һ����д��)
	State WriteField(const QString& name, int numComponents, int numTuples,
		const QString& dataType, float* values);

	// ����д��
	void End();

	
};

#endif //!VTUFORMATIO 
