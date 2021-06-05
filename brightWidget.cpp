#include"startpage.h"
#include"brightWidget.h"
#include"CGammaRamp.h"

brightWidget::brightWidget(QWidget *parent) : QWidget(parent)
{
    slider=new QSlider();
    spinBox=new QSpinBox();


    this->setWindowTitle("The brightness Settings");
    slider->setParent(this);
    spinBox->setParent(this);

    slider->setGeometry(50,0,200,30);
    spinBox->setGeometry(0,0,50,30);
    slider->setOrientation(Qt::Orientation::Horizontal);

    QObject::connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
    slider->setMaximum(200);
    spinBox->setParent(this);

    spinBox->setRange(0,200);
    //关联槽函数，把spinbox值传到onspinvaluechanged
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinValueChanged(int)));
    spinBox->setValue(90);
    slider->setVisible(true);
    spinBox->setVisible(true);

}


//获取spinbox的值
void brightWidget::onSpinValueChanged(int i)
{
    int gamma = i;
    CGammaRamp GammaRamp;
    GammaRamp.SetBrightness(NULL, gamma);
}
