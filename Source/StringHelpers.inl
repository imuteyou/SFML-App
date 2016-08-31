template <typename string>
std::string toString(const string &value)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}