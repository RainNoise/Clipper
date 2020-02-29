#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	virtual bool event(QEvent *event) override;
protected:

private:
	Ui::MainWindow *ui;
	QImage image;
	void shootScreen();
};
#endif // MAINWINDOW_H
