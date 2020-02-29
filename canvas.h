#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QLabel>
#include <QVector>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

class Canvas : public QLabel
{
	Q_OBJECT
public:
	Canvas(QWidget* parent = nullptr);

	QRect getSelection() const;
	QPixmap getSelectedFragment();
protected:
	void mousePressEvent(QMouseEvent *ev) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;

	void paintEvent(QPaintEvent *) override;

private:
	QRect selection;

	bool picked;
	bool selectionActive;

	QPainterPath painterPath;
	QPen pen;
};

#endif // CANVAS_H
