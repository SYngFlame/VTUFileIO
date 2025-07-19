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
		NotInitialized,         // δ��ʼ��
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

	// �ֶ�д�����״̬
	int fieldDataWritten;    // ��д����ֶ����ݵ���
	int currentNumTuples;    // ��ǰ�ֶε������ݵ���
	int currentNumComponents;// ��ǰ�ֶε������

public:
	virtual int Write();
	FormatWriter::State GetCurrentState() const;

	// ��ȡ��д��ڵ���
	int GetNodesWritten() const;

	// ��ȡ��д�뵥Ԫ��
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

	// �ֶ�д�����״̬
	int fieldDataRead;    // ��д����ֶ����ݵ���
	int currentNumTuples;    // ��ǰ�ֶε������ݵ���
	int currentNumComponents;// ��ǰ�ֶε������
	int currentDataPerLine;  // ÿ��д������ݵ���

public:
	virtual int Read();

	// ��ȡ��д��ڵ���
	int GetNodesRead() const;

	// ��ȡ��д�뵥Ԫ��
	int GetCellsRead() const;
};

#endif //FORMATIO