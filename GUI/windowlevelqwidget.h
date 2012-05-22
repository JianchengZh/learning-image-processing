#ifndef WINDOWLEVELQWIDGET_H
#define WINDOWLEVELQWIDGET_H

#include <QWidget>
#include "GUI/mainwindow.h"

class   MainWindow;


namespace Ui {
class WindowLevelQWidget;
}

class WindowLevelQWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WindowLevelQWidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~WindowLevelQWidget();
    
private slots:
    void on_comboBoxPresets_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::WindowLevelQWidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // WINDOWLEVELQWIDGET_H
