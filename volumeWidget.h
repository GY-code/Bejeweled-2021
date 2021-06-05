#pragma once

#include<qmediaplayer.h>
#include<qslider.h>
#include<qspinbox.h>
#include <QWidget>
#include<qtextbrowser.h>
class volumeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit volumeWidget(QWidget *parent = nullptr);
    QSpinBox* spinBox;
    QSlider* slider;
    QMediaPlayer* qm;
    bool setSysVolume(int level);
    int sysVolume();
    bool SetVolumeLevel(int level);
signals:

public slots:
    void onVolumeValueChanged(int i);


};

