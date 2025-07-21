#include "VTUFileManager.h"

#include <ptoKUtils.h>
#include <ptoKPart.h> 

#include <basMdb.h>
#include <basBasis.h>
#include <basNewModel.h>
#include <omuPrimType.h>
#include <ptoKPartShortcut.h>
#include <ftrPrimaryObjShortcut.h>
#include <sesKSessionState.h>

#include <VTUContainerWriter.h>
#include <VTUContainerReader.h>
#include <VTUFormatIO.h>
#include <VTKLegacyFormatIO.h>
#include <MessageHandler.h>

#include <qfile.h>
#include <qfileinfo.h>
#include <qstring.h>

VTUFileManager::VTUFileManager() {
	writer = NULL;
	fileWriter = NULL;
	reader = NULL;
	fileReader = NULL;
}

VTUFileManager::~VTUFileManager() {
	if (writer != NULL) delete(writer);
	if (fileWriter != NULL) delete(fileWriter);
}

TargetList::TargetList() {
	targetPartID = 0;
	type = VTKLegacy;
	withOdb = false;
	displayMode = omu_NONE;
}

const ptoKPartRepository& VTUFileManager::ConstGetModelParts(const QString& model) {

	basBasis* bas = basBasis::Instance();
	basMdb mdb = bas->Fetch();

	return ptoKConstGetPartRepos(mdb, model);
}

ptoKPartRepository& VTUFileManager::GetModelParts(const QString& model) {

	basBasis* bas = basBasis::Instance();
	basMdb mdb = bas->Fetch();
	basModelMap& mdoelMap = mdb.GetModels();
	basNewModel& targetModel = mdoelMap.Get(model);
	
	return dynamic_cast<ptoKPartRepository&>(targetModel.GetPart());
}

const cowListString& VTUFileManager::GetAssemblyParts(const QString& model) {

	basBasis* bas = basBasis::Instance();
	basMdb mdb = bas->Fetch();
	const basModelMap& models = mdb.ConstGetModels();

	basNewModel cur_model = models.ConstGet(model);
	return cur_model.ConstGetInstanceTable().Keys();
}

/*
Read in mdb for extract nodes and elements and path to output VTK files
*/
void VTUFileManager::Init(const QString& path, const int& display, const QString& modelName, const QString& partName) {
	
	wcsncpy(this->target.targetPath, reinterpret_cast<const wchar_t*>(path.utf16()),path.size() + 1);
	this->target.displayMode = display;
	wcsncpy(this->target.targetModel, reinterpret_cast<const wchar_t*>(modelName.utf16()), modelName.size() + 1);
	wcsncpy(this->target.targetPart, reinterpret_cast<const wchar_t*>(partName.utf16()), partName.size() + 1);
};

void VTUFileManager::Init(const QString& path, const QString& modelName) {

	wcsncpy(this->target.targetPath, reinterpret_cast<const wchar_t*>(path.utf16()), path.size() + 1);
	wcsncpy(this->target.targetModel, reinterpret_cast<const wchar_t*>(modelName.utf16()), modelName.size() + 1);
	QString baseName = QFileInfo(path).baseName();
	wcsncpy(this->target.targetPart, reinterpret_cast<const wchar_t*>(baseName.utf16()), baseName.size() + 1);
};

int VTUFileManager::WriteCache() {
	
	writer = new VTUContainerWriter();
	switch (target.displayMode) {
		case omu_PART: {
			return writeSinglePart();
		}
		case omu_ASSEMBLY: {
			return writeAllParts();
		}
		case omu_ODB: {
			return writeODB();
		}
	}
	return ERRORTYPE_WRONG_SCENE;
}

int VTUFileManager::ReadToCache() {
	writer = new VTUContainerWriter();
	fileReader = new VTKLegacyFormatReader(target.TargetPath(), writer->GetContainerPointer());

	int status = fileReader->Read();

	MessageHandler::ReportImportInfo(fileReader->GetNodesRead(), fileReader->GetCellsRead());
	delete fileReader;

	if(status == 0) reader = new VTUContainerReader(writer->GetContainerPointer());

	return status;
}

int VTUFileManager::ReadToSAM() {
	QString targetP = target.TargetPart();
	int status = reader->ConstructNewPart(target.TargetModel(), targetP, target.targetPartID);
	//memset((void*)target.targetPart, 0, 128 * sizeof(wchar_t));
	wcsncpy(target.targetPart, reinterpret_cast<const wchar_t*>(targetP.utf16()), targetP.size() + 1);
	//reader->ReleaseMemory();
	delete reader;
	delete writer;
	writer = NULL;
	reader = NULL;
	return status;
}

int VTUFileManager::WriteFile() {

	fileWriter = new VTKLegacyFormatWriter(target.TargetPath(), writer->GetContainerPointer());

	int status = fileWriter->Write();
	
	MessageHandler::ReportExportInfo(fileWriter->GetNodesWritten(), fileWriter->GetCellsWritten());
	delete fileWriter;
	fileWriter = NULL;
	delete writer;
	writer = NULL;

	return status;
}

int VTUFileManager::writeSinglePart() {
	const ptoKPartRepository& parts = ConstGetModelParts(target.TargetModel());
	if (parts.IsEmpty())
		return ERRORTYPE_NOTEXIST;
	return writer->GetVTKPart(parts.ConstGet(target.TargetPart()));
}

int VTUFileManager::writeAllParts() {
	const ptoKPartRepository& parts = ConstGetModelParts(target.TargetModel());
	//const cowListString& assmParts = GetAssemblyParts(target.TargetModel());
	if (parts.IsEmpty())
		return ERRORTYPE_NOTEXIST;
	int status = 0;
	for (int i = 1; i <= parts.Size(); ++i) {
		//if(assmParts.FindMember(parts.GetKey(i)) != -1)
			status |= writer->GetVTKPart(parts.ConstGet(i));
	}
	return status;
}

int VTUFileManager::writeODB() {
	//FEOdb::get
	
	return writer->VTKExportODB();
}

QString TargetList::TargetModel() {
	return QString::fromWCharArray(targetModel);
}

QString TargetList::TargetPart() {
	return QString::fromWCharArray(targetPart);
}

QString TargetList::TargetPath() {
	return QString::fromWCharArray(targetPath);
}

const QString VTUFileManager::GetTargetPartName() {
	return target.TargetPart().trimmed();
}