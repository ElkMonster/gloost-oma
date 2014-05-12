
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
#include <BinaryFile.h>
#include <gloostHelper.h>
#include <gloostMath.h>
#include <BinaryBundle.h>



/// cpp includes
#include <string>
#include <iostream>
#include <cstring>



namespace gloost
{

/**
  \class BinaryFile

  \brief Reads and writes binary files

  \author  Felix Weiszig
  \date    Juli 2010
  \remarks ...
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor

  \remarks ...
*/

BinaryFile::BinaryFile():
    _filePath(),
    _fileBuffer(0),
    _fileSize(0),
    _bufferStart(0),
    _currentPosition(0),
    _bufferEnd(0),
    _deleteBufferInDestructor(true),
    _fileToWriteTo(0)
{

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class destructor
  \remarks ...
*/

BinaryFile::~BinaryFile()
{
  unload();
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes a whole buffer to a file
  \param   filename path to the file to write to
  \param   buffer Pointer to an array of data
  \param   bufferSizeInByte Length of buffer in Bytes
  \remarks If the file does not exist it will be created. Existing files will be
           overwriten.
  \remarks This is an example how to write a buffer:
           \code
            struct Vertex{ float x; float y; float z; };

            // generate test data
            unsigned int numVertices = 100;
            std::vector<Vertex> vertices(numVertices, Vertex());

            for (unsigned int i=0; i!=numVertices; ++i)
            {
              Vertex v;
              v.x = i; v.y = i+1; v.z = i+2;
              vertices[i] = v;
            }

            // write
            gloost::BinaryFile::write("binaryFile_test.bin",
                                      (unsigned char*) &(*vertices.begin()),
                                      sizeof(Vertex)*vertices.size());
          \endcode
*/

/*static*/
bool
BinaryFile::write(const std::string& filename,
                  unsigned char*     buffer,
                  unsigned int       bufferSizeInByte)
{
  std::cout << std::endl << "Message from BinaryFile::write(): ";
  std::cout << std::endl << "             Writing \"" << filename << "\".";
  std::cout << std::endl << "            " << bufferSizeInByte << " Bytes to write...";
  std::cout << std::endl;
  std::flush(std::cout);


  std::ofstream myFile (filename.c_str(), std::ios::out | std::ios::binary);

  if (!myFile.is_open())
  {

    std::cout << std::endl << "ERROR in BinaryFile::write(): ";
    std::cout << std::endl << "         Could NOT open file \"" << filename << "\" to write to.";
    std::cout << std::endl;

    return false;
  }

  myFile.write ((char*)buffer, bufferSizeInByte);
  myFile.close();

  return true;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   reads a whole file and fills a buffer with its content
  \param   filename Path to the file to read from
  \param   buffer Pointer of type unsigned char*. No memory has
           to be allocated befor calling read()
  \param   bufferSizeInByte Will be the length of buffer in Byte after calling
           read()
  \remarks This is an example how to read a buffer:

           \code
              std::string    filename         = "somefile.bin";
              unsigned char* buffer           = 0;
              unsigned int   bufferSizeInByte = 0;

              if (!gloost::BinaryFile::read(filename, buffer, bufferSizeInByte))
              {
                std::cout << std::endl << "ERROR: Could not read file: " << filename;
              }
              else
              {
                std::cout << std::endl << "bufferSizeInByte: " << bufferSizeInByte;

                // use buffer ...
              }
           \endcode
*/

/*static*/
bool
BinaryFile::read(const std::string& filename,
                 unsigned char*&     buffer,
                 unsigned int&       bufferSizeInByte)
{

  // estimate file size
  struct stat results;

  if (stat(filename.c_str(), &results) == 0)
  {
    bufferSizeInByte = results.st_size;

//#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_MESSAGES
//    std::cout << std::endl << "Message from BinaryFile::read(): ";
//    std::cout << std::endl << "             Reading \"" << filename << "\".";
//    std::cout << std::endl << "             " << bufferSizeInByte << " (" << bufferSizeInByte/1048576.0f << " MB)" << " Bytes to load...";
//    std::cout << std::endl;
//    std::flush(std::cout);
//#endif
  }
  else
  {

#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
    std::cout << std::endl << "ERROR in BinaryFile::read(): ";
    std::cout << std::endl << "         While reading \"" << filename << "\"...";
    std::cout << std::endl << "         Could not estimate filesize!";
    std::cout << std::endl;
    std::flush(std::cout);
#endif

    return false;
  }


  // allocate
  buffer = new unsigned char[bufferSizeInByte];


  // read file
  std::ifstream myFile (filename.c_str(), std::ios::in | std::ios::binary);

  if (!myFile.read ((char*)buffer, bufferSizeInByte))
  {

#ifndef GLOOST_SYSTEM_DISABLE_OUTPUT_ERRORS
    std::cout << std::endl << "ERROR in BinaryFile::read(): ";
    std::cout << std::endl << "         While reading \"" << filename << "\"...";
    std::cout << std::endl << "         Could not estimate filesize! Maybe the file";
    std::cout << std::endl << "         does not exist in this universe?";
    std::cout << std::endl;
    std::flush(std::cout);
#endif

    myFile.close();

    delete[] buffer;

    return false;
  }

  // close file
  myFile.close();
  return true;

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   opens and loads a binary file for reading
  \param   filename Path to the file to read from
  \remarks This loads the complete file into your Ram. Call BinaryFile::unload()
           to free the memory after use.
*/

bool
BinaryFile::openAndLoad(const std::string& filename)
{
  _filePath   = filename;
  _fileBuffer = 0;
  _fileSize   = 0;

  if (!gloost::BinaryFile::read(_filePath, _fileBuffer, _fileSize))
  {
    return false;
  }

  _bufferStart     = _fileBuffer;
  _currentPosition = _fileBuffer;
  _bufferEnd       = _fileBuffer + _fileSize;

  return true;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   "opens" a BinaryBundle to read from
  \param   bundle A gloost::BinaryBundle
  \remarks ...
*/

bool
BinaryFile::openAndLoad(BinaryBundle* bundle)
{
//  _filePath   = "BinaryBundle";
  _deleteBufferInDestructor = false;
  _fileBuffer               = bundle->data();
  _fileSize                 = bundle->getSize();

  _bufferStart     = _fileBuffer;
  _currentPosition = _fileBuffer;
  _bufferEnd       = _fileBuffer + _fileSize;

  return true;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   "opens" custom binary data to read from
  \remarks ...
*/

bool
BinaryFile::openAndLoad(unsigned char* data, unsigned dataSizeInBytes)
{
//  _filePath   = "BinaryBundle";
  _deleteBufferInDestructor = false;
  _fileBuffer               = data;
  _fileSize                 = dataSizeInBytes;

  _bufferStart     = _fileBuffer;
  _currentPosition = _fileBuffer;
  _bufferEnd       = _fileBuffer + _fileSize;

  return true;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Unloads the file from RAM
  \remarks ...
*/

void
BinaryFile::unload()
{
  if (_fileBuffer && _deleteBufferInDestructor)
  {
    _fileBuffer = _bufferStart;
	  delete[] _fileBuffer;
  }

  _fileBuffer      = 0;
  _bufferStart     = 0;
  _currentPosition = 0;
  _bufferEnd       = 0;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the next word as string
  \remarks Words are seperated by ' ' (SPACE), '\t' (TAB), '\n' and '\r'
*/

std::string
BinaryFile::readWord()
{
  unsigned char* startPos = _currentPosition;


  while (_currentPosition != _bufferEnd && (*_currentPosition) != ' '
                                        && (*_currentPosition) != '\t'
                                        && (*_currentPosition) != '\n'
                                        && (*_currentPosition) != '\r')
  {
    ++_currentPosition;
  }

  std::string word("");
  word.append( (char*)startPos, _currentPosition-startPos );
  seekNextWord();

  return word;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Returns the whole line from current read position
  \remarks Lines are seperated by '\n' and '\r'. If the read position is
           somewhere within a line, only the rest of the line will be returned
*/

std::string
BinaryFile::readLine()
{

  std::string line = "";
  unsigned char* startPos = _currentPosition;

  while (_currentPosition != _bufferEnd && (*_currentPosition) != '\n'
                                        && (*_currentPosition) != '\r')
  {
    ++_currentPosition;
  }

  line.append( (char*)startPos, _currentPosition-startPos );
  seekNextWord();

  return line;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Reads 1 bytes of the buffer and returns it as a unsigned char value
  \remarks ...
*/

unsigned char
BinaryFile::readChar8()
{
  unsigned char value = (unsigned char)(*(reinterpret_cast<unsigned char*>(_currentPosition)));
  _currentPosition += 1;

  return value;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Reads 4 bytes of the buffer and returns it as a int value
  \remarks ...
*/

int
BinaryFile::readInt32()
{
  int value = int(*(reinterpret_cast<int*>(_currentPosition)));
  _currentPosition += 4;

  return value;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Reads 4 bytes of the buffer and returns it as a float value
  \remarks ...
*/

float
BinaryFile::readFloat32()
{
  float value = float(*(reinterpret_cast<float*>(_currentPosition)));
  _currentPosition += 4;

  return value;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Reads numBytes bytes (or the rest) of the buffer
  \remarks The buffer will be allocated within this methode. The size of the Buffer
           is either numBytes or the number of bytes left in the file.
           In the second case, the argument numBytes will be changed to the number
           of bytes actually read.<br>
           Is numBytes given with 0, everything behind the current position in the
           file is read.<br>
           If end of file was allready reached, buffer will be set to 0.
*/

void
BinaryFile::readVarLength(unsigned char*& buffer,
                          unsigned&      numBytes)
{
  if (numBytes)
  {
    numBytes = min(numBytes, (unsigned) (_bufferEnd-_currentPosition) );
  }
  else
  {
    numBytes = (unsigned) (_bufferEnd-_currentPosition);
  }

  if (numBytes)
  {
    buffer = new unsigned char[numBytes];
    memcpy ( buffer, _currentPosition, numBytes);
    _currentPosition += numBytes;
    return;
  }

  buffer = 0;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Sets the current read position to the next character != ' ', '\t', '\n', '\r'
  \remarks ...
*/

void
BinaryFile::seekNextWord()
{
  while ((*_currentPosition) == ' ' || (*_currentPosition) == '\t'
                                    || (*_currentPosition) == '\n'
                                    || (*_currentPosition) == '\r')
  {
    ++_currentPosition;

    if (_currentPosition == _bufferEnd)
    {
      break;
    }
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Increments the read position by numBytes
  \remarks ...
*/

void
BinaryFile::advanceBy(unsigned int numBytes)
{
  _currentPosition += numBytes;

  if (_currentPosition > _bufferEnd)
  {
    _currentPosition = _bufferEnd;
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns the number of bytes left behind the current reading position
  \remarks ...
*/

unsigned
BinaryFile::getBytesLeft() const
{
  return _bufferEnd - _currentPosition;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   Returns true if end of file is reached
  \remarks ...
*/

bool
BinaryFile::eof() const
{
  return (_currentPosition == _bufferEnd);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   returns a pointer to the current position in the loaded data
  \remarks ...
*/

const unsigned char*
BinaryFile::getCurrent() const
{
  return _currentPosition;
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   opens a file to write data piece by piece
  \remarks ...
*/

bool
BinaryFile::openToWrite(const std::string& filename)
{
  if (_fileToWriteTo == 0)
  {
    _fileToWriteTo = new std::ofstream(filename.c_str(), std::ios::out | std::ios::binary);
  }

  if (!_fileToWriteTo->is_open())
  {

    std::cout << std::endl << "ERROR in BinaryFile::openToWrite(const std::string& filename): ";
    std::cout << std::endl << "         Could NOT open file \"" << filename << "\" to write to.";
    std::cout << std::endl;

    delete _fileToWriteTo;
    _fileToWriteTo = 0;

    return false;
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief   closes the file you wrote to
  \remarks You need to call this method only if you opened a file with
           BinaryFile::openToWrite(const std::string& filename)
*/

void
BinaryFile::close()
{
  if (_fileToWriteTo)
  {
    _fileToWriteTo->close();
    delete _fileToWriteTo;
    _fileToWriteTo = 0;
  }
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   closes the file you wrote to
  \remarks
*/


// writes a string to the file (length-1 byte)
void
BinaryFile::writeString(const std::string& string)
{
  _fileToWriteTo->write ((char*)string.c_str(), string.length());
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes a char to the file (1 byte)
  \remarks
*/

void
BinaryFile::writeChar8(unsigned char c)
{
  _fileToWriteTo->write ((char*)&c, 1);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes an signed integer value to the file (4 byte)
  \remarks
*/

void
BinaryFile::writeInt32(int i)
{
  _fileToWriteTo->write ((char*)&i, 4);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes an unsigned integer value to the file (4 byte)
  \remarks
*/

void
BinaryFile::writeUInt32(unsigned int ui)
{
  _fileToWriteTo->write ((char*)&ui, 4);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes an float value to the file (4 byte)
  \remarks
*/

void
BinaryFile::writeFloat32(float f)
{
  _fileToWriteTo->write ((char*)&f, 4);
}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief   writes an array to the file
  \remarks
*/

void
BinaryFile::writeBuffer(unsigned char* buffer,
                        unsigned int   bufferSizeInByte)
{
  _fileToWriteTo->write ((char*)buffer, bufferSizeInByte);
}


////////////////////////////////////////////////////////////////////////////////




} // namespace gloost


