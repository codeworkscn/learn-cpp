#ifndef ___TestSrvObj_impl_h__
#define ___TestSrvObj_impl_h__


#include <TestSrvObj_skel.h>

//
// IDL:SERVICEOBJ:1.0
//
namespace SERVICEOBJ
{

//
// IDL:SERVICEOBJ/A:1.0
//
class A_impl : virtual public POA_SERVICEOBJ::A,
               virtual public PortableServer::RefCountServantBase
{
    A_impl(const A_impl&);
    void operator=(const A_impl&);

    PortableServer::POA_var poa_;

public:

    A_impl(PortableServer::POA_ptr);
    ~A_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:SERVICEOBJ/A/opetater_a:1.0
    //
    virtual void opetater_a()
        throw(::CORBA::SystemException);
};

//
// IDL:SERVICEOBJ/B:1.0
//
class B_impl : virtual public POA_SERVICEOBJ::B,
               virtual public PortableServer::RefCountServantBase
{
    B_impl(const B_impl&);
    void operator=(const B_impl&);

    PortableServer::POA_var poa_;

public:

    B_impl(PortableServer::POA_ptr);
    ~B_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:SERVICEOBJ/B/opetater_b:1.0
    //
    virtual void opetater_b()
        throw(::CORBA::SystemException);
};

//
// IDL:SERVICEOBJ/CallBack:1.0
//
class CallBack_impl : virtual public POA_SERVICEOBJ::CallBack,
                      virtual public PortableServer::RefCountServantBase
{
    CallBack_impl(const CallBack_impl&);
    void operator=(const CallBack_impl&);

    PortableServer::POA_var poa_;

public:

    CallBack_impl(PortableServer::POA_ptr);
    ~CallBack_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:SERVICEOBJ/CallBack/opetater_callBack:1.0
    //
    virtual void opetater_callBack(const char* message_)
        throw(::CORBA::SystemException);
};

//
// IDL:SERVICEOBJ/AB:1.0
//
class AB_impl : virtual public POA_SERVICEOBJ::AB,
                virtual public PortableServer::RefCountServantBase
{
    AB_impl(const AB_impl&);
    void operator=(const AB_impl&);

    PortableServer::POA_var poa_;

public:

    AB_impl(PortableServer::POA_ptr);
    ~AB_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:SERVICEOBJ/AB/a_:1.0
    //
    virtual ::SERVICEOBJ::A_ptr a_()
        throw(::CORBA::SystemException);
    virtual void a_(::SERVICEOBJ::A_ptr)
        throw(::CORBA::SystemException);

    //
    // IDL:SERVICEOBJ/AB/b_:1.0
    //
    virtual ::SERVICEOBJ::B_ptr b_()
        throw(::CORBA::SystemException);
    virtual void b_(::SERVICEOBJ::B_ptr)
        throw(::CORBA::SystemException);

    //
    // IDL:SERVICEOBJ/AB/opetater_setCallBack:1.0
    //
    virtual void opetater_setCallBack(::SERVICEOBJ::CallBack_ptr callback_)
        throw(::CORBA::SystemException);
};

} // End of namespace SERVICEOBJ

#endif
