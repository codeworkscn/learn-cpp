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

#ifndef ___TestSrvObj_skel_h__
#define ___TestSrvObj_skel_h__

#include <TestSrvObj.h>


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
namespace POA_SERVICEOBJ
{

//
// IDL:SERVICEOBJ/A:1.0
//
class A : virtual public PortableServer::ServantBase
{
    A(const A&);
    void operator=(const A&);

protected:

    //
    // IDL:SERVICEOBJ/A/opetater_a:1.0
    //
    void _OB_op_opetater_a(OB::Upcall_ptr);

public:

    A() { }

    virtual ::CORBA::Boolean _is_a(const char*)
        throw(::CORBA::SystemException);

    virtual ::CORBA::RepositoryId _primary_interface(
        const PortableServer::ObjectId&,
        PortableServer::POA_ptr);

    SERVICEOBJ::A_ptr _this();

    virtual OB::DirectStubImpl_ptr _OB_createDirectStubImpl(
        PortableServer::POA_ptr,
        const PortableServer::ObjectId&);
    virtual void _OB_dispatch(OB::Upcall_ptr);

    //
    // IDL:SERVICEOBJ/A/opetater_a:1.0
    //
    virtual void opetater_a()
        throw(::CORBA::SystemException) = 0;
};

//
// IDL:SERVICEOBJ/B:1.0
//
class B : virtual public PortableServer::ServantBase
{
    B(const B&);
    void operator=(const B&);

protected:

    //
    // IDL:SERVICEOBJ/B/opetater_b:1.0
    //
    void _OB_op_opetater_b(OB::Upcall_ptr);

public:

    B() { }

    virtual ::CORBA::Boolean _is_a(const char*)
        throw(::CORBA::SystemException);

    virtual ::CORBA::RepositoryId _primary_interface(
        const PortableServer::ObjectId&,
        PortableServer::POA_ptr);

    SERVICEOBJ::B_ptr _this();

    virtual OB::DirectStubImpl_ptr _OB_createDirectStubImpl(
        PortableServer::POA_ptr,
        const PortableServer::ObjectId&);
    virtual void _OB_dispatch(OB::Upcall_ptr);

    //
    // IDL:SERVICEOBJ/B/opetater_b:1.0
    //
    virtual void opetater_b()
        throw(::CORBA::SystemException) = 0;
};

//
// IDL:SERVICEOBJ/CallBack:1.0
//
class CallBack : virtual public PortableServer::ServantBase
{
    CallBack(const CallBack&);
    void operator=(const CallBack&);

protected:

    //
    // IDL:SERVICEOBJ/CallBack/opetater_callBack:1.0
    //
    void _OB_op_opetater_callBack(OB::Upcall_ptr);

public:

    CallBack() { }

    virtual ::CORBA::Boolean _is_a(const char*)
        throw(::CORBA::SystemException);

    virtual ::CORBA::RepositoryId _primary_interface(
        const PortableServer::ObjectId&,
        PortableServer::POA_ptr);

    SERVICEOBJ::CallBack_ptr _this();

    virtual OB::DirectStubImpl_ptr _OB_createDirectStubImpl(
        PortableServer::POA_ptr,
        const PortableServer::ObjectId&);
    virtual void _OB_dispatch(OB::Upcall_ptr);

    //
    // IDL:SERVICEOBJ/CallBack/opetater_callBack:1.0
    //
    virtual void opetater_callBack(const char* message_)
        throw(::CORBA::SystemException) = 0;
};

//
// IDL:SERVICEOBJ/AB:1.0
//
class AB : virtual public PortableServer::ServantBase
{
    AB(const AB&);
    void operator=(const AB&);

protected:

    //
    // IDL:SERVICEOBJ/AB/a_:1.0
    //
    void _OB_get_a_(OB::Upcall_ptr);
    void _OB_set_a_(OB::Upcall_ptr);

    //
    // IDL:SERVICEOBJ/AB/b_:1.0
    //
    void _OB_get_b_(OB::Upcall_ptr);
    void _OB_set_b_(OB::Upcall_ptr);

    //
    // IDL:SERVICEOBJ/AB/opetater_setCallBack:1.0
    //
    void _OB_op_opetater_setCallBack(OB::Upcall_ptr);

public:

    AB() { }

    virtual ::CORBA::Boolean _is_a(const char*)
        throw(::CORBA::SystemException);

    virtual ::CORBA::RepositoryId _primary_interface(
        const PortableServer::ObjectId&,
        PortableServer::POA_ptr);

