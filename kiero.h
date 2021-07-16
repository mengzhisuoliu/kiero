#ifndef __KIERO_H__
#define __KIERO_H__

//
// ** ATTENTION: This version is unfinished! **
// More information in README.md or https://github.com/Rebzzel/kiero
//

#define KIERO_VERSION "1.22.0-preview"

#ifndef KIERO_DISABLE_USERCONFIG
# include "kiero_userconfig.h"
#endif

#include <stdint.h>

#ifndef KIERO_ASSERT
# include <assert.h>
# define KIERO_ASSERT(_EXPR) assert(_EXPR)
#endif

#ifndef KIERO_TEXTA
# define KIERO_TEXTA(_TEXT) _TEXT
#endif

#ifndef KIERO_TEXTW
# define KIERO_TEXTW(_TEXT) L##_TEXT
#endif

#ifndef KIERO_ARRAYSIZE
# define KIERO_ARRAYSIZE(_ARR) ((size_t)(sizeof(_ARR) / sizeof(*(_ARR))))
#endif

namespace kiero
{
	struct Status
	{
		enum Enum
		{
			ModuleNotFoundError = -3,

			NotImplementedError = -2,

			UnknownError = -1,

			Success = 0,

			AlreadyInitialized = 1,
		};
	};

	struct RenderType
	{
		enum Enum
		{
			None,

			D3D7,
			D3D8,
			D3D9,
			D3D9Ex,
			D3D10,
			D3D11,
			D3D12,
			
			OpenGL,
			Vulkan,

			Auto,
		};
	};

	Status::Enum init(RenderType::Enum renderType);
	void shutdown();

	RenderType::Enum getRenderType();
	uintptr_t getMethodAddress(const char* alias);

	Status::Enum bind(const char* alias, void** original, void* function);
	void unbind(const char* alias);
}

#endif // __KIERO_H__