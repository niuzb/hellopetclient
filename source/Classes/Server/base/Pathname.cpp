#include <string.h>
#include "Pathname.hpp"

namespace base {

std::string const EMPTY_STR = "";

const char EXT_DELIM = '.';

const char* const FOLDER_DELIMS="/\\";

const char DEFAULT_FOLDER_DELIM ='/';

bool Pathname::IsFolderDelimiter(char ch) {
	return (NULL !=::strchr(FOLDER_DELIMS, ch));
}

Pathname::Pathname()
	: folder_delimiter_(DEFAULT_FOLDER_DELIM) {
}

Pathname::Pathname(const std::string& pathname)
	: folder_delimiter_(DEFAULT_FOLDER_DELIM) {
	SetPathname(pathname);
}

Pathname::Pathname(const std::string& folder, const std::string& filename)
	: folder_delimiter_(DEFAULT_FOLDER_DELIM) {
	SetPathname(folder, filename);
}

void Pathname::Normalize() {
	for(size_t i=0; i<folder_.length(); i++) {
		if(IsFolderDelimiter(folder_[i])) {
			folder_[i] = folder_delimiter_;
		}
	}
}

void Pathname::clear() {
	folder_.clear();
	basename_.clear();
	extension_.clear();
}

bool Pathname::empty() const {
	return folder_.empty() && basename_.empty() && extension_.empty();
}

std::string Pathname::pathname() const {
	std::string pathname(folder_);
	pathname.append(basename_);
	pathname.append(extension_);
	if(pathname.empty()) {
		pathname.push_back('.');
		pathname.push_back(folder_delimiter_);
	}
	return pathname;
}

void Pathname::SetPathname(const std::string& pathname) {
	std::string::size_type pos = pathname.find_last_of(FOLDER_DELIMS);
	if (pos != std::string::npos) {
		SetFolder(pathname.substr(0, pos+1));
		SetFileName(pathname.substr(pos+1));
	} else {
		SetFolder(EMPTY_STR);
		SetFileName(pathname);
	}
}

void Pathname::SetPathname(const std::string& folder, const std::string& filename) {
	SetFolder(folder);
	SetFileName(filename);
}

std::string Pathname::basename() const {
	return basename_;
}

bool Pathname::SetBasename(const std::string& basename) {
	if(basename.find_first_of(FOLDER_DELIMS) != std::string::npos) {
		return false;
	}
	basename_.assign(basename);
	return true;
}

std::string Pathname::folder()  const {
	return folder_;
}

std::string Pathname::folder_name() const {
	std::string::size_type pos = std::string::npos;
	if(folder_.size() >=2) {
		pos = folder_.find_last_of(FOLDER_DELIMS, folder_.length() - 2);
	}
	if (pos != std::string::npos) {
		return folder_.substr(pos+1);
	} else {
		return folder_;
	}
}

std::string Pathname::parent_folder() const {
	std::string::size_type pos = std::string::npos;
	if(folder_.size() >=2) {
		pos = folder_.find_last_of(FOLDER_DELIMS, folder_.length()-2);
	}
	if(pos!=std::string::npos) {
		return folder_.substr(0, pos+1);
	} else {
		return EMPTY_STR;
	}
}

void Pathname::SetFolder(const std::string& folder) {
	folder_.assign(folder);
	if(!folder_.empty() && !IsFolderDelimiter(folder_[folder_.length()-1])) {
		folder_.push_back(folder_delimiter_);
	}
}

std::string Pathname::extension() const {
	return extension_;
}
	
bool Pathname::SetExtension(const std::string& extension) {
	if(extension.find_first_of(FOLDER_DELIMS) != std::string::npos || extension.find_first_of(EXT_DELIM, 1) != std::string::npos) {
		return false;
	}
	extension_.assign(extension);
	if(!extension_.empty() && (extension_[0] != EXT_DELIM)) {
		extension_.insert(extension_.begin(), EXT_DELIM);
	}
	return true;
}

bool Pathname::SetFileName(const std::string& filename) {
	std::string::size_type pos = filename.rfind(EXT_DELIM);
	if((pos == std::string::npos) || (pos == 0)) {
		return SetExtension(EMPTY_STR) && SetBasename(filename);
	} else {
		return SetExtension(filename.substr(pos)) && SetBasename(filename.substr(0, pos));
	}
}


}
