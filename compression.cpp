//#ifndef NOCRYPTLIB

#include "precompiled.h"
#include "compression.h"

//#ifndef MUTINY_FRAMEWORK
//#include "cryptlib.h"
//#include "gzip.h"
//#else
#if _MSC_VER <= 1900
#include "G:\developerframework_old\Libs\Headers\cryptlib.h"
#include "G:\developerframework_old\Libs\Headers\gzip.h"
#else

#endif
//#endif

void tcp_compressor::compress(const char *data, std::uint32_t size)
{
	
}

void tcp_decompressor::decompress(const char *data, std::uint32_t size)
{
	
}

//#endif