/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

   File:	PkgModule.cc

   Author:	Klaus Kaempf <kkaempf@suse.de>
   Maintainer:  Klaus Kaempf <kkaempf@suse.de>

   Purpose:	Access to packagemanager
		Handles Pkg::function calls from rest of YaST.
/-*/


#include <PkgModule.h>
#include "log.h"

#include <zypp/base/Logger.h>
#include <zypp/base/LogControl.h>

PkgModule* PkgModule::current_pkg = NULL;

struct YaSTZyppLogger : public zypp::base::LogControl::LineWriter
{
  virtual void writeOut( const std::string & formated_r )
  {
    // don't log empty (debug) messages  
    if (!formated_r.empty())
    {
	y2lograw((formated_r+"\n").c_str());
    }
  }
};

struct YaSTZyppFormatter : public zypp::base::LogControl::LineFormater
{
    virtual std::string format( const std::string & group_r,
	    zypp::base::logger::LogLevel    level_r,
	    const char *        file_r,
	    const char *        func_r,
	    int                 line_r,
	    const std::string & message_r )
    {
	if (get_log_debug() || level_r > zypp::base::logger::E_DBG)
	{
	    // call the default implementation
	    return zypp::base::LogControl::LineFormater::format(group_r, level_r, file_r, func_r, line_r, message_r);
	}

	// return empty string (ignore debug messages when debug is tuned off)
	return std::string();
    }

};

PkgModule* PkgModule::instance ()
{
    if (current_pkg == NULL)
    {
	y2milestone("Redirecting ZYPP log to y2log");

        boost::shared_ptr<YaSTZyppLogger> myLogger( new YaSTZyppLogger );
        zypp::base::LogControl::instance().setLineWriter( myLogger );

        boost::shared_ptr<YaSTZyppFormatter> myFormatter( new YaSTZyppFormatter );
        zypp::base::LogControl::instance().setLineFormater( myFormatter );

	current_pkg = new PkgModule ();
    }
    
    return current_pkg;
}

//-------------------------------------------------------------------
// PkgModule

PkgModule::PkgModule ()
    : PkgModuleFunctions ()
{
}

/**
 * Destructor.
 */
PkgModule::~PkgModule ()
{
}

void PkgModule::destroy()
{
    if (current_pkg != NULL)
    {
	y2debug("Deleting PkgModule object...");
	delete current_pkg;
	current_pkg = NULL;
    }
}
