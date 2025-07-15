#pragma once

#define TASK_EXPORT 0
#define TASK_IMPORT 1
#define ERRORTYPE_NOTEXIST -1
#define ERRORTYPE_FILEREADFAILED -2
#define ERRORTYPE_FILEWRITEFAILED -3

#include <QtPlugin>
#include <basMdb.h>
#include <qvector.h>

class VTUFileManager
{
private:
	const basMdb* mdb;
	QVector<QString> SAMmodels;
	QVector<QVector<QString>> SAMparts;
	QString VTKPath;

public:
	VTUFileManager();
	virtual ~VTUFileManager();
	int isReady();

	int Init(basMdb* mdb, const QString& path);
	int GenerateTarget();
	int WriteTarget();
};

