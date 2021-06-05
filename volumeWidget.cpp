#include"startpage.h"
#include"volumeWidget.h"
#include"CGammaRamp.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
//#include <combaseapi.h>
//#include <ks.h>
#include <QAxBase>

volumeWidget::volumeWidget(QWidget *parent) : QWidget(parent)
{
    slider=new QSlider();
    spinBox=new QSpinBox();
    qm=new QMediaPlayer();

    this->setWindowTitle("The brightness Settings");
    slider->setParent(this);
    spinBox->setParent(this);

    slider->setGeometry(50,0,200,30);
    spinBox->setGeometry(0,0,50,30);
    slider->setOrientation(Qt::Orientation::Horizontal);

    QObject::connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
    slider->setMaximum(99);
    spinBox->setParent(this);

    spinBox->setRange(0,99);
    //关联槽函数，把spinbox值传到onspinvaluechanged
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(onVolumeValueChanged(int)));
    spinBox->setValue(50);
    slider->setVisible(true);
    spinBox->setVisible(true);

}


//获取spinbox的值
void volumeWidget::onVolumeValueChanged(int i)
{
    SetVolumeLevel(i);
}

bool volumeWidget::SetVolumeLevel(int level)
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


