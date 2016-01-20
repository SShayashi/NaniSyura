/****************************************************************************

 Copyright (c) 2014-2015 Chukong Technologies

 ****************************************************************************/

#ifndef _CC_SDKBOX_H_
#define _CC_SDKBOX_H_

#define SDKBOX_VERSION_STR  "sdkbox V1.5.3.3"

/**
 * Only certain compilers support __attribute__((deprecated)).
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define SDKBOX_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define SDKBOX_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
#define SDKBOX_DEPRECATED_ATTRIBUTE
#endif

/**
 * SDKBOX_DEPRECATED(4.0) or SDKBOX_DEPRECATED(4.0, "not going to need this anymore") etc.
 */
#define SDKBOX_DEPRECATED(...) SDKBOX_DEPRECATED_ATTRIBUTE

namespace sdkbox {

    void init( const char* application_token, const char* application_key );
    void init( const char* application_token, const char* application_key, bool debug );
    void setProjectType(const char* project_type);
    
    void sessionStart();
    void sessionEnd();
}

#endif//_CC_SDKBOX_H_
