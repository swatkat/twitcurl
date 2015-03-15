# How to use twitcurl library? #
twitcurl is an open-source pure C++ library for twitter REST APIs. Currently, it has support for most of the twitter v1.1 APIs and it will be updated to support all the APIs. twitcurl uses cURL library for handling HTTP requests and responses. Building applications using twitcurl is quite easy:

1) Download twitcurl library source. Build **twitcurl.lib** by using Visual C++ workspace file or Makefile depending on your platform. Refer **UNIX/Linux** and **Windows** sections down below.

2) Include these files in your twitter client app:
  * twitcurl.h
  * oauthlib.h
  * All cURL headers present in _/include/curl/_ sub-directory in cURL source

3) Static link **twitcurl.lib** in your twitter client app.
Note: Windows based twitter client applications need **libeay32.dll** and **ssleay32.dll** as well.

4) Instantiate an object of **twitCurl** class and use the twitter API wrappers that are exposed as public methods.

5) twitcurl works on all OS (Windows, Linux, Mac etc.) as it is written completely in C++ and the only dependency is cURL (which works on all OSes mentioned earlier).

Scroll down for more detailed instructions on building libtwitcurl on Linux, Mac OSX and Windows.

# OAuth Flow: #
Refer this wiki page for OAuth flow:
http://code.google.com/p/twitcurl/wiki/TwitcurlOAuthFlow



# UNIX/Linux: #
Follow these steps to build library:

1) Make sure you have g++ and dependent packages. If you don't have g++, then install it using package manager. For example, in Ubuntu this is done as follows:

`sudo apt-get install g++`

2) Install libcurl development package using package manager. For example, in Ubuntu this is done as follows:

`sudo apt-get install libcurl4-dev`

3) Install SVN client. Again, in Ubuntu this is done as follows:

`sudo apt-get install subversion`

4) Check-out libtwitcurl using this command:

`svn co http://twitcurl.googlecode.com/svn/trunk/libtwitcurl`

5) Build twitcurl library using the command **`make`**. This will generate twitcurl shared library **`libtwitcurl.so.1.0`**. On UNIX/Linux systems, this file needs to be copied (or symlinked) to **`/usr/lib/`** directory as **`libtwitcurl.so.1`** (Note: trailing _.0_ is removed).

`cp libtwitcurl.so.1.0 /usr/lib/libtwitcurl.so.1`

or

`ln -sf /path/of/libtwitcurl.so.1.0 /usr/lib/libtwitcurl.so.1`

6) Check-out example application twitterClient using the command:

`svn co http://twitcurl.googlecode.com/svn/trunk/twitterClient`

7) Build example application using the command:

`g++ twitterClient.cpp -ltwitcurl`

8) Similarly, build your applications by linking it with twitcurl library (**`-ltwitcurl`**). For example:

`g++ yourapp.cpp -ltwitcurl`

Note: If you get `ld: cannot find -ltwitcurl` linker error, then try copying (or symlinking) **`libtwitcurl.so.1.0`** as **`libtwitcurl.so`** into **`/usr/lib/`** directory.

9) To run your application, make sure that `LD_LIBRARY_PATH` environment variable contains the directory path where `libtwitcurl.so.1` is present.  If directory path is not present in `LD_LIBRARY_PATH`, then add it using command `export` command. For example:
`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib`

# Mac/OSX: #
1) You may need to install GCC command line tools for XCode if you don't already have it, as mentioned here: http://stackoverflow.com/a/11494872

2) Once GCC tools are installed, steps to build libtwitcurl and linking it to your app is almost identical to that of UNIX/Linux.

3) If you get libcurl related linker errors (example: ld: library not found for -lcurl), then you need to download and build libcurl as well. Follow steps given in "Getting started with libcurl on OSX" section, in this page: http://dahu.co.uk/blog/?p=77

Note: Once libtwitcurl dynamic library is built, it should be copied to `/usr/local/lib/` directory so that your app can link to it.

# Windows: #
Follow these steps to build twitcurl library:

1) Download twitcurl source from `http://twitcurl.googlecode.com/svn/trunk/libtwitcurl` using SVN clients like TortoiseSVN.

2) Open `twitcurl.sln` solution using Visual C++ 2008 (or later). Build the library `twitcurl.lib`.

3) Statically link `twitcurl.lib` in your application. Do not forget to include `twitcurl.h`, `oauthlib.h` and cURL headers in your application, as mentioned in `How to use twitcurl library?` section above.

4) Build your application.

5) Since cURL depends on OpenSSL, you need to copy **libeay32.dll** and **ssleay32.dll** files to the same directory where your application executable is located.

Note: **libeay32.dll** and **ssleay32.dll** can be copied from `twitterClient\Release` directory, or downloaded from http://curl.haxx.se/latest.cgi?curl=win32-ssl-devel-msvc page.

6) Check example client application `twitterClient`'s source to know more about using twitcurl library.

Note: Currently Microsoft Visual C++ 6.0 workspace (`twitcurl.dsw`) and Visual C++ 2008 solution (`twitcurl.sln`) files are provided with the twitcurl source. These workspace files can be used to compile and build twitcurl on Windows using Visual C++ (6.0 or later). If you are using any other Windows based C++ IDE, then you can create new "workspace" or "project" in your IDE and just add twitCurl source files to this new "project".