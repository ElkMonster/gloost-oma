
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



#ifndef H_GLOOST_BINARYFILE
#define H_GLOOST_BINARYFILE



/// cpp includes
#include <string>
#include <fstream>
#include <sys/stat.h>



namespace gloost
{


  class BinaryBundle;


  //  Reads and writes binary files

class BinaryFile
{
	public:

    // class constructor
    BinaryFile();

    // class destructor
	  ~BinaryFile();


    // writes a whole buffer to a file
	  static bool write( const std::string& filename,
                       unsigned char* buffer,
                       unsigned int bufferSizeInBytes);

    // reads a buffer from file
	  static bool read(const std::string& filename,
                     unsigned char*& buffer,
                     unsigned int& bufferSizeInBytes);



    // READ METHODES

    // opens and loads a binary file for reading
    bool openAndLoad(const std::string& filename);

    // "opens" a BinaryBundle to read from
    bool openAndLoad(BinaryBundle* bundle);

    // "opens" custom binary data to read from
    bool openAndLoad(unsigned char* data, unsigned dataSizeInBytes);


    // unloads the file from RAM
    void unload();



    // returns the next word as string (words are seperated by ' ', '\t', '\n' and '\r')
    std::string readWord();

    // returns the whole line from current read position
    std::string readLine();

    // reads 1 bytes of the buffer and returns it as a unsigned char value
    unsigned char readChar8();

    // reads 4 bytes of the buffer and returns it as a int value
    int readInt32();

    // reads 4 bytes of the buffer and returns it as a float value
    float readFloat32();

    // reads numBytes bytes of the buffer
    void readVarLength(unsigned char*& buffer,
                       unsigned&      numBytes);


    // sets the current read position to the next character != ' ', '\t', '\n' or '\r'
    void seekNextWord();

    // increments the read position by numBytes
    void advanceBy(unsigned int numBytes);

    // returns the number of bytes left behind the current reading position
    unsigned getBytesLeft() const;

    // returns true if end of file is reached
    bool eof() const;

    // returns a pointer to the current position in the loaded data
    const unsigned char* getCurrent() const;



    // WRITE METHODES

    // opens a file to write data piece by piece
    bool openToWrite(const std::string& filename);

    // closes the file you wrote to
    void close();


    // writes a string to the file (length-1 byte)
    void writeString(const std::string& s);

    // writes a char to the file (1 byte)
    void writeChar8(unsigned char c);

    // writes an signed integer value to the file (4 byte)
    void writeInt32(int i);

    // writes an unsigned integer value to the file (4 byte)
    void writeUInt32(unsigned int i);

    // writes an float value to the file (4 byte)
    void writeFloat32(float f);

    // writes an array to the file
    void writeBuffer(unsigned char* buffer,
                     unsigned int   bufferSizeInByte);


	private:


    std::string    _filePath;
    unsigned char* _fileBuffer;
    unsigned int   _fileSize;

    unsigned char* _bufferStart;
    unsigned char* _currentPosition;
    unsigned char* _bufferEnd;

    bool           _deleteBufferInDestructor;

    std::ofstream* _fileToWriteTo;

};


} // namespace gloost


#endif // H_GLOOST_BINARYFILE


