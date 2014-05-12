
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



#ifndef H_GLOOST_BINARYBUNDLE
#define H_GLOOST_BINARYBUNDLE



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>
#include <SharedResource.h>


/// cpp includes
#include <string>



namespace gloost
{


  //  Bundle of binary data aka serialized objects

class BinaryBundle: public SharedResource
{
	public:

    // class constructor
    BinaryBundle(unsigned capacity);

    // class constructor
    BinaryBundle(const unsigned char* data, unsigned size);

    // class destructor
	  virtual ~BinaryBundle();


    // returns the capacity (in bytes)
	  unsigned getCapacity() const;

    // returns the current size (in bytes)
	  unsigned getSize() const;

    // returns the free elements left in the bundle
	  unsigned getFreeSpace() const;


	  // inserts a BinaryBundle at the current position
	  bool put(const BinaryBundle* bundle);

	  // inserts a generic buffer at the current position
	  bool put(const unsigned char* buffer, unsigned sizeInBytes);

	  // inserts single character at the current position
	  bool putChar(unsigned char character);

	  // inserts a unsigned int at the current position
	  bool putUnsigned(unsigned number);

	  // inserts a float at the current position
	  bool putFloat(float number);

	  // inserts a BinaryBundle at the current position and deletes it
	  bool putAndDelete(BinaryBundle* bundle);


	  // sets the current put position lengthInBytes back
	  void rewind(unsigned lengthInBytes = 0);



	  // returns a pointer to the first buffer element
	  unsigned char* data();

	  // returns a pointer to the first buffer element
	  const unsigned char* data() const;


    /// assignment
    const BinaryBundle& operator= (const BinaryBundle&);


    /// resize
//    void resize()


	protected:

   unsigned       _capacity;

   unsigned char* _buffer;
   unsigned char* _startPtr;
   unsigned char* _endPtr;
   unsigned char* _currentPtr;


};


} // namespace gloost


#endif // H_GLOOST_BINARYBUNDLE


