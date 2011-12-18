project (log4cplus CXX C)
cmake_minimum_required (VERSION 2.6)
set (CMAKE_VERBOSE_MAKEFILE on)

set (log4cplus_version_major 1)
set (log4cplus_version_minor 0)
set (log4cplus_version_patch 4)
set (log4cplus_soversion 4)
set (log4cplus_postfix "")

find_package (Threads)
message (STATUS "Threads: ${CMAKE_THREAD_LIBS_INIT}")

set (log4cplus_headers
  include/log4cplus/appender.h
  include/log4cplus/config/macosx.h
  include/log4cplus/config/win32.h
  include/log4cplus/config.hxx
  include/log4cplus/configurator.h
  include/log4cplus/consoleappender.h
  include/log4cplus/fileappender.h
  include/log4cplus/fstreams.h
  include/log4cplus/helpers/appenderattachableimpl.h
  include/log4cplus/helpers/loglog.h
  include/log4cplus/helpers/logloguser.h
  include/log4cplus/helpers/pointer.h
  include/log4cplus/helpers/property.h
  include/log4cplus/helpers/sleep.h
  include/log4cplus/helpers/socket.h
  include/log4cplus/helpers/socketbuffer.h
  include/log4cplus/helpers/stringhelper.h
  include/log4cplus/helpers/syncprims.h
  include/log4cplus/helpers/thread-config.h
  include/log4cplus/helpers/threads.h
  include/log4cplus/helpers/timehelper.h
  include/log4cplus/hierarchy.h
  include/log4cplus/hierarchylocker.h
  include/log4cplus/layout.h
  include/log4cplus/logger.h
  include/log4cplus/loggingmacros.h
  include/log4cplus/loglevel.h
  include/log4cplus/ndc.h
  include/log4cplus/nteventlogappender.h
  include/log4cplus/nullappender.h
  include/log4cplus/socketappender.h
  include/log4cplus/spi/appenderattachable.h
  include/log4cplus/spi/factory.h
  include/log4cplus/spi/filter.h
  include/log4cplus/spi/loggerfactory.h
  include/log4cplus/spi/loggerimpl.h
  include/log4cplus/spi/loggingevent.h
  include/log4cplus/spi/objectregistry.h
  include/log4cplus/spi/rootlogger.h
  include/log4cplus/streams.h
  include/log4cplus/syslogappender.h
  include/log4cplus/tstring.h
  include/log4cplus/version.h
  include/log4cplus/win32debugappender.h
  include/log4cplus/win32consoleappender.h)


set (log4cplus_sources
  src/appender.cxx
  src/appenderattachableimpl.cxx
  src/configurator.cxx
  src/consoleappender.cxx
  src/factory.cxx
  src/fileappender.cxx
  src/filter.cxx
  src/global-init.cxx
  src/hierarchy.cxx
  src/hierarchylocker.cxx
  src/layout.cxx
  src/logger.cxx
  src/loggerimpl.cxx
  src/loggingevent.cxx
  src/loglevel.cxx
  src/loglog.cxx
  src/logloguser.cxx
  src/ndc.cxx
  src/nullappender.cxx
  src/objectregistry.cxx
  src/patternlayout.cxx
  src/pointer.cxx
  src/property.cxx
  src/rootlogger.cxx
  src/sleep.cxx
  src/socket.cxx
  src/socketappender.cxx
  src/socketbuffer.cxx
  src/stringhelper.cxx
  src/syncprims.cxx
  src/syslogappender.cxx
  src/threads.cxx
  src/timehelper.cxx
  src/version.cxx)

#message (STATUS "Type: ${UNIX}|${CYGWIN}|${WIN32}")

# Uncomment the following line to get locale aware string conversions.
#add_definitions (-DLOG4CPLUS_WORKING_LOCALE)

