#ifndef ERRORHANDLER
#define ERRORHANDLER

#define ERRORTYPE_NOTEXIST 0x01
#define ERRORTYPE_FILE_READ_FAILED (0x01 << 1)
#define ERRORTYPE_FILE_WRITE_FAILED (0x01 << 2)
#define ERRORTYPE_WRONG_NODE_DATA (0x01 << 3)
#define ERRORTYPE_WRONG_ELEMENT_DATA (0x01 << 4)
#define ERRORTYPE_WRONG_SCENE (0x01 << 5)
#define ERRORTYPE_MEMORY_ALLOC_FAILED (0x01 << 6)
#define ERRORTYPE_MEMORY_RELEASE_FAILED (0x01 << 7)
#define ERRORTYPE_SAM_ACTION_FAILED (0x01 << 8)
#define ERRORTYPE_COLLISION_OCCURED (0x01 << 9)
#define ERRORTYPE_FILE_READ_VERSION (0x01 << 10)
#define ERRORTYPE_FILE_READ_ASCII (0x01 << 11)
class MessageHandler {
public:

	static void ReportExportErr(int err);
	static void ReportExportInfo(int pointNum, int elemNum);
	static void ReportImportErr(int err);
	static void ReportImportInfo(int pointNum, int elemNum);
};

#endif  ERRORHANDLER