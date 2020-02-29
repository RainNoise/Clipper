#include "canvas.h"
#include <QMouseEvent>

Canvas::Canvas(QWidget* parent)
	: QLabel(parent)
	, picked(false)
	, pen(QColor(100, 150, 255))
{

}

void Canvas::mousePressEvent(QMouseEvent* ev)
{
	if (pixmap() && !pixmap()->isNull()) {
		picked = true;
		selection.setX(ev->localPos().x());
		selection.setY(ev->localPos().y());
		selection.setWidth(0);
		selection.setHeight(0);
		repaint();
	}
}

void Canvas::mouseReleaseEvent(QMouseEvent*)
{
	picked = false;
	repaint();
}

void Canvas::mouseMoveEvent(QMouseEvent* ev)
{
	if (picked) {
		selection.setWidth(ev->localPos().x() - selection.x());
		selection.setHeight(ev->localPos().y()- selection.y());
		repaint();
	}
}

QRect Canvas::getSelection() const
{
	return selection;
}

QPixmap Canvas::getSelectedFragment()
{
	return pixmap()->copy(getSelection());
}

void Canvas::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QLabel::paintEvent(event);
	QPainter painter(this);
	painterPath.clear();
	painterPath.addRect(selection);
	painter.setPen(pen);
	painter.fillPath(painterPath, QBrush(QColor(100, 150, 255, 50)));
	painter.drawPath(painterPath);
}

