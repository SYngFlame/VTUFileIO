#include <VTUFileIOCommand.h>

#include <omuArguments.h>
#include <omuMethodCall.h>

#include <cmdGCommandDeliveryRole.h>
#include <cmdKCommandDeliveryRole.h>
#include <omuArguments.h>
#include <omuMethodCall.h>
#include <omuPrimExpr.h>

#include <SAMBoolKeyword.h>
#include <cmdGCommandDeliveryRole.h>
#include <sesGSessionState.h>

void VTUFileIOCommand::CommitPrint() {
	omuArguments args;

	cmdGCommandDeliveryRole::Instance().SendCommand("import VTUFileIO");
	const sesGVpContext& context = sesGSessionState::Instance()->ConstGetVpContext();
	QString pyt = QString("mdb.models['%1'].parts['%2']").arg(context.ModelName()).arg(context.PartName());
	if (context.ModelName().isEmpty() || context.PartName().isEmpty()) return;

	omuMethodCall mc(pyt, "printAll", args);
	QString cmd;
	cmd.append(mc);
	cmdGCommandDeliveryRole::Instance().SendCommand(cmd);
	return;
}

void VTUFileIOCommand::CommitSave(const QString& path) {
	cmdGCommandDeliveryRole::Instance().SendCommand("import VTUFileIO");
	const sesGVpContext& context = sesGSessionState::Instance()->ConstGetVpContext();
	QString pyt = QString("mdb.models['%1'].parts['%2']").arg(context.ModelName()).arg(context.PartName());

	omuArguments args;
	args.Put(path);
	args.Put(context.TypeByModule());
	args.Put(context.ModelName());
	args.Put(context.PartName());

	omuMethodCall mc(pyt, "initManager", args);
	QString cmd;
	cmd.append(mc);
	cmdGCommandDeliveryRole::Instance().SendCommand(cmd);
} 