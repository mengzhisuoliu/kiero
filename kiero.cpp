#include <Windows.h>
#include <unordered_map>
#include "kiero.h"

#ifdef UNICODE
# define KIERO_TEXT(_TEXT) KIERO_TEXTW(_TEXT)
#else
# define KIERO_TEXT(_TEXT) KIERO_TEXTA(_TEXT)
#endif

#define KIERO_DIRECTX_BUILD 0

#if defined(KIERO_INCLUDE_D3D7 ) || defined(KIERO_INCLUDE_D3D8  ) || \
    defined(KIERO_INCLUDE_D3D9 ) || defined(KIERO_INCLUDE_D3D9EX) || \
    defined(KIERO_INCLUDE_D3D10) || defined(KIERO_INCLUDE_D3D11 ) || defined(KIERO_INCLUDE_D3D12)
# undef KIERO_DIRECTX_BUILD
# define KIERO_DIRECTX_BUILD 1
# include <d3d.h>
#endif

static kiero::RenderType::Enum g_renderType = kiero::RenderType::None;
static std::unordered_map<const char*, uintptr_t> g_methodsMap = {};
static HMODULE g_autoImportLib = NULL;

namespace kiero 
{
	namespace kitchen 
	{
#if KIERO_DIRECTX_BUILD
		struct DirectXWindow
		{
			WNDCLASSEX clazz;
			HWND handle;

			DirectXWindow()
			{
				clazz.cbSize = sizeof(WNDCLASSEX);
				clazz.style = CS_HREDRAW | CS_VREDRAW;
				clazz.lpfnWndProc = DefWindowProc;
				clazz.cbClsExtra = 0;
				clazz.cbWndExtra = 0;
				clazz.hInstance = ::GetModuleHandle(NULL);
				clazz.hIcon = NULL;
				clazz.hCursor = NULL;
				clazz.hbrBackground = NULL;
				clazz.lpszMenuName = NULL;
				clazz.lpszClassName = KIERO_TEXT("Kiero");
				clazz.hIconSm = NULL;

				::RegisterClassEx(&clazz);

				handle = ::CreateWindow(
					clazz.lpszClassName,
					KIERO_TEXT("Kiero DirectX Window"),
					WS_OVERLAPPEDWINDOW,
					0, 0, 100, 100, NULL, NULL,
					clazz.hInstance,
					NULL
				);
			}

			~DirectXWindow()
			{
				::DestroyWindow(handle);
				::UnregisterClass(clazz.lpszClassName, clazz.hInstance);
			}
		};

		struct DirectXObjectPtr
		{
			void* instance;

			DirectXObjectPtr()
				: instance(NULL)
			{
			}

			~DirectXObjectPtr()
			{
				if (instance != NULL)
				{
					((IUnknown*)instance)->Release();
					instance = NULL;
				}
			}
		};

# ifdef KIERO_INCLUDE_D3D7
		namespace d3d7
		{
			static const char* s_methodsTable[] = 
			{ 
				"**NOT IMPLEMENTED**" 
			};
		}
# endif
# ifdef KIERO_INCLUDE_D3D8
		namespace d3d8
		{
			static const char* s_methodsTable[] =
			{
				"IDirect3DDevice8::QueryInterface",
				"IDirect3DDevice8::AddRef",
				"IDirect3DDevice8::Release",
				"IDirect3DDevice8::TestCooperativeLevel",
				"IDirect3DDevice8::GetAvailableTextureMem",
				"IDirect3DDevice8::ResourceManagerDiscardBytes",
				"IDirect3DDevice8::GetDirect3D",
				"IDirect3DDevice8::GetDeviceCaps",
				"IDirect3DDevice8::GetDisplayMode",
				"IDirect3DDevice8::GetCreationParameters",
				"IDirect3DDevice8::SetCursorProperties",
				"IDirect3DDevice8::SetCursorPosition",
				"IDirect3DDevice8::ShowCursor",
				"IDirect3DDevice8::CreateAdditionalSwapChain",
				"IDirect3DDevice8::Reset",
				"IDirect3DDevice8::Present",
				"IDirect3DDevice8::GetBackBuffer",
				"IDirect3DDevice8::GetRasterStatus",
				"IDirect3DDevice8::SetGammaRamp",
				"IDirect3DDevice8::GetGammaRamp",
				"IDirect3DDevice8::CreateTexture",
				"IDirect3DDevice8::CreateVolumeTexture",
				"IDirect3DDevice8::CreateCubeTexture",
				"IDirect3DDevice8::CreateVertexBuffer",
				"IDirect3DDevice8::CreateIndexBuffer",
				"IDirect3DDevice8::CreateRenderTarget",
				"IDirect3DDevice8::CreateDepthStencilSurface",
				"IDirect3DDevice8::CreateImageSurface",
				"IDirect3DDevice8::CopyRects",
				"IDirect3DDevice8::UpdateTexture",
				"IDirect3DDevice8::GetFrontBuffer",
				"IDirect3DDevice8::SetRenderTarget",
				"IDirect3DDevice8::GetRenderTarget",
				"IDirect3DDevice8::GetDepthStencilSurface",
				"IDirect3DDevice8::BeginScene",
				"IDirect3DDevice8::EndScene",
				"IDirect3DDevice8::Clear",
				"IDirect3DDevice8::SetTransform",
				"IDirect3DDevice8::GetTransform",
				"IDirect3DDevice8::MultiplyTransform",
				"IDirect3DDevice8::SetViewport",
				"IDirect3DDevice8::GetViewport",
				"IDirect3DDevice8::SetMaterial",
				"IDirect3DDevice8::GetMaterial",
				"IDirect3DDevice8::SetLight",
				"IDirect3DDevice8::GetLight",
				"IDirect3DDevice8::LightEnable",
				"IDirect3DDevice8::GetLightEnable",
				"IDirect3DDevice8::SetClipPlane",
				"IDirect3DDevice8::GetClipPlane",
				"IDirect3DDevice8::SetRenderState",
				"IDirect3DDevice8::GetRenderState",
				"IDirect3DDevice8::BeginStateBlock",
				"IDirect3DDevice8::EndStateBlock",
				"IDirect3DDevice8::ApplyStateBlock",
				"IDirect3DDevice8::CaptureStateBlock",
				"IDirect3DDevice8::DeleteStateBlock",
				"IDirect3DDevice8::CreateStateBlock",
				"IDirect3DDevice8::SetClipStatus",
				"IDirect3DDevice8::GetClipStatus",
				"IDirect3DDevice8::GetTexture",
				"IDirect3DDevice8::SetTexture",
				"IDirect3DDevice8::GetTextureStageState",
				"IDirect3DDevice8::SetTextureStageState",
				"IDirect3DDevice8::ValidateDevice",
				"IDirect3DDevice8::GetInfo",
				"IDirect3DDevice8::SetPaletteEntries",
				"IDirect3DDevice8::GetPaletteEntries",
				"IDirect3DDevice8::SetCurrentTexturePalette",
				"IDirect3DDevice8::GetCurrentTexturePalette",
				"IDirect3DDevice8::DrawPrimitive",
				"IDirect3DDevice8::DrawIndexedPrimitive",
				"IDirect3DDevice8::DrawPrimitiveUP",
				"IDirect3DDevice8::DrawIndexedPrimitiveUP",
				"IDirect3DDevice8::ProcessVertices",
				"IDirect3DDevice8::CreateVertexShader",
				"IDirect3DDevice8::SetVertexShader",
				"IDirect3DDevice8::GetVertexShader",
				"IDirect3DDevice8::DeleteVertexShader",
				"IDirect3DDevice8::SetVertexShaderConstant",
				"IDirect3DDevice8::GetVertexShaderConstant",
				"IDirect3DDevice8::GetVertexShaderDeclaration",
				"IDirect3DDevice8::GetVertexShaderFunction",
				"IDirect3DDevice8::SetStreamSource",
				"IDirect3DDevice8::GetStreamSource",
				"IDirect3DDevice8::SetIndices",
				"IDirect3DDevice8::GetIndices",
				"IDirect3DDevice8::CreatePixelShader",
				"IDirect3DDevice8::SetPixelShader",
				"IDirect3DDevice8::GetPixelShader",
				"IDirect3DDevice8::DeletePixelShader",
				"IDirect3DDevice8::SetPixelShaderConstant",
				"IDirect3DDevice8::GetPixelShaderConstant",
				"IDirect3DDevice8::GetPixelShaderFunction",
				"IDirect3DDevice8::DrawRectPatch",
				"IDirect3DDevice8::DrawTriPatch",
				"IDirect3DDevice8::DeletePatch"
			};

