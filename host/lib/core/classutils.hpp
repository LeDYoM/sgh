#ifndef LIB_CLASSUTILS_HPP
#define LIB_CLASSUTILS_HPP

#define NO_COPY(ClassName) ClassName(const ClassName &) = delete; \
	ClassName &operator=(const ClassName&) = delete;

#endif
