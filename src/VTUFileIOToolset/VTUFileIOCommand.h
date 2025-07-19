#include <QtCore>

class VTUFileIOToolsetGui;

class VTUFileIOCommand {
public:
	static void CommitPrint();
	static void CommitSave(const QString& path);
	static void CommitOpen(const QString& path);
	static void CommitLoad();
};