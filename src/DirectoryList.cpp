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



// gloost includes
#include <DirectoryList.h>



// cpp includes
#include <stddef.h>
#include <cstdio>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <algorithm>



namespace gloost
{




DirectoryList::DirectoryList(const std::string& path):
  _entries(),
  _path(path)
{}


///////////////////////////////////////////////////////////////////////////////


///

DirectoryList::~DirectoryList()
{}


///////////////////////////////////////////////////////////////////////////////


///

size_t
DirectoryList::size() const
{
  return _entries.size();
}


///////////////////////////////////////////////////////////////////////////////


///

bool
DirectoryList::open(const char* filter)
{
  DIR *dp;
  struct dirent *ep;

  dp = opendir (_path.c_str());
  if (dp != NULL)
  {
    ep = readdir (dp);
    while (ep)
    {

      if (ep)
      {
        std::string entry(_path + "/" + ep->d_name);
        if (filter)
        {
          std::string fil(filter);
          if (string_ends_with(entry,fil))
          {
            _entries.push_back(entry);
          }
        }
        else
        {
          _entries.push_back(entry);
        }
      }

      ep = readdir (dp);

    }
    closedir (dp);
  }
  else
  {
    perror (std::string("Couldn't open the directory" + _path).c_str());
    return false;
  }

  std::sort(_entries.begin(),_entries.end());

  return true;

}


///////////////////////////////////////////////////////////////////////////////


///

std::vector<std::string>&
DirectoryList::get_entries()
{
  return _entries;
}


///////////////////////////////////////////////////////////////////////////////


///

const std::vector<std::string>&
DirectoryList::get_entries() const
{
  return _entries;
}


///////////////////////////////////////////////////////////////////////////////


/// get List begin Iterator

std::vector<std::string>::iterator
DirectoryList::getListBegin()
{
  return _entries.begin();
}


///////////////////////////////////////////////////////////////////////////////


/// get List end Iterator

std::vector<std::string>::iterator
DirectoryList::getListEnd()
{
  return _entries.end();
}


///////////////////////////////////////////////////////////////////////////////


///

bool
DirectoryList::string_ends_with(std::string s, std::string e)
{

  int index_s(s.size()-1);
  int index_e(e.size()-1);
  if (index_s < index_e)
  {
    return false;
  }
  while (index_s >= 0 && index_e >= 0)
  {

    if (s[index_s] != e[index_e])
    {
      return false;
    }

    --index_s;
    --index_e;
  }

  return true;
}


////////////////////////////////////////////////////////////////////////////////


///

/* extern */
std::ostream&
operator<< (std::ostream& os, const DirectoryList& dl)
{


  std::vector<std::string> entries = dl.get_entries();

  os << std::endl << "DirectoryList:";

  for (unsigned int i=0; i != entries.size(); ++i)
  {
    os << std::endl << "  " << entries[i];
  }

  return os;
}



}
