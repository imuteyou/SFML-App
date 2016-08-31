#ifndef RESOURCEHOLDER_HPP

#define RESOURCEHOLDER_HPP


#include <memory>
#include <map>
#include <string>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void												loadResource(Identifier ID, const std::string & filename);
	void												insertResource(Identifier ID, std::unique_ptr<Resource> resource);
	Resource &											getResource(Identifier ID);


private:
	std::map<Identifier, std::unique_ptr<Resource>>		mResourceMap;
};

#include "ResourceHolder.inl"


#endif