			struct D3DPRESENT_PARAMETERS
			{
				UINT BackBufferWidth;
				UINT BackBufferHeight;
				UINT BackBufferFormat;
				UINT BackBufferCount;
				UINT MultiSampleType;
				UINT SwapEffect;
				HWND hDeviceWindow;
				BOOL Windowed;
				BOOL EnableAutoDepthStencil;
				UINT AutoDepthStencilFormat;
				DWORD Flags;
				UINT FullScreen_RefreshRateInHz;
				UINT FullScreen_PresentationInterval;
			};
		}
# endif
# if defined(KIERO_INCLUDE_D3D9) || defined(KIERO_INCLUDE_D3D9EX)
		namespace d3d9
		{
			static const char* s_methodsTable[] =
			{
				"IDirect3DDevice9::QueryInterface",
				"IDirect3DDevice9::AddRef",
				"IDirect3DDevice9::Release",
				"IDirect3DDevice9::TestCooperativeLevel",
				"IDirect3DDevice9::GetAvailableTextureMem",
				"IDirect3DDevice9::EvictManagedResources",
				"IDirect3DDevice9::GetDirect3D",
				"IDirect3DDevice9::GetDeviceCaps",
				"IDirect3DDevice9::GetDisplayMode",
				"IDirect3DDevice9::GetCreationParameters",
				"IDirect3DDevice9::SetCursorProperties",
				"IDirect3DDevice9::SetCursorPosition",
				"IDirect3DDevice9::ShowCursor",
				"IDirect3DDevice9::CreateAdditionalSwapChain",
				"IDirect3DDevice9::GetSwapChain",
				"IDirect3DDevice9::GetNumberOfSwapChains",
				"IDirect3DDevice9::Reset",
				"IDirect3DDevice9::Present",
				"IDirect3DDevice9::GetBackBuffer",
				"IDirect3DDevice9::GetRasterStatus",
				"IDirect3DDevice9::SetDialogBoxMode",
				"IDirect3DDevice9::SetGammaRamp",
				"IDirect3DDevice9::GetGammaRamp",
				"IDirect3DDevice9::CreateTexture",
				"IDirect3DDevice9::CreateVolumeTexture",
				"IDirect3DDevice9::CreateCubeTexture",
				"IDirect3DDevice9::CreateVertexBuffer",
				"IDirect3DDevice9::CreateIndexBuffer",
				"IDirect3DDevice9::CreateRenderTarget",
				"IDirect3DDevice9::CreateDepthStencilSurface",
				"IDirect3DDevice9::UpdateSurface",
				"IDirect3DDevice9::UpdateTexture",
				"IDirect3DDevice9::GetRenderTargetData",
				"IDirect3DDevice9::GetFrontBufferData",
				"IDirect3DDevice9::StretchRect",
				"IDirect3DDevice9::ColorFill",
				"IDirect3DDevice9::CreateOffscreenPlainSurface",
				"IDirect3DDevice9::SetRenderTarget",
				"IDirect3DDevice9::GetRenderTarget",
				"IDirect3DDevice9::SetDepthStencilSurface",
				"IDirect3DDevice9::GetDepthStencilSurface",
				"IDirect3DDevice9::BeginScene",
				"IDirect3DDevice9::EndScene",
				"IDirect3DDevice9::Clear",
				"IDirect3DDevice9::SetTransform",
				"IDirect3DDevice9::GetTransform",
				"IDirect3DDevice9::MultiplyTransform",
				"IDirect3DDevice9::SetViewport",
				"IDirect3DDevice9::GetViewport",
				"IDirect3DDevice9::SetMaterial",
				"IDirect3DDevice9::GetMaterial",
				"IDirect3DDevice9::SetLight",
				"IDirect3DDevice9::GetLight",
				"IDirect3DDevice9::LightEnable",
				"IDirect3DDevice9::GetLightEnable",
				"IDirect3DDevice9::SetClipPlane",
				"IDirect3DDevice9::GetClipPlane",
				"IDirect3DDevice9::SetRenderState",
				"IDirect3DDevice9::GetRenderState",
				"IDirect3DDevice9::CreateStateBlock",
				"IDirect3DDevice9::BeginStateBlock",
				"IDirect3DDevice9::EndStateBlock",
				"IDirect3DDevice9::SetClipStatus",
				"IDirect3DDevice9::GetClipStatus",
				"IDirect3DDevice9::GetTexture",
				"IDirect3DDevice9::SetTexture",
				"IDirect3DDevice9::GetTextureStageState",
				"IDirect3DDevice9::SetTextureStageState",
				"IDirect3DDevice9::GetSamplerState",
				"IDirect3DDevice9::SetSamplerState",
				"IDirect3DDevice9::ValidateDevice",
				"IDirect3DDevice9::SetPaletteEntries",
				"IDirect3DDevice9::GetPaletteEntries",
				"IDirect3DDevice9::SetCurrentTexturePalette",
				"IDirect3DDevice9::GetCurrentTexturePalette",
				"IDirect3DDevice9::SetScissorRect",
				"IDirect3DDevice9::GetScissorRect",
				"IDirect3DDevice9::SetSoftwareVertexProcessing",
				"IDirect3DDevice9::GetSoftwareVertexProcessing",
				"IDirect3DDevice9::SetNPatchMode",
				"IDirect3DDevice9::GetNPatchMode",
				"IDirect3DDevice9::DrawPrimitive",
				"IDirect3DDevice9::DrawIndexedPrimitive",
				"IDirect3DDevice9::DrawPrimitiveUP",
				"IDirect3DDevice9::DrawIndexedPrimitiveUP",
				"IDirect3DDevice9::ProcessVertices",
				"IDirect3DDevice9::CreateVertexDeclaration",
				"IDirect3DDevice9::SetVertexDeclaration",
				"IDirect3DDevice9::GetVertexDeclaration",
				"IDirect3DDevice9::SetFVF",
				"IDirect3DDevice9::GetFVF",
				"IDirect3DDevice9::CreateVertexShader",
				"IDirect3DDevice9::SetVertexShader",
				"IDirect3DDevice9::GetVertexShader",
				"IDirect3DDevice9::SetVertexShaderConstantF",
				"IDirect3DDevice9::GetVertexShaderConstantF",
				"IDirect3DDevice9::SetVertexShaderConstantI",
				"IDirect3DDevice9::GetVertexShaderConstantI",
				"IDirect3DDevice9::SetVertexShaderConstantB",
				"IDirect3DDevice9::GetVertexShaderConstantB",
				"IDirect3DDevice9::SetStreamSource",
				"IDirect3DDevice9::GetStreamSource",
				"IDirect3DDevice9::SetStreamSourceFreq",
				"IDirect3DDevice9::GetStreamSourceFreq",
				"IDirect3DDevice9::SetIndices",
				"IDirect3DDevice9::GetIndices",
				"IDirect3DDevice9::CreatePixelShader",
				"IDirect3DDevice9::SetPixelShader",
				"IDirect3DDevice9::GetPixelShader",
				"IDirect3DDevice9::SetPixelShaderConstantF",
				"IDirect3DDevice9::GetPixelShaderConstantF",
				"IDirect3DDevice9::SetPixelShaderConstantI",
				"IDirect3DDevice9::GetPixelShaderConstantI",
				"IDirect3DDevice9::SetPixelShaderConstantB",
				"IDirect3DDevice9::GetPixelShaderConstantB",
				"IDirect3DDevice9::DrawRectPatch",
				"IDirect3DDevice9::DrawTriPatch",
				"IDirect3DDevice9::DeletePatch",
				"IDirect3DDevice9::CreateQuery",

				"IDirect3DDevice9Ex::SetConvolutionMonoKernel",
				"IDirect3DDevice9Ex::ComposeRects",
				"IDirect3DDevice9Ex::PresentEx",
				"IDirect3DDevice9Ex::GetGPUThreadPriority",
				"IDirect3DDevice9Ex::SetGPUThreadPriority",
				"IDirect3DDevice9Ex::WaitForVBlank",
				"IDirect3DDevice9Ex::CheckResourceResidency",
				"IDirect3DDevice9Ex::SetMaximumFrameLatency",
				"IDirect3DDevice9Ex::GetMaximumFrameLatency",
				"IDirect3DDevice9Ex::CheckDeviceState",
				"IDirect3DDevice9Ex::CreateRenderTargetEx",
				"IDirect3DDevice9Ex::CreateOffscreenPlainSurfaceEx",
				"IDirect3DDevice9Ex::CreateDepthStencilSurfaceEx",
				"IDirect3DDevice9Ex::ResetEx",
				"IDirect3DDevice9Ex::GetDisplayModeEx"
			};

