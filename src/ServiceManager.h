/* ------------------------------------------------------------------------------
 * Copyright (c) 2008 Novell, Inc. All Rights Reserved.
 *
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may find
 * current contact information at www.novell.com.
 * ------------------------------------------------------------------------------
 */


#include <map>
#include <string>
#include "PkgService.h"

namespace zypp
{
    class RepoManager;
}

class ServiceManager
{
    public:

	typedef std::list<zypp::ServiceInfo> Services;

	ServiceManager();

	~ServiceManager();

	Services GetServices() const; 

	bool LoadServices(const zypp::RepoManager &repomgr);

	bool SaveServices(zypp::RepoManager &repomgr) const;

	bool AddService(const std::string &alias, const std::string &url);

	bool RemoveService(const std::string &alias);

	zypp::ServiceInfo GetService(const std::string &alias) const;

	bool SetService(const std::string old_alias, const zypp::ServiceInfo &srv);

	bool RefreshService(const std::string &alias, zypp::RepoManager &repomgr) const;

	void Reset();


    private:

	// alias -> PkgService
	typedef std::map<std::string, PkgService> PkgServices;

	bool _services_loaded;

	PkgServices _known_services;
};


