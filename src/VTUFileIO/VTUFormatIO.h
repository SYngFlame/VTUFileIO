#ifndef VTUFORMATIO 
#define VTUFORMATIO

#include <MessageHandler.h>
#include <FormatIO.h>

class VTUDataContainer;
class QString;
class QFile;
class QTextStream;

class VTUFormatWriter : public FormatWriter {
public:
	VTUFormatWriter(const QString& path, VTUDataContainer* VTKData);
	int Write();
};

class VTUFormatReader : public FormatReader {
public:
	VTUFormatReader(const QString& path, VTUDataContainer* VTKData);
	int Read();
};

#endif //VTUFormatIO