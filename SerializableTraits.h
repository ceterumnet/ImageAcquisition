#ifndef __SerializableTraits_h
#define __SerializableTraits_h

namespace pcl
{
    /*
     * Adds an object t to a ByteArray stream b.
     */
    template <class T>
    inline
    void AddToRawData( ByteArray& b, const T& t )
    {
       const uint8* p = reinterpret_cast<const uint8*>( &t );
       b.Add( p, p+sizeof( t ) );
    }

    /*
     * Retrieves an object t from a ByteArray stream at the specified location i.
     * Returns an iterator located at the next position in the ByteArray stream.
     */
    template <class T>
    inline
    ByteArray::const_iterator GetFromRawData( T& t, ByteArray::const_iterator i )
    {
       t = *reinterpret_cast<const T*>( i );
       return i + sizeof( T );
    }

    /*
     * Adds the contents of a string s to a ByteArray stream b.
     */
    template <class S>
    inline
    void AddStringToRawData( ByteArray& b, const S& s )
    {
       AddToRawData( b, uint32( s.Length() ) );
       if ( !s.IsEmpty() )
          b.Add( reinterpret_cast<const uint8*>( s.Begin() ), reinterpret_cast<const uint8*>( s.End() ) );
    }

    /*
     * Loads a string's character contents from the specified location i on a ByteArray.
     * Returns an iterator located at the next position in the ByteArray stream.
     */
    template <class S>
    inline
    ByteArray::const_iterator GetStringFromRawData( S& s, ByteArray::const_iterator i )
    {
       uint32 n;
       //Read the size of the string into n
       i = GetFromRawData( n, i );
       if ( n > 0 )
       {
          s.Assign( reinterpret_cast<const typename S::char_type*>( i ), 0, n );
          i += n * sizeof( typename S::char_type );
       }
       else
          s.Clear();
       return i;
    }

    /*
     * Template instantiations for the String type.
     */

    void AddToRawData( ByteArray& b, const String& s )
    {
       AddStringToRawData( b, s );
    }

    ByteArray::const_iterator GetFromRawData( String& s, ByteArray::const_iterator i )
    {
       return GetStringFromRawData( s, i );
    }

    /*
     * Template instantiations for the IsoString type.
     */

    void AddToRawData( ByteArray& b, const IsoString& s )
    {
       AddStringToRawData( b, s );
    }

    ByteArray::const_iterator GetFromRawData( IsoString& s, ByteArray::const_iterator i )
    {
       return GetStringFromRawData( s, i );
    }
}

#endif
