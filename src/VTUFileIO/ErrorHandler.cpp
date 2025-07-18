#include <ErrorHandler.h>

//#include <SAMApp.h>
//#include <SAMMainWindow.h>

#include <cmdCWIP.h>
#include <qstringlist.h>
#include <qstring.h>

void ErrorHandler::ReportExportErr(int err) {
	//auto app = SAMApp::getSAMApp();
	//auto mw = app->getSAMMainWindow();

	QStringList warn;

	cmdCWIP& Ins = cmdCWIP::Instance();
	if (!err) Ins.Print("Export Finished");

	if (err & ERRORTYPE_NOTEXIST) {
		warn.append(QString("Target to export does not exist."));
	}
	if (err & ERRORTYPE_FILEREADFAILED) {
		warn.append(QString("Fail to read a file."));
	}
	if (err & ERRORTYPE_FILEWRITEFAILED) {
		warn.append(QString("Fail to write in a file."));
	}
	if (err & ERRORTYPE_WRONGNODEDATA) {
		warn.append(QString("Error occured while obtaining nodes."));
	}
	if (err & ERRORTYPE_WRONGELEMENTDATA) {
		warn.append(QString("Error occured while obtaining elements."));
	}
	if (err & ERRORTYPE_WRONGSCENE) {
		warn.append(QString("Nothing to export in current scene"));
	}
	if (err & ERRORTYPE_MEMORYALLOCFAILED) {
		warn.append(QString("Error in allocating memory"));
	}
	
	for (int i = 0; i < warn.size(); ++i) {
		Ins.Warning(warn[i]);
	}
}