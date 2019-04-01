#include "motionupdater.h"
#include "motionupdater_p.h"
#include "../updatecontroller_p.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QMap>

using namespace QtMotionUpdater;

const QStringList MotionUpdater::NormalUpdateArguments = {QStringLiteral("--updater")};
const QStringList MotionUpdater::PassiveUpdateArguments = {QStringLiteral("--updater"), QStringLiteral("skipPrompt=true")};
const QStringList MotionUpdater::HiddenUpdateArguments = {QStringLiteral("--silentUpdate")};

MotionUpdater::MotionUpdater(QObject *parent) :
	MotionUpdater("", parent)
{}

MotionUpdater::MotionUpdater(const QString &currentVersion, QObject *parent) :
	QObject(parent),
	d(new MotionUpdaterPrivate(this))
{
	d->currentVersion = currentVersion;
}

MotionUpdater::~MotionUpdater() {}

bool MotionUpdater::exitedNormally() const
{
	return d->normalExit;
}

int MotionUpdater::errorCode() const
{
	return d->lastErrorCode;
}

QByteArray MotionUpdater::errorLog() const
{
	return d->lastErrorLog;
}

bool MotionUpdater::willRunOnExit() const
{
	return d->runOnExit;
}

QString MotionUpdater::currentVersion() const
{
	return d->currentVersion;
}

bool MotionUpdater::isRunning() const
{
	return isUpdaterRunning;
}

QList<MotionUpdater::MotionUpdateInfo> MotionUpdater::updateInfo() const
{
	return d->updateInfos;
}

bool MotionUpdater::checkForUpdates()
{
	return d->startUpdateCheck();
}

void MotionUpdater::abortUpdateCheck(int maxDelay, bool async)
{
	d->stopUpdateCheck(maxDelay, async);
}

int MotionUpdater::scheduleUpdate(int delaySeconds, bool repeated)
{
	if((((qint64)delaySeconds) * 1000ll) > (qint64)INT_MAX) {
		qCWarning(logMotionUpdater) << "delaySeconds to big to be converted to msecs";
		return 0;
	}
	return d->scheduler->startSchedule(delaySeconds * 1000, repeated);
}

int MotionUpdater::scheduleUpdate(const QDateTime &when)
{
	return d->scheduler->startSchedule(when);
}

void MotionUpdater::cancelScheduledUpdate(int taskId)
{
	d->scheduler->cancelSchedule(taskId);
}

void MotionUpdater::runUpdaterOnExit(AdminAuthoriser *authoriser)
{
	runUpdaterOnExit(NormalUpdateArguments, authoriser);
}

void MotionUpdater::runUpdaterOnExit(const QStringList &arguments, AdminAuthoriser *authoriser)
{
	d->runOnExit = true;
	d->runArguments = arguments;
	d->adminAuth.reset(authoriser);
}

void MotionUpdater::cancelExitRun()
{
	d->runOnExit = false;
	d->adminAuth.reset();
}



MotionUpdater::MotionUpdateInfo::MotionUpdateInfo() :
	name(),
	version(),
	size(0ull)
{}

MotionUpdater::MotionUpdateInfo::MotionUpdateInfo(const MotionUpdater::MotionUpdateInfo &other) :
	name(other.name),
	version(other.version),
	size(other.size)
{}

MotionUpdater::MotionUpdateInfo::MotionUpdateInfo(QString name, QString version, quint64 size) :
	name(name),
	version(version),
	size(size)
{}

QDebug &operator<<(QDebug &debug, const MotionUpdater::MotionUpdateInfo &info)
{
	QDebugStateSaver state(debug);
	Q_UNUSED(state);

	debug.noquote() << QStringLiteral("{Name: \"%1\"; Version: %2; Size: %3}")
					   .arg(info.name)
					   .arg(info.version.toUtf8().constData())
					   .arg(info.size);
	return debug;
}
