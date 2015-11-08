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

#include <OB/CORBAServer.h>
#include <TestSrvObj_skel.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030200L)
#       error ORBacus version mismatch!
#   endif
#endif

//
// IDL:SERVICEOBJ:1.0
//

//
// IDL:SERVICEOBJ/A/opetater_a:1.0
//
void
POA_SERVICEOBJ::A::_OB_op_opetater_a(OB::Upcall_ptr _ob_up)
{
    _OB_preUnmarshal(_ob_up);
    _OB_postUnmarshal(_ob_up);
    opetater_a();
    _OB_postinvoke(_ob_up);
    _OB_preMarshal(_ob_up);
    _OB_postMarshal(_ob_up);
}

//
// IDL:SERVICEOBJ/A:1.0
//
::CORBA::Boolean
POA_SERVICEOBJ::A::_is_a(const char* type)
    throw(::CORBA::SystemException)
{
    const char** _ob_ids = SERVICEOBJ::A::_OB_staticIds();
    for(::CORBA::ULong _ob_i = 0; _ob_ids[_ob_i] != 0; ++_ob_i)
        if(strcmp(type, _ob_ids[_ob_i]) == 0)
            return true;

    return false;
}

::CORBA::RepositoryId
POA_SERVICEOBJ::A::_primary_interface(const PortableServer::ObjectId&,
                                      PortableServer::POA_ptr)
{
    return ::CORBA::string_dup(SERVICEOBJ::A::_OB_staticIds()[0]);
}

SERVICEOBJ::A_ptr
POA_SERVICEOBJ::A::_this()
{
    ::CORBA::Object_var obj = _OB_createReference();
    SERVICEOBJ::A_var result = SERVICEOBJ::A::_narrow(obj);
    return result._retn();
}

OB::DirectStubImpl_ptr
POA_SERVICEOBJ::A::_OB_createDirectStubImpl(PortableServer::POA_ptr poa,
                                            const PortableServer::ObjectId& oid)
{
    return new OBDirectStubImpl_SERVICEOBJ::A(poa, oid, this);
}

void
POA_SERVICEOBJ::A::_OB_dispatch(OB::Upcall_ptr _ob_up)
{
    static const char* _ob_names[] =
    {
        "opetater_a"
    };
    static const ::CORBA::ULong _ob_numNames = 1;

    switch(_OB_findOperation(_ob_up, _ob_names, _ob_numNames))
    {
    case 0: // opetater_a
        _OB_op_opetater_a(_ob_up);
        return;
    }

    _OB_dispatchBase(_ob_up);
}

//
// IDL:SERVICEOBJ/B/opetater_b:1.0
//
void
POA_SERVICEOBJ::B::_OB_op_opetater_b(OB::Upcall_ptr _ob_up)
{
    _OB_preUnmarshal(_ob_up);
    _OB_postUnmarshal(_ob_up);
    opetater_b();
    _OB_postinvoke(_ob_up);
    _OB_preMarshal(_ob_up);
    _OB_postMarshal(_ob_up);
}

//
// IDL:SERVICEOBJ/B:1.0
//
::CORBA::Boolean
POA_SERVICEOBJ::B::_is_a(const char* type)
    throw(::CORBA::SystemException)
{
    const char** _ob_ids = SERVICEOBJ::B::_OB_staticIds();
    for(::CORBA::ULong _ob_i = 0; _ob_ids[_ob_i] != 0; ++_ob_i)
        if(strcmp(type, _ob_ids[_ob_i]) == 0)
            return true;

    return false;
}

::CORBA::RepositoryId
POA_SERVICEOBJ::B::_primary_interface(const PortableServer::ObjectId&,
                                      PortableServer::POA_ptr)
{
    return ::CORBA::string_dup(SERVICEOBJ::B::_OB_staticIds()[0]);
}

SERVICEOBJ::B_ptr
POA_SERVICEOBJ::B::_this()
{
    ::CORBA::Object_var obj = _OB_createReference();
    SERVICEOBJ::B_var result = SERVICEOBJ::B::_narrow(obj);
    return result._retn();
}

OB::DirectStubImpl_ptr
POA_SERVICEOBJ::B::_OB_createDirectStubImpl(PortableServer::POA_ptr poa,
                                            const PortableServer::ObjectId& oid)
{
    return new OBDirectStubImpl_SERVICEOBJ::B(poa, oid, this);
}

