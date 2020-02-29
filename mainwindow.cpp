#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QMessageBox>
#include <QClipboard>
#include <QKeyEvent>
#include <QWindow>
#include <QScreen>

#include <runtimeexception.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	shootScreen();
	QClipboard *clipboard = QGuiApplication::clipboard();
	QPixmap pixmap = clipboard->pixmap();


	if (!pixmap.isNull()) {
		resize(pixmap.size());
		ui->setupUi(this);
		ui->imageView->setPixmap(pixmap);
		QMainWindow::showFullScreen();
		QMessageBox::information(
					this,
					tr("Info"),
					tr("Select region and press ENTER. Press ESC to copy entire screen")
					);
	}
	else {
		QMessageBox::critical(this, tr("Error"), tr("There is no image in clipboard"));
		throw RuntimeException(1, "There is no image in clipboard");
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::event(QEvent* event)
{
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

		QPixmap imageFragment = ui->imageView->getSelectedFragment();
		QClipboard* clipboard = QGuiApplication::clipboard();

		switch (keyEvent->key())
		{
		case (Qt::Key_Enter):
		case (Qt::Key_Return):
			clipboard->setPixmap(imageFragment);
			close();
			break;

		case (Qt::Key_Escape):
			close();
			break;
		}

	}
	return QMainWindow::event(event);
}

void MainWindow::shootScreen()
{
	QScreen *screen = QGuiApplication::primaryScreen();
	if (const QWindow *window = windowHandle())
		screen = window->screen();
	if (!screen)
		return;

	QClipboard* clipboard = QGuiApplication::clipboard();

	clipboard->setPixmap(screen->grabWindow(0));
}
