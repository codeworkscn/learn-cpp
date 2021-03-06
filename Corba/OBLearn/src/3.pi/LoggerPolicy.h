// **********************************************************************
//
// Generated by the ORBacus IDL-to-C++ Translator
//
// Copyright (c) 2005
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

// Version: 4.3.2

#ifndef ___LoggerPolicy_h__
#define ___LoggerPolicy_h__

#include <OB/Policy.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030200L)
#       error ORBacus version mismatch!
#   endif
#endif

class LoggerPolicy;
typedef LoggerPolicy* LoggerPolicy_ptr;
typedef LoggerPolicy* LoggerPolicyRef;

extern OB::TypeCodeConst _tc_LoggerPolicy;

void OBDuplicate(LoggerPolicy_ptr);
void OBRelease(LoggerPolicy_ptr);

void OBMarshal(LoggerPolicy_ptr, OB::OutputStreamImpl*);
void OBUnmarshal(LoggerPolicy_ptr&, OB::InputStreamImpl*);

typedef OB::ObjVar< LoggerPolicy > LoggerPolicy_var;
typedef OB::ObjOut< LoggerPolicy > LoggerPolicy_out;

//
// IDL:LOGGER_POLICY_ID:1.0
//
const ::CORBA::PolicyType LOGGER_POLICY_ID = 1010U;

//
// IDL:LoggerPolicy:1.0
//
class LoggerPolicy : virtual public ::CORBA::Policy
{
    LoggerPolicy(const LoggerPolicy&);
    void operator=(const LoggerPolicy&);

protected:

    static const char* ids_[];

public:

    LoggerPolicy() { }
    virtual ~LoggerPolicy() { }

    typedef LoggerPolicy_ptr _ptr_type;
    typedef LoggerPolicy_var _var_type;

    static inline LoggerPolicy_ptr
    _duplicate(LoggerPolicy_ptr p)
    {
        if(p)
            p -> _add_ref();
        return p;
    }

    static inline LoggerPolicy_ptr
    _nil()
    {
        return 0;
    }

    static LoggerPolicy_ptr _narrow(::CORBA::Object_ptr);

    static LoggerPolicy_ptr _narrow(::CORBA::AbstractBase_ptr);


    //
    // IDL:LoggerPolicy/level:1.0
    //
    virtual ::CORBA::Short level() = 0;
};

//
// IDL:LoggerPolicy:1.0
//
namespace CORBA
{

inline void
release(::LoggerPolicy_ptr p)
{
    if(p)
        p -> _remove_ref();
}

inline Boolean
is_nil(::LoggerPolicy_ptr p)
{
    return p == 0;
}

} // End of namespace CORBA

void operator<<=(::CORBA::Any&, LoggerPolicy_ptr*);
void operator<<=(::CORBA::Any&, LoggerPolicy_ptr);
CORBA::Boolean operator>>=(const ::CORBA::Any&, LoggerPolicy_ptr&);

inline void
operator<<=(::CORBA::Any_var& any, LoggerPolicy_ptr* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, LoggerPolicy_ptr val)
{
    any.inout() <<= val;
}

inline CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, LoggerPolicy_ptr& val)
{
    return any.in() >>= val;
}

#endif
