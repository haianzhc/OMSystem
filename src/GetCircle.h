//
// MATLAB Compiler: 7.1 (R2019b)
// Date: Tue Mar 31 21:39:15 2020
// Arguments:
// "-B""macro_default""-W""cpplib:GetCircle,all,version=1.0""-T""link:lib""-d""C
// :\Users\asus\Desktop\ar\GetCircle\for_testing""-v""C:\Users\asus\Desktop\ar\G
// etCircle.m"
//

#ifndef GetCircle_h
#define GetCircle_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_GetCircle_C_API 
#define LIB_GetCircle_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_GetCircle_C_API 
bool MW_CALL_CONV GetCircleInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_GetCircle_C_API 
bool MW_CALL_CONV GetCircleInitialize(void);

extern LIB_GetCircle_C_API 
void MW_CALL_CONV GetCircleTerminate(void);

extern LIB_GetCircle_C_API 
void MW_CALL_CONV GetCirclePrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_GetCircle_C_API 
bool MW_CALL_CONV mlxGetCircle(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_GetCircle
#define PUBLIC_GetCircle_CPP_API __declspec(dllexport)
#else
#define PUBLIC_GetCircle_CPP_API __declspec(dllimport)
#endif

#define LIB_GetCircle_CPP_API PUBLIC_GetCircle_CPP_API

#else

#if !defined(LIB_GetCircle_CPP_API)
#if defined(LIB_GetCircle_C_API)
#define LIB_GetCircle_CPP_API LIB_GetCircle_C_API
#else
#define LIB_GetCircle_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_GetCircle_CPP_API void MW_CALL_CONV GetCircle(const mwArray& path, const mwArray& filename);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