    SERVICEOBJ::AB_ptr _this();

    virtual OB::DirectStubImpl_ptr _OB_createDirectStubImpl(
        PortableServer::POA_ptr,
        const PortableServer::ObjectId&);
    virtual void _OB_dispatch(OB::Upcall_ptr);

    //
    // IDL:SERVICEOBJ/AB/a_:1.0
    //
    virtual ::SERVICEOBJ::A_ptr a_()
        throw(::CORBA::SystemException) = 0;
    virtual void a_(::SERVICEOBJ::A_ptr)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:SERVICEOBJ/AB/b_:1.0
    //
    virtual ::SERVICEOBJ::B_ptr b_()
        throw(::CORBA::SystemException) = 0;
    virtual void b_(::SERVICEOBJ::B_ptr)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:SERVICEOBJ/AB/opetater_setCallBack:1.0
    //
    virtual void opetater_setCallBack(::SERVICEOBJ::CallBack_ptr callback_)
        throw(::CORBA::SystemException) = 0;
};

} // End of namespace POA_SERVICEOBJ

//
// IDL:SERVICEOBJ:1.0
//
namespace OBDirectStubImpl_SERVICEOBJ
{

//
// IDL:SERVICEOBJ/A:1.0
//
class A : virtual public OBStubImpl_SERVICEOBJ::A,
          virtual public OB::DirectStubImpl
{
    A(const A&);
    void operator=(const A&);

protected:

#ifdef HAVE_VCPLUSPLUS_BUGS

    A() { }

#endif

    A(PortableServer::POA_ptr,
      const PortableServer::ObjectId&,
      PortableServer::ServantBase*);

    friend class POA_SERVICEOBJ::A;

public:

    //
    // IDL:SERVICEOBJ/A/opetater_a:1.0
    //
    virtual void opetater_a();
};

//
// IDL:SERVICEOBJ/B:1.0
//
class B : virtual public OBStubImpl_SERVICEOBJ::B,
          virtual public OB::DirectStubImpl
{
    B(const B&);
    void operator=(const B&);

protected:

#ifdef HAVE_VCPLUSPLUS_BUGS

    B() { }

#endif

    B(PortableServer::POA_ptr,
      const PortableServer::ObjectId&,
      PortableServer::ServantBase*);

    friend class POA_SERVICEOBJ::B;

public:

    //
    // IDL:SERVICEOBJ/B/opetater_b:1.0
    //
    virtual void opetater_b();
};

//
// IDL:SERVICEOBJ/CallBack:1.0
//
class CallBack : virtual public OBStubImpl_SERVICEOBJ::CallBack,
                 virtual public OB::DirectStubImpl
{
    CallBack(const CallBack&);
    void operator=(const CallBack&);

protected:

#ifdef HAVE_VCPLUSPLUS_BUGS

    CallBack() { }

#endif

    CallBack(PortableServer::POA_ptr,
             const PortableServer::ObjectId&,
             PortableServer::ServantBase*);

    friend class POA_SERVICEOBJ::CallBack;

public:

    //
    // IDL:SERVICEOBJ/CallBack/opetater_callBack:1.0
    //
    virtual void opetater_callBack(const char* message_);
};

//
// IDL:SERVICEOBJ/AB:1.0
//
class AB : virtual public OBStubImpl_SERVICEOBJ::AB,
           virtual public OB::DirectStubImpl
{
    AB(const AB&);
    void operator=(const AB&);

protected:

#ifdef HAVE_VCPLUSPLUS_BUGS

    AB() { }

#endif

    AB(PortableServer::POA_ptr,
       const PortableServer::ObjectId&,
       PortableServer::ServantBase*);

    friend class POA_SERVICEOBJ::AB;

public:

    //
    // IDL:SERVICEOBJ/AB/a_:1.0
    //
    virtual ::SERVICEOBJ::A_ptr a_();
    virtual void a_(::SERVICEOBJ::A_ptr);

    //
    // IDL:SERVICEOBJ/AB/b_:1.0
    //
    virtual ::SERVICEOBJ::B_ptr b_();
    virtual void b_(::SERVICEOBJ::B_ptr);

    //
    // IDL:SERVICEOBJ/AB/opetater_setCallBack:1.0
    //
    virtual void opetater_setCallBack(::SERVICEOBJ::CallBack_ptr callback_);
};

} // End of namespace OBDirectStubImpl_SERVICEOBJ

#endif