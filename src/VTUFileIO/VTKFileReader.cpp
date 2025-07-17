#include "VTKFileReader.h"
#include "VTUDataContainer.h" // 包含完整定义
#include <qdebug.h>

VTKFileReader::VTKFileReader(QFile* file) : m_file(file) {}

int VTKFileReader::ReadVTK() {
	if (!m_file->open(QIODevice::ReadOnly | QIODevice::Text)) {
		return ERRORTYPE_FILEREADFAILED;
	}

	QTextStream in(m_file);
	int err = ParseHeader(in);
	if (err) {
		m_file->close();
		return err;
	}

	while (!in.atEnd()) {
		QString line = in.readLine().trimmed();
		if (line.startsWith("POINTS")) {
			QStringList parts = line.split(' ', QString::SkipEmptyParts);
			if (parts.size() < 2) return ERRORTYPE_WRONGNODEDATA;

			bool ok;
			int numPoints = parts[1].toInt(&ok);
			if (!ok) return ERRORTYPE_WRONGNODEDATA;

			err = ParsePoints(in, numPoints);
			if (err) {
				m_file->close();
				return err;
			}
		}
		else if (line.startsWith("CELLS")) {
			QStringList parts = line.split(' ', QString::SkipEmptyParts);
			if (parts.size() < 2) return ERRORTYPE_WRONGELEMENTDATA;

			bool ok;
			int numCells = parts[1].toInt(&ok);
			if (!ok) return ERRORTYPE_WRONGELEMENTDATA;

			err = ParseCells(in, numCells);
			if (err) {
				m_file->close();
				return err;
			}
		}
		else if (line.startsWith("CELL_TYPES")) {
			// Skip cell types section as we use node count for determination
			QStringList parts = line.split(' ', QString::SkipEmptyParts);
			if (parts.size() < 2) continue;

			bool ok;
			int numTypes = parts[1].toInt(&ok);
			if (!ok) continue;

			for (int i = 0; i < numTypes; ++i) {
				if (in.atEnd()) break;
				in.readLine(); // Skip type lines
			}
		}
	}

	m_file->close();
	return 0;
}

VTUDataContainer& VTKFileReader::GetDataContainer() {
	return m_dataContainer;
}

int VTKFileReader::ParseHeader(QTextStream& in) {
	// Version line
	if (in.atEnd()) return ERRORTYPE_FILEREADFAILED;
	QString versionLine = in.readLine();
	if (!versionLine.startsWith("# vtk DataFile Version")) {
		return ERRORTYPE_FILEREADFAILED;
	}

	// Comment line (skip)
	if (in.atEnd()) return ERRORTYPE_FILEREADFAILED;
	in.readLine();

	// Format (only ASCII supported)
	if (in.atEnd()) return ERRORTYPE_FILEREADFAILED;
	QString format = in.readLine().trimmed();
	if (format != "ASCII") {
		return ERRORTYPE_FILEREADFAILED;
	}

	// Dataset type
	if (in.atEnd()) return ERRORTYPE_FILEREADFAILED;
	QString dataset = in.readLine().trimmed();
	if (!dataset.startsWith("DATASET UNSTRUCTURED_GRID")) {
		return ERRORTYPE_FILEREADFAILED;
	}

	return 0;
}

int VTKFileReader::ParsePoints(QTextStream& in, int numPoints) {
	for (int i = 0; i < numPoints; ++i) {
		if (in.atEnd()) return ERRORTYPE_WRONGNODEDATA;

		QString line = in.readLine().trimmed();
		QStringList coords = line.split(' ', QString::SkipEmptyParts);
		if (coords.size() < 3) return ERRORTYPE_WRONGNODEDATA;

		bool ok;
		float x = coords[0].toFloat(&ok);
		if (!ok) return ERRORTYPE_WRONGNODEDATA;

		float y = coords[1].toFloat(&ok);
		if (!ok) return ERRORTYPE_WRONGNODEDATA;

		float z = coords[2].toFloat(&ok);
		if (!ok) return ERRORTYPE_WRONGNODEDATA;

		m_dataContainer.InsertNextPoint(x, y, z);
	}
	return 0;
}

int VTKFileReader::ParseCells(QTextStream& in, int numCells) {
	for (int i = 0; i < numCells; ++i) {
		if (in.atEnd()) return ERRORTYPE_WRONGELEMENTDATA;

		QString line = in.readLine().trimmed();
		QStringList tokens = line.split(' ', QString::SkipEmptyParts);
		if (tokens.isEmpty()) continue;

		bool ok;
		int count = tokens[0].toInt(&ok);
		if (!ok || tokens.size() < count + 1) {
			return ERRORTYPE_WRONGELEMENTDATA;
		}

		// Determine element type by node count
		QString elemType;
		if (count == 2)      elemType = "B31";
		else if (count == 3) elemType = "S3";
		else if (count == 4) elemType = "S4R";
		else continue; // Skip unsupported element types

					   // Copy element connectivity
		int* conn = static_cast<int*>(malloc(count * sizeof(int)));
		if (!conn) return ERRORTYPE_MEMORYALLOCFAILED;

		for (int j = 0; j < count; ++j) {
			conn[j] = tokens[j + 1].toInt(&ok);
			if (!ok) {
				free(conn);
				return ERRORTYPE_WRONGELEMENTDATA;
			}
		}

		// Add to data container
		int err = m_dataContainer.InsertNextElement(elemType, conn);
		if (err) {
			free(conn);
			return err;
		}
	}
	return 0;
}