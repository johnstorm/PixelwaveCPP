
#ifndef _PXX_HEADER_UTILS_H_
#define _PXX_HEADER_UTILS_H_

#ifdef __cplusplus
#define PXXExtern extern "C"
#else
#define PXXExtern extern
#endif

//#import <CoreGraphics/CGBase.h>
//CGPointMake
//#define PXInline_h static
//#define PXInline_c static inline

#define PXXInline static inline
#define PXXInline_h
#define PXXInline_c inline
#define PXXAlwaysInline  __attribute__((always_inline))

#define PXX_LINENAME_CONCAT(_name_, _line_) _name_ ## _line_
#define PXX_LINENAME(_name_, _line_) PX_LINENAME_CONCAT(_name_, _line_)
#define PXX_UNIQUE_VAR(_name_) PX_LINENAME(_name_,__LINE__)

#define PXX_NOT_USED(_val_) ((void)(_val_))

#endif
