#ifndef PASSAGEWIDGET_H
#define PASSAGEWIDGET_H
#include<qslider.h>
#include<qspinbox.h>
#include <QWidget>
#include<qtextbrowser.h>
class brightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit brightWidget(QWidget *parent = nullptr);
    QSpinBox* spinBox;
    QSlider* slider;
signals:

public slots:
    void onSpinValueChanged(int i);

};

#endif // PASSAGEWIDGET_H
