#ifndef ADDEDITMOTIONNODE_H
#define ADDEDITMOTIONNODE_H

#include <QDialog>

namespace Ui {
class AddEditMotionNode;
}


class AddEditMotionNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditMotionNode(QWidget *parent = 0);
    ~AddEditMotionNode();

protected:

private Q_SLOTS:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

signals:

private:
    Ui::AddEditMotionNode *ui;
};

#endif // ADDEDITMOTIONNODE_H
