
#include <lclib-c++/Dynamic.hpp>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <libloaderapi.h>
#undef WIN32_LEAN_AND_MEAN
#include <utility>

namespace lclib::dynamic {

	DynamicLibrary::DynamicLibrary(const std::filesystem::path& p) :handle{ LoadLibraryW(p.c_str()) } {}
	DynamicLibrary::~DynamicLibrary() {
		if (handle)
			FreeLibrary((HMODULE)handle);
	}
	DynamicLibrary::DynamicLibrary(DynamicLibrary&& rhs)noexcept :handle{ std::exchange(rhs.handle,nullptr) } {}
	DynamicLibrary& DynamicLibrary::operator=(DynamicLibrary rhs)noexcept {
		std::swap(handle, rhs.handle);
		return *this;
	}

	void* DynamicLibrary::find_sym(const char* sym) {
		return (void*)GetProcAddress((HMODULE)handle, sym);
	}
}