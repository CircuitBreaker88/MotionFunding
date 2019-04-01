#ifndef QTMOTIONUPDATER_ADMINAUTHORIZATION_P_H
#define QTMOTIONUPDATER_ADMINAUTHORIZATION_P_H

#include "motionupdater/adminauthoriser.h"

namespace QtMotionUpdater
{

class AdminAuthorization : public AdminAuthoriser
{
public:
	bool hasAdminRights() override;
	bool executeAsAdmin(const QString &program, const QStringList &arguments) override;
};

}

#endif // QTMOTIONUPDATER_ADMINAUTHORIZATION_P_H
