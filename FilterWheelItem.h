// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __FilterWheelItem_h
#define __FilterWheelItem_h
#include <pcl/String.h>
#include <pcl/Defs.h>
#include <pcl/MetaParameter.h>
#include "DeviceItem.h"
#include "IPixInsightFilterWheel.h"

namespace pcl
{
   class FilterWheelItem : public DeviceItem
   {
   public:
       String filterWheelName;

       FilterWheelItem( );
       FilterWheelItem( const String& fn, const String& dp);
       FilterWheelItem( const FilterWheelItem& x );

       void AddToRawData( ByteArray& ) const;
       ByteArray::const_iterator GetFromRawData( ByteArray::const_iterator );

       virtual IPixInsightFilterWheel* GetDevice() const;

   };
}

#endif
