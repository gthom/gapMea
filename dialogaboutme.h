#ifndef DIALOGABOUTME_H
#define DIALOGABOUTME_H

#include <QDialog>

namespace Ui {
class DialogAboutMe;
}

class DialogAboutMe : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAboutMe(QWidget *parent = 0);
    ~DialogAboutMe();

private:
    Ui::DialogAboutMe *ui;
};

#endif // DIALOGABOUTME_H
