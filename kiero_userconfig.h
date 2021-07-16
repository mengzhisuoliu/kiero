#ifndef __KIERO_USERCONFIG_H__
#define __KIERO_USERCONFIG_H__

//
// Hello dear user ^.^
// Here you can configure Kiero for yourself:
// Read the comments below - they will help you with this <3
//

// 
// Below you can configure the hooks for which libraries will be included in the build.
// Just uncomment what you need.
// Hint: You can uncomment all.
//

//#define KIERO_INCLUDE_D3D7   // Includes d3d7 hook implementation
//#define KIERO_INCLUDE_D3D8   // Includes d3d8 hook implementation
//#define KIERO_INCLUDE_D3D9   // Includes d3d9 hook implementation
//#define KIERO_INCLUDE_D3D9EX // Includes d3d9ex hook implementation
//#define KIERO_INCLUDE_D3D10  // Includes d3d10 hook implementation
//#define KIERO_INCLUDE_D3D11  // Includes d3d11 hook implementation
//#define KIERO_INCLUDE_D3D12  // Includes d3d12 hook implementation
//#define KIERO_INCLUDE_OPENGL // Includes opengl hook implementation
//#define KIERO_INCLUDE_VULKAN // Includes vulkan hook implementation

//
// Below you can configure utility definitions
// 
// ---------------------------------------------------------------
// ** ATTENTION: You must really understand what you are doing! **
// ---------------------------------------------------------------
// 
// Examples:
//    1. Disabling asserts:
// #define KIERO_ASSERT(_EXPR) ((void)(_EXPR))
// 
//    2. Strings encryption:
// #define KIERO_TEXTA(_TEXT) _SXOR_A_(_TEXT)
// #define KIERO_TEXTW(_TEXT) _SXOR_W_(_TEXT)
//
//    3. STL array size calculation:
// #include <array>
// #define KIERO_ARRAYSIZE(_ARR) std::size(_ARR)
//

//#define KIERO_ASSERT(_EXPR)
//#define KIERO_TEXTA(_TEXT)
//#define KIERO_TEXTW(_TEXT)
//#define KIERO_ARRAYSIZE(_ARR)

#endif