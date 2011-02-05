#ifndef __IPixInsightCamera_h
#define __IPixInsightCamera_h
#include <pcl/String.h>

namespace pcl
{
	class IPixInsightCamera
	{
	public:
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
	        guideNorth,
	        guideSouth,
	        guideEast,
	        guideWest
	    };
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
	    virtual bool Connected() = 0;
	    virtual int SetConnected(bool) = 0;
	    virtual bool CoolerOn() = 0;
	    virtual int SetCoolerOn(bool) = 0;
	    virtual double CoolerPower() = 0;
	    virtual String Description() = 0;
	    virtual double ElectronsPerADU() = 0;
	    virtual double FullWellCapacity() = 0;
	    virtual bool HasShutter() = 0;
	    virtual double HeatSinkTemperature() = 0;
	    virtual Array< Array<long> > ImageArray() = 0;
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
        virtual double SetCCDTemperature() = 0;
        virtual double StartX() = 0;
        virtual int SetStartX(double) = 0;
        virtual double StartY() = 0;
        virtual int SetStartY(double) = 0;

        virtual int AbortExposure() = 0;
        virtual int PulseGuide(GuideDirection) = 0;
        virtual void SetupDialog() = 0;
        virtual void StartExposure() = 0;
        virtual void StopExposure() = 0;
	};
}

#endif
