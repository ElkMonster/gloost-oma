
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

            gloost is being created by Felix Weiﬂig and Stephan Beck

     Felix Weiﬂig (thesleeper@gmx.net), Stephan Beck (stephan@pixelstars.de)
*/



#ifndef GLOOST_DIRECTORY_H
#define GLOOST_DIRECTORY_H



// cpp includes
#include <string>
#include <vector>



namespace gloost
{

  /// reads a directory and provides a vector with the content as string

class DirectoryList
{


public:

  DirectoryList(const std::string& path);
  ~DirectoryList();

  size_t size() const;
  bool   open(const char* filter = 0);

  std::vector<std::string>&       get_entries();
  const std::vector<std::string>& get_entries() const;

  /// get List Iterators
  std::vector<std::string>::iterator getListBegin();
  std::vector<std::string>::iterator getListEnd();

private:

  bool string_ends_with(std::string s, std::string e);

  std::vector<std::string> _entries;
  std::string              _path;
};



/// ostream operator
extern std::ostream& operator<< (std::ostream&, const DirectoryList&);

}



#endif // #ifndef  GLOOST_DIRECTORY_H

