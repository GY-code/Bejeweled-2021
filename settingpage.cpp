#include"CGammaRamp.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
#include "settingpage.h"
#include "ui_settingpage.h"
#include<qpixmap.h>
#include<qfile.h>
#include <QTemporaryDir>
#include<qdesktopservices.h>
#include<qurl.h>
#include<qpainter.h>
settingpage::settingpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settingpage)
{


    ui->setupUi(this);
    QPixmap pixmap = QPixmap(":/picture/Settingpage/dialogbox.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    //去窗口边框
    this->setWindowFlags(Qt::FramelessWindowHint | this->windowFlags());
    //把窗口背景设置为透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    //以下属性默认为false，即mouseMoveEvent只有在按键按下时移动才能触发



    ui->Help->setCursor(QCursor(Qt::PointingHandCursor));
    ui->Web->setCursor(QCursor(Qt::PointingHandCursor));
    ui->Done->setCursor(QCursor(Qt::PointingHandCursor));

    ui->Help->setGeometry(140, 260, 131, 51);
    ui->Help->setStyleSheet("border-image:url(:/picture/Settingpage/dialogbutton.png)");
    connect(ui->Help, &QPushButton::pressed, [=](){
        ui->Help->setStyleSheet("border-image:url(:/picture/Settingpage/DialogButtonGlow.png)");}
    );
    connect(ui->Help, &QPushButton::released, [=](){
        ui->Help->setStyleSheet("border-image:url(:/picture/Settingpage/dialogbutton.png)"); }
    );


    ui->Web->setGeometry(460, 260, 131, 51);
    ui->Web->setStyleSheet("border-image:url(:/picture/Settingpage/dialogbutton.png)");
    connect(ui->Web, &QPushButton::pressed, [=](){
        ui->Web->setStyleSheet("border-image:url(:/picture/Settingpage/DialogButtonGlow.png)");}
    );
    connect(ui->Web, &QPushButton::released, [=](){
        ui->Web->setStyleSheet("border-image:url(:/picture/Settingpage/dialogbutton.png)"); }
    );

    ui->Done->setGeometry(300, 320, 131, 51);
    ui->Done->setStyleSheet("border-image:url(:/picture/Settingpage/dialogbutton.png)");
    connect(ui->Done, &QPushButton::pressed, [=](){
        ui->Done->setStyleSheet("border-image:url(:/picture/Settingpage/DialogButtonGlow.png)");}
    );
    connect(ui->Done, &QPushButton::released, [=](){
        ui->Done->setStyleSheet("border-image:url(:/picture/Settingpage/dialogbutton.png)"); }
    );



    slider1=new PixmapSlider();
    slider1->setParent(this);
    slider1->setGeometry(291,140,40,40);
    slider1->SetChannelImage(":/picture/Settingpage/slider-track-1.png","");
    slider1->SetThumbImage(":/picture/Settingpage/thumb.png",":/picture/Settingpage/thumb.png");
    slider1->SetRange(0, 99);
    slider1->SetPos(40,false);
    QObject::connect(slider1, SIGNAL(valueChanged(int)), this, SLOT(onVolumeValueChanged(int)));



    slider2=new PixmapSlider();
    slider2->setParent(this);
    slider2->setGeometry(291,200,40,40);
    slider2->SetChannelImage(":/picture/Settingpage/slider-track-1.png","");
    slider2->SetThumbImage(":/picture/Settingpage/thumb.png",":/picture/Settingpage/thumb.png");
    slider2->SetRange(0, 99);
    slider2->SetPos(40,false);
    QObject::connect(slider2, SIGNAL(valueChanged(int)), this, SLOT(onSpinValueChanged(int)));

}



void settingpage::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap(":/picture/Settingpage/dialogbox.png"));
}


//打开文档
void settingpage::on_Help_clicked()
{
    QFile file(":/doc/Exp.doc");
    QTemporaryDir tempDir;
    tempDir.setAutoRemove(false);
    if (tempDir.isValid()) {
        QString tempFile = tempDir.path() + "/Exp.doc";
        if (QFile::copy(":/doc/Exp.doc", tempFile)) {
            //now extracted to the filesystem
            QDesktopServices::openUrl(QUrl::fromLocalFile(tempDir.path() + "/Exp.doc"));
        }
    }
}

//获取spinbox的值
void settingpage::onSpinValueChanged(int i)
{
    int gamma = i;
    CGammaRamp GammaRamp;
    GammaRamp.SetBrightness(NULL, gamma);
}




//打开网页
void settingpage::on_Web_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://gitee.com/guyi2020/bejeweled-2021")));
}

//关闭设置界面
void settingpage::on_Done_clicked()
{
    this->setVisible(false);
}


void settingpage::onVolumeValueChanged(int i)
{
    SetVolumeLevel(i/2);
}

bool settingpage::SetVolumeLevel(int level)
{
    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator = 0;
    IMMDevice* pDevice = 0;
    IAudioEndpointVolume* pAudioEndpointVolume = 0;
    IAudioClient* pAudioClient = 0;

    try {
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
        if (FAILED(hr)) throw "CoCreateInstance";
        hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
        if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
        hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
        if (FAILED(hr)) throw "pDevice->Active";
        hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
        if (FAILED(hr)) throw "pDevice->Active";

        if (level == -2) {
            hr = pAudioEndpointVolume->SetMute(FALSE, NULL);
            if (FAILED(hr)) throw "SetMute";
        }
        else if (level == -1) {
            hr = pAudioEndpointVolume->SetMute(TRUE, NULL);
            if (FAILED(hr)) throw "SetMute";
        }
        else {
            if (level<0 || level>100) {
                hr = E_INVALIDARG;
                throw "Invalid Arg";
            }

            float fVolume;
            fVolume = level / 100.0f;
            hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume, &GUID_NULL);
            if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";

            pAudioClient->Release();
            pAudioEndpointVolume->Release();
            pDevice->Release();
            pDeviceEnumerator->Release();
            return true;
        }
    }
    catch (...) {
        if (pAudioClient) pAudioClient->Release();
        if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
        if (pDevice) pDevice->Release();
        if (pDeviceEnumerator) pDeviceEnumerator->Release();
        throw;
    }
    return false;
}



settingpage::~settingpage()
{
    delete ui;
}