void
POA_SERVICEOBJ::B::_OB_dispatch(OB::Upcall_ptr _ob_up)
{
    static const char* _ob_names[] =
    {
        "opetater_b"
    };
    static const ::CORBA::ULong _ob_numNames = 1;

    switch(_OB_findOperation(_ob_up, _ob_names, _ob_numNames))
    {
    case 0: // opetater_b
        _OB_op_opetater_b(_ob_up);
        return;
    }

    _OB_dispatchBase(_ob_up);
}

//
// IDL:SERVICEOBJ/CallBack/opetater_callBack:1.0
//
void
POA_SERVICEOBJ::CallBack::_OB_op_opetater_callBack(OB::Upcall_ptr _ob_up)
{
    OB::StrForStruct _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    _ob_a0 = _ob_in -> read_string();
    _OB_postUnmarshal(_ob_up);
    opetater_callBack(_ob_a0);
    _OB_postinvoke(_ob_up);
    _OB_preMarshal(_ob_up);
    _OB_postMarshal(_ob_up);
}

//
// IDL:SERVICEOBJ/CallBack:1.0
//
::CORBA::Boolean
POA_SERVICEOBJ::CallBack::_is_a(const char* type)
    throw(::CORBA::SystemException)
{
    const char** _ob_ids = SERVICEOBJ::CallBack::_OB_staticIds();
    for(::CORBA::ULong _ob_i = 0; _ob_ids[_ob_i] != 0; ++_ob_i)
        if(strcmp(type, _ob_ids[_ob_i]) == 0)
            return true;

    return false;
}

::CORBA::RepositoryId
POA_SERVICEOBJ::CallBack::_primary_interface(const PortableServer::ObjectId&,
                                             PortableServer::POA_ptr)
{
    return ::CORBA::string_dup(SERVICEOBJ::CallBack::_OB_staticIds()[0]);
}

SERVICEOBJ::CallBack_ptr
POA_SERVICEOBJ::CallBack::_this()
{
    ::CORBA::Object_var obj = _OB_createReference();
    SERVICEOBJ::CallBack_var result = SERVICEOBJ::CallBack::_narrow(obj);
    return result._retn();
}

OB::DirectStubImpl_ptr
POA_SERVICEOBJ::CallBack::_OB_createDirectStubImpl(PortableServer::POA_ptr poa,
                                                   const PortableServer::ObjectId& oid)
{
    return new OBDirectStubImpl_SERVICEOBJ::CallBack(poa, oid, this);
}

void
POA_SERVICEOBJ::CallBack::_OB_dispatch(OB::Upcall_ptr _ob_up)
{
    static const char* _ob_names[] =
    {
        "opetater_callBack"
    };
    static const ::CORBA::ULong _ob_numNames = 1;

    switch(_OB_findOperation(_ob_up, _ob_names, _ob_numNames))
    {
    case 0: // opetater_callBack
        _OB_op_opetater_callBack(_ob_up);
        return;
    }

    _OB_dispatchBase(_ob_up);
}

//
// IDL:SERVICEOBJ/AB/a_:1.0
//
void
POA_SERVICEOBJ::AB::_OB_get_a_(OB::Upcall_ptr _ob_up)
{
    _OB_preUnmarshal(_ob_up);
    _OB_postUnmarshal(_ob_up);
    ::SERVICEOBJ::A_var _ob_r = a_();
    _OB_postinvoke(_ob_up);
    OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_up);
    OBMarshal(_ob_r.in(), _ob_out);
    _OB_postMarshal(_ob_up);
}

void
POA_SERVICEOBJ::AB::_OB_set_a_(OB::Upcall_ptr _ob_up)
{
    ::SERVICEOBJ::A_var _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    OBUnmarshal(_ob_a0.inout(), _ob_in);
    _OB_postUnmarshal(_ob_up);
    a_(_ob_a0);
    _OB_postinvoke(_ob_up);
    _OB_preMarshal(_ob_up);
    _OB_postMarshal(_ob_up);
}

