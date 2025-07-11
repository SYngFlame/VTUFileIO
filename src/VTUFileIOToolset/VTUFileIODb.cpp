#include <VTUFileIODB.h>
#include <VTUFileIOForm.h>

#include <QValidator>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QMessageBox>

#include <omuArguments.h>
#include <omuMethodCall.h>

#include <cmdGCommandDeliveryRole.h>




VTUFileIODB::VTUFileIODB(VTUFileIOForm* form)
	:SAMDataDialog(form, tr("VTUFileIO"), OK | CANCEL)
{
	setMinimumSize(470, 250);

	/*************************Parameters*************************************/
	QGroupBox* geomGroup = new QGroupBox(tr("VTUFileIOGroupBox"));
	QDoubleValidator* doubleValidator = new QDoubleValidator(geomGroup);

	startPointEdit = new QLineEdit("0,0,0", geomGroup);
	midPointEdit = new QLineEdit("0,0,0", geomGroup);
	endPointEdit = new QLineEdit("0,0,0", geomGroup);

	QFormLayout* geomLayout = new QFormLayout(geomGroup);
	geomLayout->addRow(tr("Start (P1):"), startPointEdit);
	geomLayout->addRow(tr("Mid (P2):"), midPointEdit);
	geomLayout->addRow(tr("End (P3):"), endPointEdit);

	QVBoxLayout* paramLayout = new QVBoxLayout;
	paramLayout->addWidget(geomGroup);

	QHBoxLayout* contentLayout = new QHBoxLayout(contentArea);
	contentLayout->addLayout(paramLayout);

}

/// Destructor.
VTUFileIODB::~VTUFileIODB()
{

}


void VTUFileIODB::onCmdOk(int id)
{	
	double p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z;
	QString s, m, e; 
	s = startPointEdit->text();
	m = midPointEdit->text();
	e = endPointEdit->text();
	QStringList parts;
	parts = s.split(',');
	if (parts.isEmpty() || !(parts.size() == 3)) {
		QMessageBox::warning(NULL, "Create Curve", "Wrong start point Format",QMessageBox::Yes);
		return;
	}
	else {
		bool startPointOk =true, ok = false;
		p1x = parts[0].trimmed().toDouble(&ok);
		startPointOk &= ok;
		p1y = parts[1].trimmed().toDouble(&ok);
		startPointOk &= ok;
		p1z = parts[2].trimmed().toDouble(&ok);
		startPointOk &= ok;
		if (!startPointOk) return;
	}

	parts = m.split(',');
	if (parts.isEmpty() || !(parts.size() == 3)) {
		QMessageBox::warning(NULL, "Create Curve", "Wrong Mid point Format", QMessageBox::Yes);
		return;
	}
	else {
		bool startPointOk = true, ok = false;
		p2x = parts[0].trimmed().toDouble(&ok);
		startPointOk &= ok;
		p2y = parts[1].trimmed().toDouble(&ok);
		startPointOk &= ok;
		p2z = parts[2].trimmed().toDouble(&ok);
		startPointOk &= ok;
		if (!startPointOk) return;
	}

	parts = e.split(',');
	if (parts.isEmpty() || !(parts.size() == 3)) {
		QMessageBox::warning(NULL, "Create Curve", "Wrong End point Format", QMessageBox::Yes);
		return;
	}
	else {
		bool startPointOk = true, ok = false;
		p3x = parts[0].trimmed().toDouble(&ok);
		startPointOk &= ok;
		p3y = parts[1].trimmed().toDouble(&ok);
		startPointOk &= ok;
		p3z = parts[2].trimmed().toDouble(&ok);
		startPointOk &= ok;
		if (!startPointOk) return;
	}

	omuArguments args(9);

	args.Put(p1x);
	args.Put(p1y);
	args.Put(p1z);
	args.Put(p2x);
	args.Put(p2y);
	args.Put(p2z);
	args.Put(p3x);
	args.Put(p3y);
	args.Put(p3z);

	cmdGCommandDeliveryRole::Instance().SendCommand("import VTUFileIO");

	omuMethodCall mc("mdb.models['Model-1'].parts['Part-1']", "drawExample", args);

	QString cmd;
	cmd.append(mc);

	cmdGCommandDeliveryRole::Instance().SendCommand(cmd);

	cmdGCommandDeliveryRole::Instance().SendCommand("session.viewports['Viewport: 1'].view.fitView()");

	hide();

}





