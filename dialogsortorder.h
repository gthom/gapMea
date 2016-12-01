#ifndef DIALOGSORTORDER_H
#define DIALOGSORTORDER_H

#include <QDialog>

namespace Ui {
    class dialogSortOrder;
}

class dialogSortOrder : public QDialog {
    Q_OBJECT
public:
    dialogSortOrder(QWidget *parent = 0);
    ~dialogSortOrder();
    Ui::dialogSortOrder *m_ui;

protected:
    void changeEvent(QEvent *e);



private slots:
    void on_listWidgetChamps_currentRowChanged(int currentRow);
    void on_toolButtonDown_clicked();
    void on_toolButtonUp_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonOk_clicked();
};

#endif // DIALOGSORTORDER_H