			struct D3DPRESENT_PARAMETERS
			{
				UINT BackBufferWidth;
				UINT BackBufferHeight;
				UINT BackBufferFormat;
				UINT BackBufferCount;
				UINT MultiSampleType;
				DWORD MultiSampleQuality;
				UINT SwapEffect;
				HWND hDeviceWindow;
				BOOL Windowed;
				BOOL EnableAutoDepthStencil;
				UINT AutoDepthStencilFormat;
				DWORD Flags;
				UINT FullScreen_RefreshRateInHz;
				UINT PresentationInterval;
			};
		}
# endif
# if defined(KIERO_INCLUDE_D3D10) || defined(KIERO_INCLUDE_D3D11) || defined(KIERO_INCLUDE_D3D12)
		namespace dxgi
		{
			static GUID IID_IDXGIFactory = { 0x7b7166ec, 0x21c7, 0x44ae, 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 };

			struct DXGI_RATIONAL
			{
				UINT Numerator;
				UINT Denominator;
			};

			struct DXGI_MODE_DESC
			{
				UINT Width;
				UINT Height;
				DXGI_RATIONAL RefreshRate;
				UINT Format;
				UINT ScanlineOrdering;
				UINT Scaling;
			};

			struct DXGI_SAMPLE_DESC
			{
				UINT Count;
				UINT Quality;
			};

