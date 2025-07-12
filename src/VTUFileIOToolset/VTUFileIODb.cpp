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

	QFormLayout* geomLayout = new QFormLayout(geomGroup);

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
	omuArguments args;

	cmdGCommandDeliveryRole::Instance().SendCommand("import VTUFileIO");

	omuMethodCall mc("mdb.models['Model-1'].parts['Part-1']", "printAll", args);

	QString cmd;
	cmd.append(mc);

	cmdGCommandDeliveryRole::Instance().SendCommand(cmd);

	cmdGCommandDeliveryRole::Instance().SendCommand("session.viewports['Viewport: 1'].view.fitView()");

	this->deleteLater();

}