//
// IDL:SERVICEOBJ/AB/b_:1.0
//
void
POA_SERVICEOBJ::AB::_OB_get_b_(OB::Upcall_ptr _ob_up)
{
    _OB_preUnmarshal(_ob_up);
    _OB_postUnmarshal(_ob_up);
    ::SERVICEOBJ::B_var _ob_r = b_();
    _OB_postinvoke(_ob_up);
    OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_up);
    OBMarshal(_ob_r.in(), _ob_out);
    _OB_postMarshal(_ob_up);
}

void
POA_SERVICEOBJ::AB::_OB_set_b_(OB::Upcall_ptr _ob_up)
{
    ::SERVICEOBJ::B_var _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    OBUnmarshal(_ob_a0.inout(), _ob_in);
    _OB_postUnmarshal(_ob_up);
    b_(_ob_a0);
    _OB_postinvoke(_ob_up);
    _OB_preMarshal(_ob_up);
    _OB_postMarshal(_ob_up);
}

//
// IDL:SERVICEOBJ/AB/opetater_setCallBack:1.0
//
void
POA_SERVICEOBJ::AB::_OB_op_opetater_setCallBack(OB::Upcall_ptr _ob_up)
{
    ::SERVICEOBJ::CallBack_var _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    OBUnmarshal(_ob_a0.inout(), _ob_in);
    _OB_postUnmarshal(_ob_up);
    opetater_setCallBack(_ob_a0);
    _OB_postinvoke(_ob_up);
    _OB_preMarshal(_ob_up);
    _OB_postMarshal(_ob_up);
}

//
// IDL:SERVICEOBJ/AB:1.0
//
::CORBA::Boolean
POA_SERVICEOBJ::AB::_is_a(const char* type)
    throw(::CORBA::SystemException)
{
    const char** _ob_ids = SERVICEOBJ::AB::_OB_staticIds();
    for(::CORBA::ULong _ob_i = 0; _ob_ids[_ob_i] != 0; ++_ob_i)
        if(strcmp(type, _ob_ids[_ob_i]) == 0)
            return true;

    return false;
}

::CORBA::RepositoryId
POA_SERVICEOBJ::AB::_primary_interface(const PortableServer::ObjectId&,
                                       PortableServer::POA_ptr)
{
    return ::CORBA::string_dup(SERVICEOBJ::AB::_OB_staticIds()[0]);
}

SERVICEOBJ::AB_ptr
POA_SERVICEOBJ::AB::_this()
{
    ::CORBA::Object_var obj = _OB_createReference();
    SERVICEOBJ::AB_var result = SERVICEOBJ::AB::_narrow(obj);
    return result._retn();
}

OB::DirectStubImpl_ptr
POA_SERVICEOBJ::AB::_OB_createDirectStubImpl(PortableServer::POA_ptr poa,
                                             const PortableServer::ObjectId& oid)
{
    return new OBDirectStubImpl_SERVICEOBJ::AB(poa, oid, this);
}

void
POA_SERVICEOBJ::AB::_OB_dispatch(OB::Upcall_ptr _ob_up)
{
    static const char* _ob_names[] =
    {
        "_get_a_",
        "_get_b_",
        "_set_a_",
        "_set_b_",
        "opetater_setCallBack"
    };
    static const ::CORBA::ULong _ob_numNames = 5;

    switch(_OB_findOperation(_ob_up, _ob_names, _ob_numNames))
    {
    case 0: // _get_a_
        _OB_get_a_(_ob_up);
        return;

    case 1: // _get_b_
        _OB_get_b_(_ob_up);
        return;

    case 2: // _set_a_
        _OB_set_a_(_ob_up);
        return;

    case 3: // _set_b_
        _OB_set_b_(_ob_up);
        return;

    case 4: // opetater_setCallBack
        _OB_op_opetater_setCallBack(_ob_up);
        return;
    }

    _OB_dispatchBase(_ob_up);
}

//
// IDL:SERVICEOBJ/A:1.0
//
OBDirectStubImpl_SERVICEOBJ::A::A(
    PortableServer::POA_ptr poa,
    const PortableServer::ObjectId& oid,
    PortableServer::ServantBase* servant)
#ifdef HAVE_VCPLUSPLUS_BUGS
{
    _ob_initialize(poa, oid, servant);
}
#else
    : OB::DirectStubImpl(poa, oid, servant)
{
}
#endif

