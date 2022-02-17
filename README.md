# wxExtend

Provides additional classes for wxWidgets

## Building

Requires:
- Microsoft Visual Studio 2017-2019
- `..\..\include` folder with the following files to customize building process for individual applications (optional):
  - `Debug.props`
  - `Release.props`
  - `ARM64.props`
  - `x64.props`
  - `Win32.props`
- wxWidgets with `%WXWIN%` environment pointing to its root. Build wxWidgets with:

```bat
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsamd64_x86.bat"
cd /d "%WXWIN%\build\msw"
nmake /f makefile.vc /ls RUNTIME_LIBS=static  SHARED=0 TARGET_CPU=X86 COMPILER_VERSION=142 && nmake /f makefile.vc /ls RUNTIME_LIBS=static  SHARED=0 TARGET_CPU=X86 COMPILER_VERSION=142 BUILD=release
nmake /f makefile.vc /ls RUNTIME_LIBS=dynamic SHARED=0 TARGET_CPU=X86 COMPILER_VERSION=142 && nmake /f makefile.vc /ls RUNTIME_LIBS=dynamic SHARED=0 TARGET_CPU=X86 COMPILER_VERSION=142 BUILD=release
```

```bat
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cd /d "%WXWIN%\build\msw"
nmake /f makefile.vc /ls RUNTIME_LIBS=static  SHARED=0 TARGET_CPU=X64 COMPILER_VERSION=142 && nmake /f makefile.vc /ls RUNTIME_LIBS=static  SHARED=0 TARGET_CPU=X64 COMPILER_VERSION=142 BUILD=release
nmake /f makefile.vc /ls RUNTIME_LIBS=dynamic SHARED=0 TARGET_CPU=X64 COMPILER_VERSION=142 && nmake /f makefile.vc /ls RUNTIME_LIBS=dynamic SHARED=0 TARGET_CPU=X64 COMPILER_VERSION=142 BUILD=release
```

```bat
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsamd64_arm64.bat"
cd /d "%WXWIN%\build\msw"
nmake /f makefile.vc /ls RUNTIME_LIBS=static  SHARED=0 TARGET_CPU=ARM64 USE_OPENGL=0 COMPILER_VERSION=142 && nmake /f makefile.vc /ls RUNTIME_LIBS=static  SHARED=0 TARGET_CPU=ARM64 USE_OPENGL=0 COMPILER_VERSION=142 BUILD=release
nmake /f makefile.vc /ls RUNTIME_LIBS=dynamic SHARED=0 TARGET_CPU=ARM64 USE_OPENGL=0 COMPILER_VERSION=142 && nmake /f makefile.vc /ls RUNTIME_LIBS=dynamic SHARED=0 TARGET_CPU=ARM64 USE_OPENGL=0 COMPILER_VERSION=142 BUILD=release
```

## Usage

1. Clone the repository into your solution folder.
2. Add the appropriate `build\wxExtend<variant>.vcxproj` to your solution.
3. Add wxExtend's `include` folder to _Additional Include Directories_ in your project's C/C++ settings.
4. Add a new reference to wxExtend project from your project's common properties.
5. Include `.h` files from wxExtend as needed.

An auto-generated documentation is [here](http://amebis.github.io/wxExtend/).

More examples and use-cases can be found in [GÉANTLink](https://github.com/Amebis/GEANTLink) and [ZRCola](https://github.com/Amebis/ZRCola) projects source code. They make use of this library.
