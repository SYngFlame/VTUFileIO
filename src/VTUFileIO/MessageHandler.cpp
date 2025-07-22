#include <MessageHandler.h>



#include <cmdCWIP.h>
#include <qstringlist.h>
#include <qstring.h>

void MessageHandler::ReportExportErr(int err) {

	QStringList warn;

	cmdCWIP& Ins = cmdCWIP::Instance();
	{
		if (!err) Ins.Print("Export Finished");
		return;
	}

	if (err & ERRORTYPE_NOTEXIST) {
		warn.append(QString("Target to export does not exist."));
	}
	if (err & ERRORTYPE_FILE_WRITE_FAILED) {
		warn.append(QString("Fail to write in target file."));
	}
	if (err & ERRORTYPE_WRONG_NODE_DATA) {
		warn.append(QString("Error occured while obtaining nodes."));
	}
	if (err & ERRORTYPE_WRONG_ELEMENT_DATA) {
		warn.append(QString("Error occured while obtaining elements."));
	}
	if (err & ERRORTYPE_WRONG_SCENE) {
		warn.append(QString("Nothing to export in current scene"));
	}
	if (err & ERRORTYPE_MEMORY_ALLOC_FAILED) {
		warn.append(QString("Error in allocating memory"));
	}
	
	for (int i = 0; i < warn.size(); ++i) {
		Ins.Warning(warn[i]);
	}
}

void MessageHandler::ReportExportInfo(int pointNum, int elemNum) {
	cmdCWIP& Ins = cmdCWIP::Instance();
	QString message = QString("%1 nodes and %2 cells written.").arg(pointNum).arg(elemNum);
	Ins.Print(message);
}

void MessageHandler::ReportImportErr(int err) {
	//auto app = SAMApp::getSAMApp();
	//auto mw = app->getSAMMainWindow();

	QStringList warn;

	cmdCWIP& Ins = cmdCWIP::Instance();
	{
		if (!err) Ins.Print("Import Finished");
		return;
	}

	if (err & ERRORTYPE_NOTEXIST) {
		warn.append(QString("Target for import does not exist."));
	}
	if (err & ERRORTYPE_FILE_READ_FAILED) {
		warn.append(QString("Fail to read target file."));
	}
	if (err & ERRORTYPE_WRONG_NODE_DATA) {
		warn.append(QString("Error occured while obtaining nodes."));
	}
	if (err & ERRORTYPE_WRONG_ELEMENT_DATA) {
		warn.append(QString("Error occured while obtaining elements."));
	}
	if (err & ERRORTYPE_MEMORY_ALLOC_FAILED) {
		warn.append(QString("Error in allocating memory"));
	}
	if (err & ERRORTYPE_SAM_ACTION_FAILED) {
		warn.append(QString("SAM returned an error."));
	}
	if (err & ERRORTYPE_COLLISION_OCCURED) {
		warn.append(QString("Part name collision."));
	}

	for (int i = 0; i < warn.size(); ++i) {
		Ins.Warning(warn[i]);
	}
}

void MessageHandler::ReportImportInfo(int pointNum, int elemNum) {
	cmdCWIP& Ins = cmdCWIP::Instance();
	QString message = QString("%1 nodes and %2 cells read.").arg(pointNum).arg(elemNum);
	Ins.Print(message);
}