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

#ifndef ___CallStack_h__
#define ___CallStack_h__


#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030200L)
#       error ORBacus version mismatch!
#   endif
#endif

//
// IDL:CallStack:1.0
//
class OBUnique_CallStack { };

typedef OB::StrSeq< OBUnique_CallStack > CallStack;
typedef OB::SeqVar< OB::StrSeq< OBUnique_CallStack > > CallStack_var;
typedef OB::SeqOut< OB::StrSeq< OBUnique_CallStack > > CallStack_out;
extern OB::TypeCodeConst _tc_CallStack;

struct OBInfo_CallStack : public OB::ConstructedInfo
{
    OBInfo_CallStack() { }

    virtual void free(void* p) const
    {
        delete (CallStack*)p;
    }

    virtual void* dup(const void* p) const
    {
        return new CallStack(*(const CallStack*)p);
    }

    virtual void marshal(const void*, OB::OutputStreamImpl*) const;
    virtual void unmarshal(void*, OB::InputStreamImpl*) const;
};

//
// IDL:CallStack:1.0
//
void operator<<=(::CORBA::Any&, CallStack*);
void operator<<=(::CORBA::Any&, const CallStack&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const CallStack*&);

inline void
operator<<=(::CORBA::Any_var& any, CallStack* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const CallStack& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const CallStack*& val)
{
    return any.in() >>= val;
}

#endif
