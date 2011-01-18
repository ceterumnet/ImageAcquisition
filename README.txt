ImageAcquisitionModule

 - ExposeImage (in progress)
   This will support the following parameters:
       cameraID (this will dispatch to the Camera object that exists
       		         in the camera settings...)
       exposureCount
       exposureDuration
         ...
       cameraTemperature
       filterIndex
       isPreviewExposure
       binningModeX
       binningModeY
       fileSavePath
       fileNamePrefix
       
       ... I am probably missing some, but you should get the general idea here...

 - ImagingSession
    I'm thinking this can drive multiple sets of ImageExposures.
    Additionally, this would be a lot like a CCD Commander where we
    can add actions as the rest of the processes are developed.

 - Autoguide
    This would be higher priority, but PHD guiding is good and
    free. (I've bumped this up the list per Vicent's feedback.)

 - ImageAcquisitionSettings
    There needs to be a place to store things like F/L, Aperture, Site
    locations, Sensor characteristics, Image scale etc...this would be
    a place to centralize those data points for all of the other
    processes in the module.

 - HFD/FWHM:
    A real time monitor of star quality.  It can even possibly notify
    a user based on a threshold that there is an increase in HFD
    etc...

- SlewProcess
    This would be really easy to do.

 - FocusProcess
    With the HFD/FWHM function, this would be relatively easy to implement

 - PlateSolve
   This would be a fairly "dumb" module that could interface with the
   Blind Solver or PinPoint etc...

 - CurvatureMeasurement
   I would also like to be able to perform similar curvature maps like
   CCDInspector...

 - TiltMeasurement
   And tilt as well...
   

All of these processes will have GUI interfaces where appropriate and
instance classes.


