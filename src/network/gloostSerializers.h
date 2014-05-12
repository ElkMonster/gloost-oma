
/*
                       ___                            __
                      /\_ \                          /\ \__
                   __ \//\ \     ___     ___     ____\ \  _\
                 /'_ `\ \ \ \   / __`\  / __`\  /  __\\ \ \/
                /\ \ \ \ \_\ \_/\ \ \ \/\ \ \ \/\__   \\ \ \_
                \ \____ \/\____\ \____/\ \____/\/\____/ \ \__\
                 \/___/\ \/____/\/___/  \/___/  \/___/   \/__/
                   /\____/
                   \_/__/

                   OpenGL framework for fast demo programming

                             http://www.gloost.org

    This file is part of the gloost framework. You can use it in parts or as
       whole under the terms of the GPL (http://www.gnu.org/licenses/#GPL).

            gloost is being created by Felix Weißig and Stephan Beck

     Felix Weißig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



#ifndef H_GLOOST_GLOOST_SERIALIZERS
#define H_GLOOST_GLOOST_SERIALIZERS


#include <BinaryBundle.h>
#include <BinaryFile.h>





namespace gloost
{


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   creates a BinaryBundle from a generic type
  \remarks Good luck ;-)
*/

template <class inType>
BinaryBundle*
serialize(const inType& generic)
{
  return new BinaryBundle((unsigned char*)&generic, sizeof(inType));
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   unserialises a generic type from a BinaryFile
  \remarks Will advance the current read position of the binary file with sizeof(genericType)
*/

template <class Type>
bool
unserialize(Type& generic, BinaryFile& binFile)
{
  unsigned sizeOfGeneric = sizeof(Type);

  if (binFile.getBytesLeft() >= sizeOfGeneric)
  {
    memcpy((void*)&generic, binFile.getCurrent(), sizeOfGeneric);
    binFile.advanceBy(sizeOfGeneric);
    return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////


/**
  \brief   unserialises a number of bytes from a BinaryFile
  \remarks Will advance the current read position of the binary file with sizeInBytes
*/

bool
unserialize(unsigned char* destination, unsigned sizeInBytes, BinaryFile& binFile)
{
  if (binFile.getBytesLeft() >= sizeInBytes)
  {
    memcpy((void*)destination, binFile.getCurrent(), sizeInBytes);
    binFile.advanceBy(sizeInBytes);
    return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Math //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


///**
//  \brief creates a BinaryBundle from a Point3
//*/
//
//BinaryBundle*
//serialize(const Point3& object)
//{
//  return new BinaryBundle((unsigned char*)&object, sizeof(Point3));
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//
//
///**
//  \brief creates a BinaryBundle from a Vector3
//*/
//
//BinaryBundle*
//serialize(const Vector3& object)
//{
//  return new BinaryBundle((unsigned char*)&object, sizeof(Vector3)-1);
//}


///////////////////////////////////////////////////////////////////////////////


/**
//  \brief creates a BinaryBundle from a Matrix
*/

//BinaryBundle*
//serialize(const Matrix& object)
//{
//  return new BinaryBundle((unsigned char*)object.data(), sizeof(mathType)*16);
//}


///////////////////////////////////////////////////////////////////////////////














}  /// namespace gloost


#endif // H_GLOOST_GLOOST_SERIALIZERS
