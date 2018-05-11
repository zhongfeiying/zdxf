#if defined(APDRAW_DLL)
#   ifdef _WIN32
#       if defined(APDRAW_LIBRARY)
#           define APDRAW_EXPORT __declspec(dllexport)
#       else
#           define APDRAW_EXPORT __declspec(dllimport)
#       endif
#   else
#       define APDRAW_EXPORT
#   endif
#else
#   define APDRAW_EXPORT
#endif