			struct DXGI_SWAP_CHAIN_DESC
			{
				DXGI_MODE_DESC BufferDesc;
				DXGI_SAMPLE_DESC SampleDesc;
				UINT BufferUsage;
				UINT BufferCount;
				HWND OutputWindow;
				BOOL Windowed;
				UINT SwapEffect;
				UINT Flags;
			};
		}
# endif
# ifdef KIERO_INCLUDE_D3D10
		namespace d3d10
		{
			static const char* s_methodsTable[] = 
			{ 
				"IDXGISwapChain::QueryInterface",
				"IDXGISwapChain::AddRef",
				"IDXGISwapChain::Release",
				"IDXGISwapChain::SetPrivateData",
				"IDXGISwapChain::SetPrivateDataInterface",
				"IDXGISwapChain::GetPrivateData",
				"IDXGISwapChain::GetParent",
				"IDXGISwapChain::GetDevice",
				"IDXGISwapChain::Present",
				"IDXGISwapChain::GetBuffer",
				"IDXGISwapChain::SetFullscreenState",
				"IDXGISwapChain::GetFullscreenState",
				"IDXGISwapChain::GetDesc",
				"IDXGISwapChain::ResizeBuffers",
				"IDXGISwapChain::ResizeTarget",
				"IDXGISwapChain::GetContainingOutput",
				"IDXGISwapChain::GetFrameStatistics",
				"IDXGISwapChain::GetLastPresentCount",

				"ID3D10Device::QueryInterface",
				"ID3D10Device::AddRef",
				"ID3D10Device::Release",
				"ID3D10Device::VSSetConstantBuffers",
				"ID3D10Device::PSSetShaderResources",
				"ID3D10Device::PSSetShader",
				"ID3D10Device::PSSetSamplers",
				"ID3D10Device::VSSetShader",
				"ID3D10Device::DrawIndexed",
				"ID3D10Device::Draw",
				"ID3D10Device::PSSetConstantBuffers",
				"ID3D10Device::IASetInputLayout",
				"ID3D10Device::IASetVertexBuffers",
				"ID3D10Device::IASetIndexBuffer",
				"ID3D10Device::DrawIndexedInstanced",
				"ID3D10Device::DrawInstanced",
				"ID3D10Device::GSSetConstantBuffers",
				"ID3D10Device::GSSetShader",
				"ID3D10Device::IASetPrimitiveTopology",
				"ID3D10Device::VSSetShaderResources",
				"ID3D10Device::VSSetSamplers",
				"ID3D10Device::SetPredication",
				"ID3D10Device::GSSetShaderResources",
				"ID3D10Device::GSSetSamplers",
				"ID3D10Device::OMSetRenderTargets",
				"ID3D10Device::OMSetBlendState",
				"ID3D10Device::OMSetDepthStencilState",
				"ID3D10Device::SOSetTargets",
				"ID3D10Device::DrawAuto",
				"ID3D10Device::RSSetState",
				"ID3D10Device::RSSetViewports",
				"ID3D10Device::RSSetScissorRects",
				"ID3D10Device::CopySubresourceRegion",
				"ID3D10Device::CopyResource",
				"ID3D10Device::UpdateSubresource",
				"ID3D10Device::ClearRenderTargetView",
				"ID3D10Device::ClearDepthStencilView",
				"ID3D10Device::GenerateMips",
				"ID3D10Device::ResolveSubresource",
				"ID3D10Device::VSGetConstantBuffers",
				"ID3D10Device::PSGetShaderResources",
				"ID3D10Device::PSGetShader",
				"ID3D10Device::PSGetSamplers",
				"ID3D10Device::VSGetShader",
				"ID3D10Device::PSGetConstantBuffers",
				"ID3D10Device::IAGetInputLayout",
				"ID3D10Device::IAGetVertexBuffers",
				"ID3D10Device::IAGetIndexBuffer",
				"ID3D10Device::GSGetConstantBuffers",
				"ID3D10Device::GSGetShader",
				"ID3D10Device::IAGetPrimitiveTopology",
				"ID3D10Device::VSGetShaderResources",
				"ID3D10Device::VSGetSamplers",
				"ID3D10Device::GetPredication",
				"ID3D10Device::GSGetShaderResources",
				"ID3D10Device::GSGetSamplers",
				"ID3D10Device::OMGetRenderTargets",
				"ID3D10Device::OMGetBlendState",
				"ID3D10Device::OMGetDepthStencilState",
				"ID3D10Device::SOGetTargets",
				"ID3D10Device::RSGetState",
				"ID3D10Device::RSGetViewports",
				"ID3D10Device::RSGetScissorRects",
				"ID3D10Device::GetDeviceRemovedReason",
				"ID3D10Device::SetExceptionMode",
				"ID3D10Device::GetExceptionMode",
				"ID3D10Device::GetPrivateData",
				"ID3D10Device::SetPrivateData",
				"ID3D10Device::SetPrivateDataInterface",
				"ID3D10Device::ClearState",
				"ID3D10Device::Flush",
				"ID3D10Device::CreateBuffer",
				"ID3D10Device::CreateTexture1D",
				"ID3D10Device::CreateTexture2D",
				"ID3D10Device::CreateTexture3D",
				"ID3D10Device::CreateShaderResourceView",
				"ID3D10Device::CreateRenderTargetView",
				"ID3D10Device::CreateDepthStencilView",
				"ID3D10Device::CreateInputLayout",
				"ID3D10Device::CreateVertexShader",
				"ID3D10Device::CreateGeometryShader",
				"ID3D10Device::CreateGemoetryShaderWithStreamOutput",
				"ID3D10Device::CreatePixelShader",
				"ID3D10Device::CreateBlendState",
				"ID3D10Device::CreateDepthStencilState",
				"ID3D10Device::CreateRasterizerState",
				"ID3D10Device::CreateSamplerState",
				"ID3D10Device::CreateQuery",
				"ID3D10Device::CreatePredicate",
				"ID3D10Device::CreateCounter",
				"ID3D10Device::CheckFormatSupport",
				"ID3D10Device::CheckMultisampleQualityLevels",
				"ID3D10Device::CheckCounterInfo",
				"ID3D10Device::CheckCounter",
				"ID3D10Device::GetCreationFlags",
				"ID3D10Device::OpenSharedResource",
				"ID3D10Device::SetTextFilterSize",
				"ID3D10Device::GetTextFilterSize"
			};
		}
# endif
# ifdef KIERO_INCLUDE_D3D11
		namespace d3d11
		{
			static const char* s_methodsTable[] = 
			{ 
				"IDXGISwapChain::QueryInterface",
				"IDXGISwapChain::AddRef",
				"IDXGISwapChain::Release",
				"IDXGISwapChain::SetPrivateData",
				"IDXGISwapChain::SetPrivateDataInterface",
				"IDXGISwapChain::GetPrivateData",
				"IDXGISwapChain::GetParent",
				"IDXGISwapChain::GetDevice",
				"IDXGISwapChain::Present",
				"IDXGISwapChain::GetBuffer",
				"IDXGISwapChain::SetFullscreenState",
				"IDXGISwapChain::GetFullscreenState",
				"IDXGISwapChain::GetDesc",
				"IDXGISwapChain::ResizeBuffers",
				"IDXGISwapChain::ResizeTarget",
				"IDXGISwapChain::GetContainingOutput",
				"IDXGISwapChain::GetFrameStatistics",
				"IDXGISwapChain::GetLastPresentCount",

				"ID3D11Device::QueryInterface",
				"ID3D11Device::AddRef",
				"ID3D11Device::Release",	
				"ID3D11Device::CreateBuffer",
				"ID3D11Device::CreateTexture1D",
				"ID3D11Device::CreateTexture2D",
				"ID3D11Device::CreateTexture3D",
				"ID3D11Device::CreateShaderResourceView",
				"ID3D11Device::CreateUnorderedAccessView",
				"ID3D11Device::CreateRenderTargetView",
				"ID3D11Device::CreateDepthStencilView",
				"ID3D11Device::CreateInputLayout",
				"ID3D11Device::CreateVertexShader",
				"ID3D11Device::CreateGeometryShader",
				"ID3D11Device::CreateGeometryShaderWithStreamOutput",
				"ID3D11Device::CreatePixelShader",
				"ID3D11Device::CreateHullShader",
				"ID3D11Device::CreateDomainShader",
				"ID3D11Device::CreateComputeShader",
				"ID3D11Device::CreateClassLinkage",
				"ID3D11Device::CreateBlendState",
				"ID3D11Device::CreateDepthStencilState",
				"ID3D11Device::CreateRasterizerState",
				"ID3D11Device::CreateSamplerState",
				"ID3D11Device::CreateQuery",
				"ID3D11Device::CreatePredicate",
				"ID3D11Device::CreateCounter",
				"ID3D11Device::CreateDeferredContext",
				"ID3D11Device::OpenSharedResource",
				"ID3D11Device::CheckFormatSupport",
				"ID3D11Device::CheckMultisampleQualityLevels",
				"ID3D11Device::CheckCounterInfo",
				"ID3D11Device::CheckCounter",
				"ID3D11Device::CheckFeatureSupport",
				"ID3D11Device::GetPrivateData",
				"ID3D11Device::SetPrivateData",
				"ID3D11Device::SetPrivateDataInterface",
				"ID3D11Device::GetFeatureLevel",
				"ID3D11Device::GetCreationFlags",
				"ID3D11Device::GetDeviceRemovedReason",
				"ID3D11Device::GetImmediateContext",
				"ID3D11Device::SetExceptionMode",
				"ID3D11Device::GetExceptionMode",

				"ID3D11DeviceContext::QueryInterface",
				"ID3D11DeviceContext::AddRef",
				"ID3D11DeviceContext::Release",
				"ID3D11DeviceContext::GetDevice",
				"ID3D11DeviceContext::GetPrivateData",
				"ID3D11DeviceContext::SetPrivateData",
				"ID3D11DeviceContext::SetPrivateDataInterface",
				"ID3D11DeviceContext::SetConstantBuffers",
				"ID3D11DeviceContext::SetShaderResources",
				"ID3D11DeviceContext::SetShader",
				"ID3D11DeviceContext::SetSamplers",
				"ID3D11DeviceContext::SetShader",
				"ID3D11DeviceContext::DrawIndexed",
				"ID3D11DeviceContext::Draw",
				"ID3D11DeviceContext::Map",
				"ID3D11DeviceContext::Unmap",
				"ID3D11DeviceContext::SetConstantBuffers",
				"ID3D11DeviceContext::IASetInputLayout",
				"ID3D11DeviceContext::IASetVertexBuffers",
				"ID3D11DeviceContext::IASetIndexBuffer",
				"ID3D11DeviceContext::DrawIndexedInstanced",
				"ID3D11DeviceContext::DrawInstanced",
				"ID3D11DeviceContext::SetConstantBuffers",
				"ID3D11DeviceContext::SetShader",
				"ID3D11DeviceContext::IASetPrimitiveTopology",
				"ID3D11DeviceContext::SetShaderResources",
				"ID3D11DeviceContext::SetSamplers",
				"ID3D11DeviceContext::Begin",
				"ID3D11DeviceContext::End",
				"ID3D11DeviceContext::GetData",
				"ID3D11DeviceContext::SetPredication",
				"ID3D11DeviceContext::SetShaderResources",
				"ID3D11DeviceContext::SetSamplers",
				"ID3D11DeviceContext::OMSetRenderTargets",
				"ID3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews",
				"ID3D11DeviceContext::OMSetBlendState",
				"ID3D11DeviceContext::OMSetDepthStencilState",
				"ID3D11DeviceContext::SOSetTargets",
				"ID3D11DeviceContext::DrawAuto",
				"ID3D11DeviceContext::DrawIndexedInstancedIndirect",
				"ID3D11DeviceContext::DrawInstancedIndirect",
				"ID3D11DeviceContext::Dispatch",
				"ID3D11DeviceContext::DispatchIndirect",
				"ID3D11DeviceContext::RSSetState",
				"ID3D11DeviceContext::RSSetViewports",
				"ID3D11DeviceContext::RSSetScissorRects",
				"ID3D11DeviceContext::CopySubresourceRegion",
				"ID3D11DeviceContext::CopyResource",
				"ID3D11DeviceContext::UpdateSubresource",
				"ID3D11DeviceContext::CopyStructureCount",
				"ID3D11DeviceContext::ClearRenderTargetView",
				"ID3D11DeviceContext::ClearUnorderedAccessViewUint",
				"ID3D11DeviceContext::ClearUnorderedAccessViewFloat",
				"ID3D11DeviceContext::ClearDepthStencilView",
				"ID3D11DeviceContext::GenerateMips",
				"ID3D11DeviceContext::SetResourceMinLOD",
				"ID3D11DeviceContext::GetResourceMinLOD",
				"ID3D11DeviceContext::ResolveSubresource",
				"ID3D11DeviceContext::ExecuteCommandList",
				"ID3D11DeviceContext::SetShaderResources",
				"ID3D11DeviceContext::SetShader",
				"ID3D11DeviceContext::SetSamplers",
				"ID3D11DeviceContext::SetConstantBuffers",
				"ID3D11DeviceContext::SetShaderResources",
				"ID3D11DeviceContext::SetShader",
				"ID3D11DeviceContext::SetSamplers",
				"ID3D11DeviceContext::SetConstantBuffers",
				"ID3D11DeviceContext::SetShaderResources",
				"ID3D11DeviceContext::CSSetUnorderedAccessViews",
				"ID3D11DeviceContext::SetShader",
				"ID3D11DeviceContext::SetSamplers",
				"ID3D11DeviceContext::SetConstantBuffers",
				"ID3D11DeviceContext::VSGetConstantBuffers",
				"ID3D11DeviceContext::PSGetShaderResources",
				"ID3D11DeviceContext::PSGetShader",
				"ID3D11DeviceContext::PSGetSamplers",
				"ID3D11DeviceContext::VSGetShader",
				"ID3D11DeviceContext::PSGetConstantBuffers",
				"ID3D11DeviceContext::IAGetInputLayout",
				"ID3D11DeviceContext::IAGetVertexBuffers",
				"ID3D11DeviceContext::IAGetIndexBuffer",
				"ID3D11DeviceContext::GSGetConstantBuffers",
				"ID3D11DeviceContext::GSGetShader",
				"ID3D11DeviceContext::IAGetPrimitiveTopology",
				"ID3D11DeviceContext::VSGetShaderResources",
				"ID3D11DeviceContext::VSGetSamplers",
				"ID3D11DeviceContext::GetPredication",
				"ID3D11DeviceContext::GSGetShaderResources",
				"ID3D11DeviceContext::GSGetSamplers",
				"ID3D11DeviceContext::OMGetRenderTargets",
				"ID3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews",
				"ID3D11DeviceContext::OMGetBlendState",
				"ID3D11DeviceContext::OMGetDepthStencilState",
				"ID3D11DeviceContext::SOGetTargets",
				"ID3D11DeviceContext::RSGetState",
				"ID3D11DeviceContext::RSGetViewports",
				"ID3D11DeviceContext::RSGetScissorRects",
				"ID3D11DeviceContext::HSGetShaderResources",
				"ID3D11DeviceContext::HSGetShader",
				"ID3D11DeviceContext::HSGetSamplers",
				"ID3D11DeviceContext::HSGetConstantBuffers",
				"ID3D11DeviceContext::DSGetShaderResources",
				"ID3D11DeviceContext::DSGetShader",
				"ID3D11DeviceContext::DSGetSamplers",
				"ID3D11DeviceContext::DSGetConstantBuffers",
				"ID3D11DeviceContext::CSGetShaderResources",
				"ID3D11DeviceContext::CSGetUnorderedAccessViews",
				"ID3D11DeviceContext::CSGetShader",
				"ID3D11DeviceContext::CSGetSamplers",
				"ID3D11DeviceContext::CSGetConstantBuffers",
				"ID3D11DeviceContext::ClearState",
				"ID3D11DeviceContext::Flush",
				"ID3D11DeviceContext::GetType",
				"ID3D11DeviceContext::GetContextFlags",
				"ID3D11DeviceContext::FinishCommandList",
				"ID3D11DeviceContext::CopySubresourceRegion1",
				"ID3D11DeviceContext::UpdateSubresource1",
				"ID3D11DeviceContext::DiscardResource",
				"ID3D11DeviceContext::DiscardView",
				"ID3D11DeviceContext::SetConstantBuffers1",
				"ID3D11DeviceContext::SetConstantBuffers1",
				"ID3D11DeviceContext::SetConstantBuffers1",
				"ID3D11DeviceContext::SetConstantBuffers1",
				"ID3D11DeviceContext::SetConstantBuffers1",
				"ID3D11DeviceContext::SetConstantBuffers1",
				"ID3D11DeviceContext::VSGetConstantBuffers1",
				"ID3D11DeviceContext::HSGetConstantBuffers1",
				"ID3D11DeviceContext::DSGetConstantBuffers1",
				"ID3D11DeviceContext::GSGetConstantBuffers1",
				"ID3D11DeviceContext::PSGetConstantBuffers1",
				"ID3D11DeviceContext::CSGetConstantBuffers1",
				"ID3D11DeviceContext::SwapDeviceContextState",
				"ID3D11DeviceContext::ClearView",
				"ID3D11DeviceContext::DiscardView1",
				"ID3D11DeviceContext::UpdateTileMappings",
				"ID3D11DeviceContext::CopyTileMappings",
				"ID3D11DeviceContext::CopyTiles",
				"ID3D11DeviceContext::UpdateTiles",
				"ID3D11DeviceContext::ResizeTilePool",
				"ID3D11DeviceContext::TiledResourceBarrier",
				"ID3D11DeviceContext::IsAnnotationEnabled",
				"ID3D11DeviceContext::SetMarkerInt",
				"ID3D11DeviceContext::BeginEventInt",
				"ID3D11DeviceContext::EndEvent",
			};
		}
# endif
# ifdef KIERO_INCLUDE_D3D12
		namespace d3d12
		{
			static const char* s_methodsTable[] = 
			{ 
				"IDXGISwapChain::QueryInterface",
				"IDXGISwapChain::AddRef",
				"IDXGISwapChain::Release",
				"IDXGISwapChain::SetPrivateData",
				"IDXGISwapChain::SetPrivateDataInterface",
				"IDXGISwapChain::GetPrivateData",
				"IDXGISwapChain::GetParent",
				"IDXGISwapChain::GetDevice",
				"IDXGISwapChain::Present",
				"IDXGISwapChain::GetBuffer",
				"IDXGISwapChain::SetFullscreenState",
				"IDXGISwapChain::GetFullscreenState",
				"IDXGISwapChain::GetDesc",
				"IDXGISwapChain::ResizeBuffers",
				"IDXGISwapChain::ResizeTarget",
				"IDXGISwapChain::GetContainingOutput",
				"IDXGISwapChain::GetFrameStatistics",
				"IDXGISwapChain::GetLastPresentCount",

				"ID3D12Device::QueryInterface",
				"ID3D12Device::AddRef",
				"ID3D12Device::Release",
				"ID3D12Device::GetPrivateData",
				"ID3D12Device::SetPrivateData",
				"ID3D12Device::SetPrivateDataInterface",
				"ID3D12Device::SetName",
				"ID3D12Device::GetNodeCount",
				"ID3D12Device::CreateCommandQueue",
				"ID3D12Device::CreateCommandAllocator",
				"ID3D12Device::CreateGraphicsPipelineState",
				"ID3D12Device::CreateComputePipelineState",
				"ID3D12Device::CreateCommandList",
				"ID3D12Device::CheckFeatureSupport",
				"ID3D12Device::CreateDescriptorHeap",
				"ID3D12Device::GetDescriptorHandleIncrementSize",
				"ID3D12Device::CreateRootSignature",
				"ID3D12Device::CreateConstantBufferView",
				"ID3D12Device::CreateShaderResourceView",
				"ID3D12Device::CreateUnorderedAccessView",
				"ID3D12Device::CreateRenderTargetView",
				"ID3D12Device::CreateDepthStencilView",
				"ID3D12Device::CreateSampler",
				"ID3D12Device::CopyDescriptors",
				"ID3D12Device::CopyDescriptorsSimple",
				"ID3D12Device::GetResourceAllocationInfo",
				"ID3D12Device::GetCustomHeapProperties",
				"ID3D12Device::CreateCommittedResource",
				"ID3D12Device::CreateHeap",
				"ID3D12Device::CreatePlacedResource",
				"ID3D12Device::CreateReservedResource",
				"ID3D12Device::CreateSharedHandle",
				"ID3D12Device::OpenSharedHandle",
				"ID3D12Device::OpenSharedHandleByName",
				"ID3D12Device::MakeResident",
				"ID3D12Device::Evict",
				"ID3D12Device::CreateFence",
				"ID3D12Device::GetDeviceRemovedReason",
				"ID3D12Device::GetCopyableFootprints",
				"ID3D12Device::CreateQueryHeap",
				"ID3D12Device::SetStablePowerState",
				"ID3D12Device::CreateCommandSignature",
				"ID3D12Device::GetResourceTiling",
				"ID3D12Device::GetAdapterLuid",

				"ID3D12CommandQueue::QueryInterface",
				"ID3D12CommandQueue::AddRef",
				"ID3D12CommandQueue::Release",
				"ID3D12CommandQueue::GetPrivateData",
				"ID3D12CommandQueue::SetPrivateData",
				"ID3D12CommandQueue::SetPrivateDataInterface",
				"ID3D12CommandQueue::SetName",
				"ID3D12CommandQueue::GetDevice",
				"ID3D12CommandQueue::UpdateTileMappings",
				"ID3D12CommandQueue::CopyTileMappings",
				"ID3D12CommandQueue::ExecuteCommandLists",
				"ID3D12CommandQueue::SetMarker",
				"ID3D12CommandQueue::BeginEvent",
				"ID3D12CommandQueue::EndEvent",
				"ID3D12CommandQueue::Signal",
				"ID3D12CommandQueue::Wait",
				"ID3D12CommandQueue::GetTimestampFrequency",
				"ID3D12CommandQueue::GetClockCalibration",
				"ID3D12CommandQueue::GetDesc",

				"ID3D12CommandAllocator::QueryInterface",
				"ID3D12CommandAllocator::AddRef",
				"ID3D12CommandAllocator::Release",
				"ID3D12CommandAllocator::GetPrivateData",
				"ID3D12CommandAllocator::SetPrivateData",
				"ID3D12CommandAllocator::SetPrivateDataInterface",
				"ID3D12CommandAllocator::SetName",
				"ID3D12CommandAllocator::GetDevice",
				"ID3D12CommandAllocator::Reset",

				"ID3D12GraphicsCommandList::QueryInterface",
				"ID3D12GraphicsCommandList::AddRef",
				"ID3D12GraphicsCommandList::Release",
				"ID3D12GraphicsCommandList::GetPrivateData",
				"ID3D12GraphicsCommandList::SetPrivateData",
				"ID3D12GraphicsCommandList::SetPrivateDataInterface",
				"ID3D12GraphicsCommandList::SetName",
				"ID3D12GraphicsCommandList::GetDevice",
				"ID3D12GraphicsCommandList::GetType",
				"ID3D12GraphicsCommandList::Close",
				"ID3D12GraphicsCommandList::Reset",
				"ID3D12GraphicsCommandList::ClearState",
				"ID3D12GraphicsCommandList::DrawInstanced",
				"ID3D12GraphicsCommandList::DrawIndexedInstanced",
				"ID3D12GraphicsCommandList::Dispatch",
				"ID3D12GraphicsCommandList::CopyBufferRegion",
				"ID3D12GraphicsCommandList::CopyTextureRegion",
				"ID3D12GraphicsCommandList::CopyResource",
				"ID3D12GraphicsCommandList::CopyTiles",
				"ID3D12GraphicsCommandList::ResolveSubresource",
				"ID3D12GraphicsCommandList::IASetPrimitiveTopology",
				"ID3D12GraphicsCommandList::RSSetViewports",
				"ID3D12GraphicsCommandList::RSSetScissorRects",
				"ID3D12GraphicsCommandList::OMSetBlendFactor",
				"ID3D12GraphicsCommandList::OMSetStencilRef",
				"ID3D12GraphicsCommandList::SetPipelineState",
				"ID3D12GraphicsCommandList::ResourceBarrier",
				"ID3D12GraphicsCommandList::ExecuteBundle",
				"ID3D12GraphicsCommandList::SetDescriptorHeaps",
				"ID3D12GraphicsCommandList::SetComputeRootSignature",
				"ID3D12GraphicsCommandList::SetGraphicsRootSignature",
				"ID3D12GraphicsCommandList::SetComputeRootDescriptorTable",
				"ID3D12GraphicsCommandList::SetGraphicsRootDescriptorTable",
				"ID3D12GraphicsCommandList::SetComputeRoot32BitConstant",
				"ID3D12GraphicsCommandList::SetGraphicsRoot32BitConstant",
				"ID3D12GraphicsCommandList::SetComputeRoot32BitConstants",
				"ID3D12GraphicsCommandList::SetGraphicsRoot32BitConstants",
				"ID3D12GraphicsCommandList::SetComputeRootConstantBufferView",
				"ID3D12GraphicsCommandList::SetGraphicsRootConstantBufferView",
				"ID3D12GraphicsCommandList::SetComputeRootShaderResourceView",
				"ID3D12GraphicsCommandList::SetGraphicsRootShaderResourceView",
				"ID3D12GraphicsCommandList::SetComputeRootUnorderedAccessView",
				"ID3D12GraphicsCommandList::SetGraphicsRootUnorderedAccessView",
				"ID3D12GraphicsCommandList::IASetIndexBuffer",
				"ID3D12GraphicsCommandList::IASetVertexBuffers",
				"ID3D12GraphicsCommandList::SOSetTargets",
				"ID3D12GraphicsCommandList::OMSetRenderTargets",
				"ID3D12GraphicsCommandList::ClearDepthStencilView",
				"ID3D12GraphicsCommandList::ClearRenderTargetView",
				"ID3D12GraphicsCommandList::ClearUnorderedAccessViewUint",
				"ID3D12GraphicsCommandList::ClearUnorderedAccessViewFloat",
				"ID3D12GraphicsCommandList::DiscardResource",
				"ID3D12GraphicsCommandList::BeginQuery",
				"ID3D12GraphicsCommandList::EndQuery",
				"ID3D12GraphicsCommandList::ResolveQueryData",
				"ID3D12GraphicsCommandList::SetPredication",
				"ID3D12GraphicsCommandList::SetMarker",
				"ID3D12GraphicsCommandList::BeginEvent",
				"ID3D12GraphicsCommandList::EndEvent",
				"ID3D12GraphicsCommandList::ExecuteIndirect",
			};

