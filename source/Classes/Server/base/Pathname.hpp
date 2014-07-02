#ifndef PATHNAME_HPP_
#define PATHNAME_HPP_

#include <string>

namespace base {

class Pathname {
public:
	static bool IsFolderDelimiter(char ch);

	Pathname();

	Pathname(const std::string& pathname);
	
	Pathname(const std::string& folder, const std::string& filename);
	
	void Normalize();

	void clear();

	bool empty() const;

	std::string pathname() const;

	char folder_delimiter() const {return folder_delimiter_;}

	void SetPathname(const std::string& pathname);

	void SetPathname(const std::string& folder, const std::string& filename);
	
	bool SetFileName(const std::string& filename);

	std::string folder() const;

	std::string folder_name() const;

	std::string parent_folder() const;

	void SetFolder(const std::string& folder);

	std::string basename() const;

	bool SetBasename(const std::string& basename);

	std::string extension() const;

	bool SetExtension(const std::string& extension);

private:
	std::string folder_, basename_, extension_;	
	char folder_delimiter_;
};


}

#endif
