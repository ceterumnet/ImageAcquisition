// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions;
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __IPixInsightCamera_h
#define __IPixInsightCamera_h
#include <pcl/String.h>
#include <pcl/Vector.h>
#include <pcl/Image.h>
#include "IPixInsightDevice.h"

namespace pcl
{
    class IPixInsightCamera : public IPixInsightDevice
    {
    public:
        enum CameraType
        {
            TypeCCD,
            TypeDSLR
        };
        enum CameraStateEnum
        {
            CameraIdle,
            CameraWaiting,
            CameraExposing,
            CameraReading,
            CameraDownload,
            CameraError
        };

        enum GuideDirection
        {
            GuideNorth,
            GuideSouth,
            GuideEast,
            GuideWest
        };

        virtual void SetLogger(void(*)(String)) = 0;
        virtual short BinX() = 0;
        virtual short BinY() = 0;
        virtual int SetBinX(short) = 0;
        virtual int SetBinY(short) = 0;
        virtual CameraStateEnum CameraState() = 0;
        virtual long CameraXSize() = 0;
        virtual long CameraYSize() = 0;
        virtual bool CanAbortExposure() = 0;
        virtual bool CanAsymmetricBin() = 0;
        virtual bool CanGetCoolerPower() = 0;
        virtual bool CanPulseGuide() = 0;
        virtual bool CanSetCCDTemperature() = 0;
        virtual bool CanStopExposure() = 0;
        virtual double CCDTemperature() = 0;
        virtual bool CoolerOn() = 0;
        virtual int SetCoolerOn(bool) = 0;
        virtual double CoolerPower() = 0;

        virtual double ElectronsPerADU() = 0;
        virtual double FullWellCapacity() = 0;
        virtual bool HasShutter() = 0;
        virtual double HeatSinkTemperature() = 0;
        virtual void ImageArray(UInt16Image *theImage) = 0;
        //virtual Array< Array<long> > ImageArrayVariant() = 0;
        virtual bool ImageReady() = 0;
        virtual bool IsPulseGuiding() = 0;
        virtual String LastError() = 0;
        virtual double LastExposureDuration() = 0;
        // Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
        virtual String LastExposureStartTime() = 0;
        virtual long MaxADU() = 0;
        virtual short MaxBinX() = 0;
        virtual short MaxBinY() = 0;
        virtual long NumX() = 0;
        virtual long NumY() = 0;
        virtual int SetNumX(long) = 0;
        virtual int SetNumY(long) = 0;
        virtual double PixelSizeX() = 0;
        virtual double PixelSizeY() = 0;
        virtual int SetCCDTemperature(double) = 0;
        virtual double GetSetCCDTemperature() = 0;
        virtual long StartX() = 0;
        virtual int SetStartX(long) = 0;
        virtual long StartY() = 0;
        virtual int SetStartY(long) = 0;

        virtual int AbortExposure() = 0;
        virtual int PulseGuide(GuideDirection, long duration) = 0;
        virtual void SetupDialog() = 0;
        virtual void StartExposure(double) = 0;
        virtual void StopExposure() = 0;
        virtual bool downloadImageFromCamera(const char*  filePath)=0;
        virtual const char* getImageFileName()=0;
        virtual CameraType getCameraType()=0;
    };
}

#endif
