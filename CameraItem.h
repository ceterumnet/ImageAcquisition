// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __CameraItem_h
#define __CameraItem_h
#include <pcl/String.h>
#include <pcl/Defs.h>
#include <pcl/MetaParameter.h>
#include "DeviceItem.h"
#include "IPixInsightCamera.h"

namespace pcl
{
   class CameraItem : public DeviceItem
   {
   public:
       String cameraName;

       CameraItem( );
       CameraItem( const String& cn, const String& dp);
       CameraItem( const CameraItem& x );

       void AddToRawData( ByteArray& ) const;
       ByteArray::const_iterator GetFromRawData( ByteArray::const_iterator );

       virtual IPixInsightCamera* GetDevice() const;
   };
}

#endif
