template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::loadResource(Identifier ID, const std::string & filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("Failed to load " + filename);
	insertResource(ID, std::move(resource));
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier ID, std::unique_ptr<Resource> resource)
{
	auto inserted = mResourceMap.insert(std::make_pair(ID, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource & ResourceHolder<Resource, Identifier>::getResource(Identifier ID)
{
	auto found = mResourceMap.find(ID);

	//assert(found != mResourceMap.end);

	return *found->second;
}