if ("${UNIX}" OR "${CYGWIN}")
  set (log4cplus_sources ${log4cplus_sources}
    src/socket-unix.cxx)
  
  file(READ include/log4cplus/config/defines.hxx.in FILE_BUFFER)
  string(REPLACE "#undef" "#cmakedefine" FILE_BUFFER "${FILE_BUFFER}")
  set(DEFINES_HXX_CMAKE ${PROJECT_BINARY_DIR}/include/log4cplus/config/defines.hxx.cmake) 
  file(WRITE ${DEFINES_HXX_CMAKE} ${FILE_BUFFER})
 
  include(CheckIncludeFiles)
  check_include_files(syslog.h LOG4CPLUS_HAVE_SYSLOG_H)
  check_include_files(netinet/in.h LOG4CPLUS_HAVE_NETINET_IN_H)
  check_include_files(sys/types.h LOG4CPLUS_HAVE_SYS_TYPES_H)
  check_include_files(sys/socket.h LOG4CPLUS_HAVE_SYS_SOCKET_H)
  check_include_files(sys/stat.h LOG4CPLUS_HAVE_SYS_STAT_H)
  check_include_files(sys/timeb.h LOG4CPLUS_HAVE_SYS_TIMEB_H)
  check_include_files(sys/time.h LOG4CPLUS_HAVE_SYS_TIME_H)
  check_include_files(time.h LOG4CPLUS_HAVE_TIME_H)
  check_include_files(netdb.h LOG4CPLUS_HAVE_NETDB_H)
  check_include_files(unistd.h LOG4CPLUS_HAVE_UNISTD_H)
  check_include_files(errno.h LOG4CPLUS_HAVE_ERRNO_H)
  check_include_files(stdarg.h LOG4CPLUS_HAVE_STDARG_H)
  check_include_files(stdio.h LOG4CPLUS_HAVE_STDIO_H)
  check_include_files(wchar.h LOG4CPLUS_HAVE_WCHAR_H)
  
  include(CheckFunctionExists)
  check_function_exists(ftime LOG4CPLUS_HAVE_FTIME)
  check_function_exists(getaddrinfo LOG4CPLUS_HAVE_GETADDRINFO)
  check_function_exists(gethostbyname_r LOG4CPLUS_HAVE_GETHOSTBYNAME_R)
  check_function_exists(getpid LOG4CPLUS_HAVE_GETPID)
  check_function_exists(gettimeofday LOG4CPLUS_HAVE_GETTIMEOFDAY)
  check_function_exists(gmtime_r LOG4CPLUS_HAVE_GMTIME_R)
  check_function_exists(htonl LOG4CPLUS_HAVE_HTONL)
  check_function_exists(htons LOG4CPLUS_HAVE_HTONS)
  check_function_exists(localtime_r LOG4CPLUS_HAVE_LOCALTIME_R)
  check_function_exists(lstat LOG4CPLUS_HAVE_LSTAT)
  check_function_exists(ntohl LOG4CPLUS_HAVE_NTOHL)
  check_function_exists(ntohs LOG4CPLUS_HAVE_NTOHS)
  check_function_exists(stat LOG4CPLUS_HAVE_STAT)
 
  #undef LOG4CPLUS_SINGLE_THREADED
  #undef LOG4CPLUS_USE_PTHREADS
  #undef LOG4CPLUS_WORKING_LOCALE
  #undef socklen_t

  if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
      set(LOG4CPLUS_DEBUGGING 1)
  endif()

  set(LOG4CPLUS_DECLSPEC_EXPORT " ")
  set(LOG4CPLUS_DECLSPEC_IMPORT " ")

  check_function_exists(__sync_add_and_fetch LOG4CPLUS_HAVE___SYNC_ADD_AND_FETCH)
  check_function_exists(__sync_sub_and_fetch LOG4CPLUS_HAVE___SYNC_SUB_AND_FETCH)
  check_function_exists(clock_gettime LOG4CPLUS_HAVE_CLOCK_GETTIME)

  set(DEFINES_HXX ${PROJECT_BINARY_DIR}/include/log4cplus/config/defines.hxx) 
  configure_file(${DEFINES_HXX_CMAKE} ${DEFINES_HXX})
  include_directories(${PROJECT_BINARY_DIR}/include)
 
elseif (WIN32)
  set (log4cplus_sources ${log4cplus_sources}
    src/socket-win32.cxx
    src/win32debugappender.cxx
    src/nteventlogappender.cxx
    src/win32consoleappender.cxx)
  set (log4cplus_headers ${log4cplus_headers}
    include/log4cplus/helpers/syncprims-win32.h)

  # Comment out the following lines if you want non-Unicode version.
  add_definitions (-DUNICODE -D_UNICODE -UMBCS -U_MBCS)
  set (log4cplus_postfix "${log4cplus_postfix}U")
  
  #add_definitions (-DLOG4CPLUS_STATIC)
  #set (log4cplus_postfix "${log4cplus_postfix}S")
endif ()

message (STATUS "Headers: ${log4cplus_headers}")
message (STATUS "Sources: ${log4cplus_sources}")

include_directories ("include")
set (log4cplus_all_sources ${log4cplus_sources} ${log4cplus_headers})

#add_library (log4cplus STATIC ${log4cplus_all_sources})
add_library (log4cplus SHARED ${log4cplus_all_sources})
target_link_libraries (log4cplus ${CMAKE_THREAD_LIBS_INIT})

set_target_properties (log4cplus PROPERTIES
  VERSION "${log4cplus_version_major}.${log4cplus_version_minor}"
  SOVERSION "${log4cplus_soversion}"
  COMPILE_FLAGS "-DINSIDE_LOG4CPLUS")
if (WIN32)
  set_target_properties (log4cplus PROPERTIES
    DEBUG_POSTFIX "${log4cplus_postfix}D"
    RELEASE_POSTFIX "${log4cplus_postfix}"
    MINSIZEREL_POSTFIX "${log4cplus_postfix}"
    RELWITHDEBINFO_POSTFIX "${log4cplus_postfix}")
  target_link_libraries (log4cplus ws2_32 advapi32)
endif ()

add_subdirectory (loggingserver)

enable_testing()
add_subdirectory (tests)
