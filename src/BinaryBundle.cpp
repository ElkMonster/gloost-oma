
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



/// gloost system includes
#include <BinaryBundle.h>



/// cpp includes
#include <string>
#include <iostream>



namespace gloost
{

/**
  \class   BinaryBundle

  \brief   Bundle of binary data aka serialized objects

  \author  Felix Weiszig
  \date    November 2011
  \remarks ...
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

BinaryBundle::BinaryBundle(unsigned capacity):
    SharedResource(),
    _capacity(capacity),
    _buffer(new unsigned char[capacity]),
    _startPtr(_buffer),
    _endPtr(_buffer+capacity),
    _currentPtr(_buffer)
{

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class constructor
  \remarks ...
*/

BinaryBundle::BinaryBundle(const unsigned char* buffer, unsigned size):
    SharedResource(),
    _capacity(size),
    _buffer(new unsigned char[size]),
    _startPtr(_buffer),
    _endPtr(_buffer+size),
    _currentPtr(_buffer)
{
  put(buffer, size);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Class destructor
  \remarks ...
*/

BinaryBundle::~BinaryBundle()
{
	delete[] _buffer;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the capacity (in bytes)
  \param   ...
  \remarks ...
*/

unsigned
BinaryBundle::getCapacity() const
{
	return _capacity;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the current size (in bytes)
  \param   ...
  \remarks ...
*/

unsigned
BinaryBundle::getSize() const
{
	return _currentPtr-_startPtr;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the free elements left in the bundle
  \param   ...
  \remarks ...
*/

unsigned
BinaryBundle::getFreeSpace() const
{
	return _endPtr-_currentPtr;
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   appends a BinaryBundle
  \param   ...
  \remarks returns FALSE if buffers free space is to small to accommodate the new data
*/

bool
BinaryBundle::put(const BinaryBundle* bundle)
{
  if (getFreeSpace() >= bundle->getSize())
  {
    memcpy(_currentPtr, bundle->data(), bundle->getSize());
    _currentPtr+=bundle->getSize();
    return true;
  }
  return false;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   appends a generic buffer
  \param   ...
  \remarks returns FALSE if buffers free space is to small to accommodate the new data
*/

bool
BinaryBundle::put(const unsigned char* buffer, unsigned sizeInBytes)
{
  if (getFreeSpace() >= sizeInBytes)
  {
    memcpy(_currentPtr, buffer, sizeInBytes);
    _currentPtr+=sizeInBytes;
    return true;
  }
  return false;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   appends a single character
  \param   ...
  \remarks returns FALSE if buffers free space is to small to accommodate the new data
*/

bool
BinaryBundle::putChar(unsigned char character)
{
  bool result = put((const unsigned char*)&character, 1);
  return result;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   appends a unsigned int
  \param   ...
  \remarks returns FALSE if buffers free space is to small to accommodate the new data
*/

bool
BinaryBundle::putUnsigned(unsigned number)
{
  bool result = put((const unsigned char*)&number, 4);
  return result;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   appends a unsigned int
  \param   ...
  \remarks returns FALSE if buffers free space is to small to accommodate the new data
*/

bool
BinaryBundle::putFloat(float number)
{
  bool result = put((const unsigned char*)&number, 4);
  return result;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   appends a BinaryBundle and deletes it
  \param   bundle Pointer to a BinaryBundle
  \remarks returns FALSE if buffers free space is to small to accommodate the new data
*/

bool
BinaryBundle::putAndDelete(BinaryBundle* bundle)
{
  bool result = put(bundle);
  delete bundle;
  return result;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   sets the current put position lengthInBytes back
  \remarks If lengthInBytes is empty or 0, the current put pointer will be set to the start
*/

void
BinaryBundle::rewind(unsigned lengthInBytes)
{
  if (lengthInBytes)
  {
    _currentPtr -= lengthInBytes;
    return;
  }
  _currentPtr = _startPtr;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns a pointer to the first buffer element
  \param   ...
  \remarks ...
*/

unsigned char*
BinaryBundle::data()
{
	return _startPtr;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns a const pointer to the first buffer element
  \param   ...
  \remarks ...
*/

const unsigned char*
BinaryBundle::data() const
{
	return _startPtr;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns a const pointer to the first buffer element
  \param   ...
  \remarks ...
*/

const BinaryBundle&
BinaryBundle::operator= (const BinaryBundle& bundle)
{
  if (getCapacity())
  {
    delete [] _buffer;
    _buffer = new unsigned char[bundle.getCapacity()];
    _startPtr = _buffer;
    _endPtr   = _buffer+bundle.getCapacity();
    _startPtr = _buffer;
  }
  memcpy(_startPtr, bundle._startPtr, bundle.getCapacity());

  return (*this);
}

////////////////////////////////////////////////////////////////////////////////





} // namespace gloost


