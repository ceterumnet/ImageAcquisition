ImageAcquisitionModule
 - ImageAcquisitionSettings (in progress)
    There needs to be a place to store things like F/L, Aperture, Site
    locations, Sensor characteristics, Image scale etc...this would be
    a place to centralize those data points for all of the other
    processes in the module.
    
 - ExposeImage (in progress)
   This will support the following parameters:
       cameraID (this will dispatch to the Camera object that exists
       		         in the camera settings...) <- I am rethinking this.  Perhaps this is something better left to introduce at a later stage...
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
       TODOs:
		 [x] Implement cross platform driver for devices
		 	[x] Camera
		 	[x] Filter Wheel
		 [ ] Implement Device Simulators
		 	[x] Camera
		 	[/] Filter Wheel (50%)
		 [x] Unify Current Camera logic across processes (currently there is a direct
		 		access to the pointer...not good)
		 [ ] Wire up filterWheelData as a globally shared object (similar to cameraData)
		 [ ] ExposeImage process / instance / interface
		 	[x] Duration
		 	[x] Qty
		 	[x] Camera Connection Logic
		 	[x] Threading for global execution
		 	[ ] Binning
		 	[ ] Filter selection
		 	[/] Implement FileOutputPattern stuff (75%)
		 	[ ] Fix range sliders.  Perhaps use a different UI paradigm.
		 	[x] Implement Temperature Monitoring / UI updates
		 	[ ] Implement Set Temperature
		 	[ ] Implement Frame and Focus
		 	[ ] Implement Sub Frame Exposure (should this be width height x,y or x1, x2 etc...?
		 	[ ] Add delay in between exposures
		 [ ] ImageAcquisitionSettings process / instance / interface
		 	[x] Camera Settings
		 	[x] Implement Serialized Settings Persistance for Cameras
		 	[ ] Filter Wheel Settings
		 	[ ] Implement Serialized Settings Persistance for Filter Wheels
		 	[ ] Implement Default Camera Driver ( maybe just in Windows? )
		 [x] Add thread safety for Camera Data access 
		 [ ] Implement error handling across the different user interactions
		 [ ] Expose scripting interface (make sure that the std paradigms that PI offers are 
		 		adhered to)
		 [ ] Documentation!
 		
 - ImagingSession
    I'm thinking this can drive multiple sets of ImageExposures.
    Additionally, this would be a lot like a CCD Commander where we
    can add actions as the rest of the processes are developed.

 - Autoguide
    This would be higher priority, but PHD guiding is good and
    free. (I've bumped this up the list per Vicent's feedback.)
    I'm not sure if Autoguide is a standalone process or not.  I think 
    it probably is.  But I don't think I can say that for sure at this
    point.

 - HFD/FWHM:
    A real time monitor of star quality.  It can even possibly notify
    a user based on a threshold that there is an increase in HFD
    etc...

 - SlewProcess
    This should be fairly easy to do.

 - FocusProcess
    With a HFD/FWHM function, this would be relatively easy to implement.
    VCurve plot is tricky

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