//
// IDL:SERVICEOBJ/A/opetater_a:1.0
//
void
OBDirectStubImpl_SERVICEOBJ::A::opetater_a()
{
    OB::InvocationHandler _ob_handler(this, "opetater_a");
    dynamic_cast<POA_SERVICEOBJ::A*>(_ob_servant_) -> opetater_a();
}

//
// IDL:SERVICEOBJ/B:1.0
//
OBDirectStubImpl_SERVICEOBJ::B::B(
    PortableServer::POA_ptr poa,
    const PortableServer::ObjectId& oid,
    PortableServer::ServantBase* servant)
#ifdef HAVE_VCPLUSPLUS_BUGS
{
    _ob_initialize(poa, oid, servant);
}
#else
    : OB::DirectStubImpl(poa, oid, servant)
{
}
#endif

//
// IDL:SERVICEOBJ/B/opetater_b:1.0
//
void
OBDirectStubImpl_SERVICEOBJ::B::opetater_b()
{
    OB::InvocationHandler _ob_handler(this, "opetater_b");
    dynamic_cast<POA_SERVICEOBJ::B*>(_ob_servant_) -> opetater_b();
}

//
// IDL:SERVICEOBJ/CallBack:1.0
//
OBDirectStubImpl_SERVICEOBJ::CallBack::CallBack(
    PortableServer::POA_ptr poa,
    const PortableServer::ObjectId& oid,
    PortableServer::ServantBase* servant)
#ifdef HAVE_VCPLUSPLUS_BUGS
{
    _ob_initialize(poa, oid, servant);
}
#else
    : OB::DirectStubImpl(poa, oid, servant)
{
}
#endif

//
// IDL:SERVICEOBJ/CallBack/opetater_callBack:1.0
//
void
OBDirectStubImpl_SERVICEOBJ::CallBack::opetater_callBack(const char* _ob_a0)
{
    OB::InvocationHandler _ob_handler(this, "opetater_callBack");
    dynamic_cast<POA_SERVICEOBJ::CallBack*>(_ob_servant_) -> opetater_callBack(_ob_a0);
}

//
// IDL:SERVICEOBJ/AB:1.0
//
OBDirectStubImpl_SERVICEOBJ::AB::AB(
    PortableServer::POA_ptr poa,
    const PortableServer::ObjectId& oid,
    PortableServer::ServantBase* servant)
#ifdef HAVE_VCPLUSPLUS_BUGS
{
    _ob_initialize(poa, oid, servant);
}
#else
    : OB::DirectStubImpl(poa, oid, servant)
{
}
#endif

//
// IDL:SERVICEOBJ/AB/a_:1.0
//
::SERVICEOBJ::A_ptr
OBDirectStubImpl_SERVICEOBJ::AB::a_()
{
    OB::InvocationHandler _ob_handler(this, "_get_a_");
    return dynamic_cast<POA_SERVICEOBJ::AB*>(_ob_servant_) -> a_();
}

void
OBDirectStubImpl_SERVICEOBJ::AB::a_(::SERVICEOBJ::A_ptr _ob_a)
{
    OB::InvocationHandler _ob_handler(this, "_set_a_");
    dynamic_cast<POA_SERVICEOBJ::AB*>(_ob_servant_) -> a_(_ob_a);
}

//
// IDL:SERVICEOBJ/AB/b_:1.0
//
::SERVICEOBJ::B_ptr
OBDirectStubImpl_SERVICEOBJ::AB::b_()
{
    OB::InvocationHandler _ob_handler(this, "_get_b_");
    return dynamic_cast<POA_SERVICEOBJ::AB*>(_ob_servant_) -> b_();
}

void
OBDirectStubImpl_SERVICEOBJ::AB::b_(::SERVICEOBJ::B_ptr _ob_a)
{
    OB::InvocationHandler _ob_handler(this, "_set_b_");
    dynamic_cast<POA_SERVICEOBJ::AB*>(_ob_servant_) -> b_(_ob_a);
}

//
// IDL:SERVICEOBJ/AB/opetater_setCallBack:1.0
//
void
OBDirectStubImpl_SERVICEOBJ::AB::opetater_setCallBack(::SERVICEOBJ::CallBack_ptr _ob_a0)
{
    OB::InvocationHandler _ob_handler(this, "opetater_setCallBack");
    dynamic_cast<POA_SERVICEOBJ::AB*>(_ob_servant_) -> opetater_setCallBack(_ob_a0);
}