			static GUID IID_ID3D12Device = { 0x189819f1, 0x1db6, 0x4b57, 0xbe, 0x54, 0x18, 0x21, 0x33, 0x9b, 0x85, 0xf7 };
			static GUID IID_ID3D12CommandQueue = { 0x0ec870a6, 0x5d7e, 0x4c22, 0x8c, 0xfc, 0x5b, 0xaa, 0xe0, 0x76, 0x16, 0xed };
			static GUID IID_ID3D12CommandAllocator = { 0x6102dee4, 0xaf59, 0x4b09, 0xb9, 0x99, 0xb4, 0x4d, 0x73, 0xf0, 0x9b, 0x24 };
			static GUID IID_ID3D12GraphicsCommandList = { 0x5b160d0f, 0xac1b, 0x4185, 0x8b, 0xa8, 0xb3, 0xae, 0x42, 0xa5, 0xa4, 0x55 };

			struct D3D12_COMMAND_QUEUE_DESC
			{
				UINT Type;
				INT Priority;
				UINT Flags;
				UINT NodeMask;
			};
		}
# endif
#endif
	}
}

kiero::Status::Enum kiero::init(RenderType::Enum _renderType)
{
	if (g_renderType != RenderType::None)
	{
		KIERO_ASSERT(0 && "Are you trying to initialize twice?");
		return Status::AlreadyInitialized;
	}

	if (_renderType == RenderType::D3D7)
	{
#ifndef KIERO_INCLUDE_D3D7
		goto NOT_IMPLEMENT_ERR;
#else
		// TODO: ...
#endif
	}
	else if (_renderType == RenderType::D3D8)
	{
#ifndef KIERO_INCLUDE_D3D8
		goto NOT_IMPLEMENT_ERR;
#else
		HMODULE libD3D8;
		if ((libD3D8 = ::GetModuleHandle(KIERO_TEXT("d3d8.dll"))) == NULL)
		{
			return Status::ModuleNotFoundError;
		}

		void* Direct3DCreate8;
		if ((Direct3DCreate8 = ::GetProcAddress(libD3D8, KIERO_TEXTA("Direct3DCreate8"))) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXObjectPtr direct3D8;
		if ((direct3D8.instance = ((void*(__stdcall*)(uint32_t))(Direct3DCreate8))(220)) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXWindow window;
		kitchen::d3d8::D3DPRESENT_PARAMETERS params;
		params.BackBufferWidth = 0;
		params.BackBufferHeight = 0;
		params.BackBufferFormat = 0;
		params.BackBufferCount = 0;
		params.MultiSampleType = 0;
		params.SwapEffect = 1;
		params.hDeviceWindow = window.handle;
		params.Windowed = 1;
		params.EnableAutoDepthStencil = 0;
		params.AutoDepthStencilFormat = 0;
		params.Flags = 0;
		params.FullScreen_RefreshRateInHz = 0;
		params.FullScreen_PresentationInterval = 0;

		// IDirect3D8::CreateDevice
		kitchen::DirectXObjectPtr device;
		if (((int(__stdcall*)(
			void*, 
			uint32_t, 
			int, 
			HWND, 
			uint32_t, 
			void*, 
			void**))(((*(uintptr_t**)(direct3D8.instance)))[15]))(
				direct3D8.instance, 
				0, // D3DADAPTER_DEFAULT
				4, // D3DDEVTYPE_NULLREF
				window.handle, 
				0x120, // D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT
				&params,
				&device.instance) < 0)
		{
			return Status::UnknownError;
		}

		// IDirect3DDevice8
		for (size_t i = 0; i < 97; ++i)
		{
			const char* alias = kitchen::d3d9::s_methodsTable[i];
			g_methodsMap[alias] = ((*(uintptr_t**)(device.instance)))[i];
		}
#endif
	}
	else if (_renderType == RenderType::D3D9)
	{
#ifndef KIERO_INCLUDE_D3D9
		goto NOT_IMPLEMENT_ERR;
#else
		HMODULE libD3D9;
		if ((libD3D9 = ::GetModuleHandle(KIERO_TEXT("d3d9.dll"))) == NULL)
		{
			return Status::ModuleNotFoundError;
		}

		void* Direct3DCreate9;
		if ((Direct3DCreate9 = ::GetProcAddress(libD3D9, KIERO_TEXTA("Direct3DCreate9"))) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXObjectPtr direct3D9;
		if ((direct3D9.instance = ((void* (__stdcall*)(uint32_t))(Direct3DCreate9))(32)) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXWindow window;
		kitchen::d3d9::D3DPRESENT_PARAMETERS params;
		params.BackBufferWidth = 0;
		params.BackBufferHeight = 0;
		params.BackBufferFormat = 0;
		params.BackBufferCount = 0;
		params.MultiSampleType = 0;
		params.MultiSampleQuality = 0;
		params.SwapEffect = 1;
		params.hDeviceWindow = window.handle;
		params.Windowed = 1;
		params.EnableAutoDepthStencil = 0;
		params.AutoDepthStencilFormat = 0;
		params.Flags = 0;
		params.FullScreen_RefreshRateInHz = 0;
		params.PresentationInterval = 0;

		// IDirect3D9::CreateDevice
		kitchen::DirectXObjectPtr device;
		if (((int(__stdcall*)(
			void*,
			uint32_t,
			int,
			HWND,
			uint32_t,
			void*,
			void**))(((*(uintptr_t**)(direct3D9.instance)))[16]))(
				direct3D9.instance,
				0, // D3DADAPTER_DEFAULT
				4, // D3DDEVTYPE_NULLREF
				window.handle,
				0x120, // D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT
				&params,
				&device.instance) < 0)
		{
			return Status::UnknownError;
		}

		// IDirect3DDevice9
		for (size_t i = 0; i < 119; ++i)
		{
			const char* alias = kitchen::d3d9::s_methodsTable[i];
			g_methodsMap[alias] = ((*(uintptr_t**)(device.instance)))[i];
		}
#endif
	}
	else if (_renderType == RenderType::D3D9Ex)
	{
#ifndef KIERO_INCLUDE_D3D9EX
		goto NOT_IMPLEMENT_ERR;
#else
		HMODULE libD3D9;
		if ((libD3D9 = ::GetModuleHandle(KIERO_TEXT("d3d9.dll"))) == NULL)
		{
			return Status::ModuleNotFoundError;
		}

		void* Direct3DCreate9Ex;
		if ((Direct3DCreate9Ex = ::GetProcAddress(libD3D9, KIERO_TEXTA("Direct3DCreate9Ex"))) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXObjectPtr direct3D9Ex;
		if ((direct3D9Ex.instance = ((void* (__stdcall*)(uint32_t))(Direct3DCreate9Ex))(32)) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXWindow window;
		kitchen::d3d9::D3DPRESENT_PARAMETERS params;
		params.BackBufferWidth = 0;
		params.BackBufferHeight = 0;
		params.BackBufferFormat = 0;
		params.BackBufferCount = 0;
		params.MultiSampleType = 0;
		params.MultiSampleQuality = 0;
		params.SwapEffect = 1;
		params.hDeviceWindow = window.handle;
		params.Windowed = 1;
		params.EnableAutoDepthStencil = 0;
		params.AutoDepthStencilFormat = 0;
		params.Flags = 0;
		params.FullScreen_RefreshRateInHz = 0;
		params.PresentationInterval = 0;

		// IDirect3D9::CreateDeviceEx
		kitchen::DirectXObjectPtr device;
		if (((int(__stdcall*)(
			void*,
			uint32_t,
			int,
			HWND,
			uint32_t,
			void*,
			void*,
			void**))(((*(uintptr_t**)(direct3D9Ex.instance)))[20]))(
				direct3D9Ex.instance,
				0, // D3DADAPTER_DEFAULT
				4, // D3DDEVTYPE_NULLREF
				window.handle,
				0x120, // D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT
				&params,
				NULL,
				&device.instance) < 0)
		{
			return Status::UnknownError;
		}

		// IDirect3DDevice9Ex
		for (size_t i = 0; i < 134; ++i)
		{
			const char* alias = kitchen::d3d9::s_methodsTable[i];
			g_methodsMap[alias] = ((*(uintptr_t**)(device.instance)))[i];
		}
#endif
	}
	else if (_renderType == RenderType::D3D10)
	{
#ifndef KIERO_INCLUDE_D3D10
		goto NOT_IMPLEMENT_ERR;
#else
		HMODULE libD3D10;
		if ((libD3D10 = ::GetModuleHandle(KIERO_TEXT("d3d10.dll"))) == NULL)
		{
			return Status::ModuleNotFoundError;
		}

		void* D3D10CreateDeviceAndSwapChain;
		if ((D3D10CreateDeviceAndSwapChain = ::GetProcAddress(libD3D10, KIERO_TEXTA("D3D10CreateDeviceAndSwapChain"))) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXWindow window;

		kitchen::dxgi::DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		kitchen::dxgi::DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = 28; // DXGI_FORMAT_R8G8B8A8_UNORM
		bufferDesc.ScanlineOrdering = 0; // DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED
		bufferDesc.Scaling = 0; // DXGI_MODE_SCALING_UNSPECIFIED

		kitchen::dxgi::DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		kitchen::dxgi::DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = 0x20; // DXGI_USAGE_RENDER_TARGET_OUTPUT
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = window.handle;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = 0; // DXGI_SWAP_EFFECT_DISCARD
		swapChainDesc.Flags = 2; // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH

		kitchen::DirectXObjectPtr device;
		kitchen::DirectXObjectPtr swapChain;

		if (((long(__stdcall*)(
			void*,
			UINT,
			HMODULE,
			UINT,
			UINT,
			void*,
			void**,
			void**))(D3D10CreateDeviceAndSwapChain))(
				NULL, 
				0, // D3D10_DRIVER_TYPE_HARDWARE
				NULL, 
				0, 
				29, // D3D10_SDK_VERSION 
				&swapChainDesc, 
				&swapChain.instance, 
				&device.instance) < 0)
		{
			return Status::UnknownError;
		}

		size_t i, o;

		// IDXGISwapChain
		for (i = 0, o = 0; i < 18; ++i, ++o)
		{
			const char* alias = kitchen::d3d10::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(swapChain.instance)))[i];
		}

		// ID3D10Device
		for (i = 0; i < 98; ++i, ++o)
		{
			const char* alias = kitchen::d3d10::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(device.instance)))[i];
		}
#endif
	}
	else if (_renderType == RenderType::D3D11)
	{
#ifndef KIERO_INCLUDE_D3D11
		goto NOT_IMPLEMENT_ERR;
#else
		HMODULE libD3D11;
		if ((libD3D11 = ::GetModuleHandle(KIERO_TEXT("d3d11.dll"))) == NULL)
		{
			return Status::ModuleNotFoundError;
		}

		void* D3D11CreateDeviceAndSwapChain;
		if ((D3D11CreateDeviceAndSwapChain = ::GetProcAddress(libD3D11, KIERO_TEXTA("D3D11CreateDeviceAndSwapChain"))) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXWindow window;

		kitchen::dxgi::DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		kitchen::dxgi::DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = 28; // DXGI_FORMAT_R8G8B8A8_UNORM
		bufferDesc.ScanlineOrdering = 0; // DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED
		bufferDesc.Scaling = 0; // DXGI_MODE_SCALING_UNSPECIFIED

		kitchen::dxgi::DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		kitchen::dxgi::DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = 0x20; // DXGI_USAGE_RENDER_TARGET_OUTPUT
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = window.handle;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = 0; // DXGI_SWAP_EFFECT_DISCARD
		swapChainDesc.Flags = 2; // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH

		kitchen::DirectXObjectPtr device;
		kitchen::DirectXObjectPtr context;
		kitchen::DirectXObjectPtr swapChain;

		HRESULT hr;

		if ((hr = ((long(__stdcall*)(
			void*,
			UINT,
			HMODULE,
			UINT,
			const void*,
			UINT,
			UINT,
			const void*,
			void**,
			void**,
			void*,
			void**))(D3D11CreateDeviceAndSwapChain))(
				NULL, 
				1, // D3D_DRIVER_TYPE_HARDWARE
				NULL, 
				0, 
				NULL, 
				0, 
				7, // D3D11_SDK_VERSION
				&swapChainDesc, 
				&swapChain.instance, 
				&device.instance, 
				NULL, 
				&context.instance)) < 0)
		{
			return Status::UnknownError;
		}

		size_t i, o;

		// IDXGISwapChain
		for (i = 0, o = 0; i < 18; ++i, ++o)
		{
			const char* alias = kitchen::d3d11::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(swapChain.instance)))[i];
		}

		// ID3D11Device
		for (i = 0; i < 43; ++i, ++o)
		{
			const char* alias = kitchen::d3d11::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(device.instance)))[i];
		}

		// ID3D11DeviceContext
		for (i = 0; i < 144; ++i, ++o)
		{
			const char* alias = kitchen::d3d11::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(context.instance)))[i];
		}
