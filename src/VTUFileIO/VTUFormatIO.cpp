#include <VTUFormatIO.h>

#include <VTUDataContainer.h>

#include <qstring.h>
#include <QtXml/qxml.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qfileinfo.h>

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

int VTUFormatWriter::Write() {
	return 0;
}

VTUFormatReader::VTUFormatReader(const QString& path, VTUDataContainer* VTKData) {

}
int VTUFormatReader::Read() {
	return 0;
}