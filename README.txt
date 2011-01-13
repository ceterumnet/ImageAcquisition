
ImageAcquisitionModule

 - ExposeImageProcess (in progress)
   This will support the following parameters:
       exposureCount
       exposureDuration
       cameraConfiguration (this may be a separate process - kind of like the Global Modules, but I haven't decided yet.  Right now, I am doing a modal type of dialog that lives inside of the same code.)
          ...
       cameraTemperature
       filterIndex
       isPreviewExposure
       binningModeX
       binningModeY
       fileSavePath
       fileNamePrefix
       
       ... I am probably missing some, but you should get the general idea here...

 - ImagingSessionProcess
    I'm thinking this can drive multiple sets of ImageExposures.  Additionally, this would be a lot like a CCD Commander where we can add actions as the rest of the processes are developed.

 - ImageAcquisitionPreferences
    There needs to be a place to store things like F/L, Aperture, Site locations, Sensor characteristics, Image scale etc...this would be a place to centralize those data points for all of the other processes in the module.

 - HFD/FWHMProcess:
    A real time monitor of star quality.  It can even possibly notify a user based on a threshold that there is an increase in HFD etc...

 - AutoguideProcess
    This would be higher priority, but PHD guiding is good and free.

 - SlewProcess
    This would be really easy to do.

 - FocusProcess
    With the HFD/FWHM function, this would be relatively easy to implement

 - PlateSolveProcess
   This would be a fairly "dumb" module that could interface with the Blind Solver or PinPoint etc...

 - CurvatureMeasurementProces
   I would also like to be able to perform similar curvature maps like CCDInspector...

 - TiltMeasurementProcess
   And tilt as well...
   

All of these processes will have GUI interfaces where appropriate and instance classes.