#endif
	}
	else if (_renderType == RenderType::D3D12)
	{
#ifndef KIERO_INCLUDE_D3D12
		goto NOT_IMPLEMENT_ERR;
#else
		HMODULE libDXGI;
		HMODULE libD3D12;
		if ((libDXGI = ::GetModuleHandle(KIERO_TEXT("dxgi.dll"))) == NULL || (libD3D12 = ::GetModuleHandle(KIERO_TEXT("d3d12.dll"))) == NULL)
		{
			return Status::ModuleNotFoundError;
		}

		void* CreateDXGIFactory;
		if ((CreateDXGIFactory = ::GetProcAddress(libDXGI, KIERO_TEXTA("CreateDXGIFactory"))) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXObjectPtr factory;
		if (((long(__stdcall*)(
			const IID&, 
			void**))(CreateDXGIFactory))(
				kitchen::dxgi::IID_IDXGIFactory, 
				&factory.instance) < 0)
		{
			return Status::UnknownError;
		}

		void* D3D12CreateDevice;
		if ((D3D12CreateDevice = ::GetProcAddress(libD3D12, KIERO_TEXTA("D3D12CreateDevice"))) == NULL)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXObjectPtr device;

		if (((long(__stdcall*)(
			IUnknown*, 
			UINT, 
			const IID&, 
			void**))(D3D12CreateDevice))(
				NULL, 
				0xb000, // D3D_FEATURE_LEVEL_11_0
				kitchen::d3d12::IID_ID3D12Device,
				(void**)&device.instance) < 0)
		{
			return Status::UnknownError;
		}

		kitchen::d3d12::D3D12_COMMAND_QUEUE_DESC queueDesc;
		queueDesc.Type = 0; //  D3D12_COMMAND_LIST_TYPE_DIRECT
		queueDesc.Priority = 0;
		queueDesc.Flags = 0; // D3D12_COMMAND_QUEUE_FLAG_NONE
		queueDesc.NodeMask = 0;

		// ID3D12Device::CreateCommandQueue
		kitchen::DirectXObjectPtr commandQueue;
		if (((int(__stdcall*)(
			void*,
			void*,
			REFIID,
			void**))(((*(uintptr_t**)(device.instance)))[8]))(
				device.instance,
				&queueDesc,
				kitchen::d3d12::IID_ID3D12CommandQueue,
				&commandQueue.instance) < 0)
		{
			return Status::UnknownError;
		}

		// ID3D12Device::CreateCommandAllocator
		kitchen::DirectXObjectPtr commandAllocator;
		if (((int(__stdcall*)(
			void*,
			UINT,
			REFIID,
			void**))(((*(uintptr_t**)(device.instance)))[9]))(
				device.instance,
				0, // D3D12_COMMAND_LIST_TYPE_DIRECT
				kitchen::d3d12::IID_ID3D12CommandAllocator,
				&commandAllocator.instance) < 0)
		{
			return Status::UnknownError;
		}

		// ID3D12Device::CreateCommandList
		kitchen::DirectXObjectPtr commandList;
		if (((int(__stdcall*)(
			void*,
			UINT,
			UINT,
			void*,
			void*,
			REFIID,
			void**))(((*(uintptr_t**)(device.instance)))[12]))(
				device.instance,
				0,
				0, // D3D12_COMMAND_LIST_TYPE_DIRECT
				commandAllocator.instance,
				NULL,
				kitchen::d3d12::IID_ID3D12GraphicsCommandList,
				&commandAllocator.instance) < 0)
		{
			return Status::UnknownError;
		}

		kitchen::DirectXWindow window;

		kitchen::dxgi::DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		kitchen::dxgi::DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = 28; // DXGI_FORMAT_R8G8B8A8_UNORM
		bufferDesc.ScanlineOrdering = 0; // DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED
		bufferDesc.Scaling = 0; // DXGI_MODE_SCALING_UNSPECIFIED

		kitchen::dxgi::DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		kitchen::dxgi::DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = 0x20; // DXGI_USAGE_RENDER_TARGET_OUTPUT
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = window.handle;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = 0; // DXGI_SWAP_EFFECT_DISCARD
		swapChainDesc.Flags = 2; // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH

		kitchen::DirectXObjectPtr swapChain;
		if (((int(__stdcall*)(
			void*,
			void*,
			void*,
			void**))(((*(uintptr_t**)(factory.instance)))[10]))(
				factory.instance,
				commandQueue.instance,
				&swapChainDesc,
				&swapChain.instance) < 0)
		{
			return Status::UnknownError;
		}

		size_t i, o;

		// IDXGISwapChain
		for (i = 0, o = 0; i < 18; ++i, ++o)
		{
			const char* alias = kitchen::d3d12::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(swapChain.instance)))[i];
		}

		// ID3D12Device
		for (i = 0; i < 44; ++i, ++o)
		{
			const char* alias = kitchen::d3d12::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(device.instance)))[i];
		}

		// ID3D12CommandQueue
		for (i = 0; i < 19; ++i, ++o)
		{
			const char* alias = kitchen::d3d12::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(commandQueue.instance)))[i];
		}

		// ID3D12CommandAllocator
		for (i = 0; i < 9; ++i, ++o)
		{
			const char* alias = kitchen::d3d12::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(commandAllocator.instance)))[i];
		}

		// ID3D12CommandList
		for (i = 0; i < 60; ++i, ++o)
		{
			const char* alias = kitchen::d3d12::s_methodsTable[o];
			g_methodsMap[alias] = ((*(uintptr_t**)(commandList.instance)))[i];
		}
