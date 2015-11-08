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

#include <OB/CORBAClient.h>
#include <hello.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030200L)
#       error ORBacus version mismatch!
#   endif
#endif

::OB::TypeCodeConst _tc_Hello(
"010000000e00000022000000010000000e00000049444c3a48656c6c6f3a312e3000496406000"
"00048656c6c6f00"
);

//
// IDL:Hello:1.0
//
const char* Hello::ids_[] =
{
    "IDL:Hello:1.0",
    0
};

void
OBDuplicate(Hello_ptr p)
{
    if(p)
        p -> _add_ref();
}

void
OBRelease(Hello_ptr p)
{
    if(p)
        p -> _remove_ref();
}

Hello_ptr
Hello::_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        Hello_ptr v = 
            dynamic_cast< Hello_ptr >(p);
        if(v)
            return _duplicate(v);

        if(p -> _is_a(ids_[0]))
        {
            OBProxy_Hello* val = new OBProxy_Hello;
            val -> _OB_copyFrom(p);
            return val;
        }
    }

    return _nil();
}

Hello_ptr
Hello::_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        Hello_ptr v =
            dynamic_cast< Hello_ptr >(p);
        if(v)
            return _duplicate(v);

        ::CORBA::Object_var obj = p -> _to_object();
        return _narrow(obj);
    }
    return _nil();
}

Hello_ptr
Hello::_unchecked_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        Hello_ptr v =
            dynamic_cast< Hello_ptr >(p);
        if(v)
            return _duplicate(v);

        OBProxy_Hello* val = new OBProxy_Hello;
        val -> _OB_copyFrom(p);
        return val;
    }

    return _nil();
}

Hello_ptr
Hello::_unchecked_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        ::CORBA::Object_var obj = p -> _to_object();
        return _unchecked_narrow(obj);
    }
    return _nil();
}

const char**
Hello::_OB_staticIds()
{
    return ids_;
}

void
OBMarshal(Hello_ptr _ob_v, OB::OutputStreamImpl* _ob_out)
{
    _ob_out -> write_Object(_ob_v);
}

void
OBUnmarshal(Hello_ptr& _ob_v, OB::InputStreamImpl* _ob_in)
{
    Hello_var old = _ob_v;
    ::CORBA::Object_var p = _ob_in -> read_Object();

    if(!::CORBA::is_nil(p))
    {
        OBProxy_Hello* _ob_obj = new OBProxy_Hello;
        _ob_obj -> _OB_copyFrom(p);
        _ob_v = _ob_obj;
    }
    else
        _ob_v = Hello::_nil();
}

void
operator<<=(::CORBA::Any& any, Hello_ptr* v)
{
    any.replace(_tc_Hello, (::CORBA::Object_ptr)*v, true);
}

void
operator<<=(::CORBA::Any& any, Hello_ptr v)
{
    Hello_ptr val = Hello::_duplicate(v);
    any <<= &val;
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, Hello_ptr& v)
{
    if(any.check_type(_tc_Hello))
    {
        ::CORBA::Object_ptr val = (::CORBA::Object_ptr)any.value();

        if(!::CORBA::is_nil(val))
        {
            if(!(v = dynamic_cast< Hello_ptr >(val)))
            {
                OBProxy_Hello* obj = new OBProxy_Hello;
                obj -> _OB_copyFrom(val);
                v = obj;
                (::CORBA::Any&)any <<= &v;
            }
        }
        else
            v = Hello::_nil();

        return true;
    }
    else
        return false;
}

//
// IDL:Hello:1.0
//
OB::MarshalStubImpl_ptr
OBProxy_Hello::_OB_createMarshalStubImpl()
{
    return new OBMarshalStubImpl_Hello;
}

const char**
OBProxy_Hello::_OB_ids() const
{
    return ::Hello::ids_;
}

//
// IDL:Hello/say_hello:1.0
//
void
OBProxy_Hello::say_hello()
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_Hello_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_Hello_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> say_hello();
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:Hello/shutdown:1.0
//
void
OBProxy_Hello::shutdown()
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_Hello_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_Hello_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> shutdown();
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:Hello:1.0
//
void
OBDuplicate(OBStubImpl_Hello_ptr p)
{
    if(p)
        p -> _OB_incRef();
}

void
OBRelease(OBStubImpl_Hello_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

//
// IDL:Hello/say_hello:1.0
//
void
OBMarshalStubImpl_Hello::say_hello()
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("say_hello", true);
        try
        {
            _OB_preMarshal(_ob_down);
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            _OB_preUnmarshal(_ob_down);
            _OB_postUnmarshal(_ob_down);
            return;
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}

//
// IDL:Hello/shutdown:1.0
//
void
OBMarshalStubImpl_Hello::shutdown()
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("shutdown", true);
        try
        {
            _OB_preMarshal(_ob_down);
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            _OB_preUnmarshal(_ob_down);
            _OB_postUnmarshal(_ob_down);
            return;
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}
