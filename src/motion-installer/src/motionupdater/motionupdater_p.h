#ifndef MOTIONUPDATER_MOTIONUPDATER_P_H
#define MOTIONUPDATER_MOTIONUPDATER_P_H

#include "motionupdater.h"
#include "simplescheduler_p.h"
#include "atomfeeder.h"
#include "downloadmanager.h"

#include <QtCore/QProcess>
#include <QtCore/QLoggingCategory>
#include <QtCore/QException>

#include <exception>

namespace QtMotionUpdater
{

class MotionUpdaterPrivate : public QObject
{
public:
	MotionUpdater *q;

	QString currentVersion;
	QList<MotionUpdater::MotionUpdateInfo> updateInfos;
	bool normalExit;
	int lastErrorCode;
	QByteArray lastErrorLog;

	AtomFeeder *atomFeeder;
	int currentVersionPos;
	QString newVersion;
	DownloadManager *downloadManager;

	SimpleScheduler *scheduler;

	bool runOnExit;
	QStringList runArguments;
	QScopedPointer<AdminAuthoriser> adminAuth;

	MotionUpdaterPrivate(MotionUpdater *q_ptr);
	~MotionUpdaterPrivate();

	bool startUpdateCheck();
	void stopUpdateCheck(int delay, bool async);

	void updaterError();

public Q_SLOTS:
	void onAppAboutToExit();
	void onUpdaterReady();
	void onDownloadProgress(DownloadManager::DownloadProgress progress);
	void onDownloadFinished(DownloadManager::DownloadProgress progress);
	void onDownloadCheckSize(DownloadManager::DownloadProgress progress);

private:
	QString getDownloadUrl(QString version);
};

}

Q_DECLARE_LOGGING_CATEGORY(logMotionUpdater)

#endif // MOTIONUPDATER_MOTIONUPDATER_P_H
