#ifndef MOTIONNODECONFIGDIALOG_H
#define MOTIONNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class MotionNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class MotionNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MotionNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:28666", QString privkey="MASTERNODEPRIVKEY");
    ~MotionNodeConfigDialog();

private:
    Ui::MotionNodeConfigDialog *ui;
};

#endif // MOTIONNODECONFIGDIALOG_H