#endif
	}
	else if (_renderType == RenderType::OpenGL)
	{
#ifndef KIERO_INCLUDE_OPENGL
		goto NOT_IMPLEMENT_ERR;
#else
		HMODULE libOpenGL32;
		if ((libOpenGL32 = ::GetModuleHandle(KIERO_TEXT("opengl32.dll"))) == NULL)
		{
			return Status::ModuleNotFoundError;
		}

		g_autoImportLib = libOpenGL32;
#endif
	}
	else if (_renderType == RenderType::Vulkan)
	{
#ifndef KIERO_INCLUDE_VULKAN
		goto NOT_IMPLEMENT_ERR;
#else
		HMODULE libVulkan;
		if ((libVulkan = ::GetModuleHandle(KIERO_TEXT("vulkan-1.dll"))) == NULL)
		{
			return Status::ModuleNotFoundError;
		}

		g_autoImportLib = libVulkan;
#endif
	}
	else if (_renderType == RenderType::Auto)
	{
		// TODO: ...
	}
	else
	{
		NOT_IMPLEMENT_ERR:
		KIERO_ASSERT(0 && "Initialization attempt for a library that is not included in the build.");
		return Status::NotImplementedError;
	}

	g_renderType = _renderType;

	return Status::Success;
}

void kiero::shutdown()
{
	if (g_renderType != RenderType::None)
	{
		// TODO: ...
		g_autoImportLib = NULL;
		g_methodsMap.clear();
		g_renderType = RenderType::None;
	}
}

kiero::RenderType::Enum kiero::getRenderType()
{
	return g_renderType;
}

uintptr_t kiero::getMethodAddress(const char* alias)
{
	if (g_renderType == RenderType::None)
	{
		KIERO_ASSERT(0 && "Trying get methods without initialization?");
		return NULL;
	}

	if (g_autoImportLib != NULL)
	{
		return (uintptr_t)::GetProcAddress(g_autoImportLib, alias);
	}

	std::unordered_map<const char*, uintptr_t>::iterator it = g_methodsMap.find(alias);

	if (it != g_methodsMap.end())
	{
		return it->second;
	}

	return NULL;
}

kiero::Status::Enum kiero::bind(const char* alias, void** original, void* function)
{
	// TODO: ...
	return Status::NotImplementedError;
}

void kiero::unbind(const char* alias)
{
	// TODO: ...
}