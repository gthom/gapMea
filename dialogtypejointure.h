#ifndef DIALOGTYPEJOINTURE_H
#define DIALOGTYPEJOINTURE_H

#include <QDialog>

namespace Ui {
    class DialogTypeJointure;
}
/**
 * @brief The DialogTypeJointure class
 * This dialog permit to choose relation type
 */
class DialogTypeJointure : public QDialog {
    Q_OBJECT
public:
    DialogTypeJointure(QWidget *parent = 0);
    ~DialogTypeJointure();
    Ui::DialogTypeJointure *m_ui;

protected:
    void changeEvent(QEvent *e);

private slots:
    /**
     * @brief on_comboBoxType_activated
     * @param arg1 new relation type
     */
    void on_comboBoxType_activated(const QString &arg1);
    /**
     * @brief on_pushButtonCancel_clicked
     * Nothing to do
     */
    void on_pushButtonCancel_clicked();
    /**
     * @brief on_pushButtonOk_clicked
     * Validation of changes
     */
    void on_pushButtonOk_clicked();
    /**
     * @brief onLineEditNomRelationChanged
     * @param arg1 new name of relation
     * register new name
     */
    void onLineEditNomRelationChanged(QString arg1);
};

#endif // DIALOGTYPEJOINTURE_H
