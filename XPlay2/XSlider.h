#pragma once

#include <QSlider>
#include<QMouseEvent>
class XSlider : public QSlider
{
	Q_OBJECT

public:
	XSlider(QWidget *parent = NULL);
	~XSlider();


	void mousePressEvent(QMouseEvent* e);
	//void mouseReleaseEvent(QMouseEvent* event);
};
