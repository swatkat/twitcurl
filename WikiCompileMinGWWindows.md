# Compiling twitcurl for Windows using MinGW #

[MinGW ("Minimalist GNU for Windows")](http://www.mingw.org/) is a minimalist development environment for Windows which allows you to compile MS Windows native programs using GCC (GNU Compiler Collection) and, along with MSYS (Minimal SYStem), allows for the use of familiar BASH commands. To install MinGW (and MSYS if desired) visit the link above and download the latest MinGW/MSYS installer. For the purpose of this wiki, I will assume you have the full MSYS development environment installed along with MinGW (recommended).


## Building cURL Library: ##

The cURL library is the only dependency of twitcurl. The steps for building the cURL library using MinGW are as follows:

  1. Download cURL source from [here](http://curl.haxx.se/download.html)
  1. Extract cURL folder to directory within MinGW. For this wiki, I will assume the extracted cURL source folder is named "curl" and that you have placed it in the ~/home/username directory of your MSYS environment. Which, for most installations, should be in C:\MinGW\msys\1.0\home\username.
  1. If you then open up a MinGW shell, you should already be in ~/home/username directory. `cd` into the "curl" folder you just copied over.
  1. Now, issue command `configure`
  1. After configuration is complete, run command `make` (alternatively you can run `mingw32-make make` see FAQ [here](http://www.mingw.org/wiki/FAQ).
  1. Once `make` has finished, the cURL library has been built and is ready for you to use.
  1. Navigate into "curl" directory to retrieve the newly compiled library file(s).
  1. **Using cURL as dynamic library:** Copy from ~/home/username/curl/lib the files libcurl.dll and libcurldll.a and place them in your project directory (for this wiki, assume project directory is ~/home/username/my\_app). Place libcurl.dll in the main project directory (~/home/username/my\_app) and place libcurldll.a in ~/home/username/my\_app/lib.
  1. **Using cURL as static library:** Would assume you copy libcurl.a from ~/home/username/curl/lib into ~/home/username/my\_app/lib, but have yet to get it to work. Compiler returns lots of "`undefined reference to _imp_curl......`" errors. (Need to re-visit to complete wiki)

## Building twitcurl Library: ##

  1. Download twitcurl source from http://twitcurl.googlecode.com/svn/trunk/libtwitcurl using SVN client such as TortoiseSVN and place in "home" folder (~/home/username/libtwitcurl, remembering that Windows knows this path as C:\MinGW\msys\1.0\home\username).
  1. In MinGW shell, `cd` into libtwitcurl directory.
  1. Compile all of the twitcurl source files into object files.
`g++ -c -I. twitcurl.cpp oauthlib.cpp urlencode.cpp base64.cpp HMAC_SHA1.cpp SHA1.cpp`
  1. **Building twitcurl as static library:** Use the archive command to build twitcurl library from object files.
`ar rvs libtwitcurl.a *.o`
  1. Then, copy libtwitcurl.a into your project directory's "lib" folder ~/home/username/my\_app/lib
  1. **Building twitcurl as dynamic library:** (Need to experiment more in MinGW before including in wiki)
  1. Be sure to copy the entire "curl" folder from ~/home/username/libtwitcurl/curl and place it in the "include" folder of your project directory (~/home/username/my\_app/include/curl). This directory contains all of the cURL headers you will need.
  1. Copy necessary twitcurl headers to your project's "include" folder as well. These files are "twitcurl.h" and "oauthlib.h".

## Using twitcurl in Your Program: ##

  1. First off, for the purpose of this wiki, I am assuming your project directory (~/home/username/my\_app) looks like this (directories are in bold):
    * **lib**
      * libcurldll.a
      * libtwitcurl.a
    * **include**
      * **curl**
        * all cURL headers & files from libtwitcurl source directory (13 total)
      * twitcurl.h
      * oauthlib.h
    * my\_app.cpp
  1. Be sure to `#include <curl/curl.h>` and `#include <twitcurl.h>` in my\_app.cpp
  1. In MinGW shell, navigate (`cd`) into your project directory (~home/username/my\_app) and compile your program as follows:
`g++ my_app.cpp -I./include -L./lib -ltwitcurl -lcurldll -o my_app.exe -static-libgcc -static-libstdc++`
    * The `-static-libgcc` & `-static-libstdc++` flags are necessary to run your program outside of MinGW. If you do not wish to do so, you don't have to include them.