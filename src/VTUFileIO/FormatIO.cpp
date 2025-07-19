#include <FormatIO.h>

#include <VTUDataContainer.h>

#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qfileinfo.h>

FormatWriter::FormatWriter() {
	currentState = NotInitialized;
	nodesWritten = 0;
	cellsWritten = 0;
}

FormatWriter::~FormatWriter() {
	if (file != NULL) {
		file->close();
		delete(file);
	}
	if(stream != NULL) delete(stream);
}

int FormatWriter::Write() {
	return 0;
}

FormatWriter::State FormatWriter::GetCurrentState() const {
	return currentState;
}

int FormatWriter::GetNodesWritten() const {
	return nodesWritten;
}

int FormatWriter::GetCellsWritten() const {
	return cellsWritten;
}

FormatReader::FormatReader() {
	status = 0;
	nodesRead = 0;
	cellsRead = 0;
}

FormatReader::~FormatReader() {
	if (file != NULL) {
		file->close();
		delete(file);
	}
	if (stream != NULL) delete(stream);
}

int FormatReader::Read() {
	return 0;
}

int FormatReader::GetNodesRead() const {
	return nodesRead;
}

int FormatReader::GetCellsRead() const {
	return cellsRead;
}