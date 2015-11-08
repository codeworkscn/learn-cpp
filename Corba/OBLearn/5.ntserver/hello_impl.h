#ifndef ___hello_impl_h__
#define ___hello_impl_h__


#include <hello_skel.h>

//
// IDL:Hello:1.0
//
class Hello_impl : virtual public POA_Hello,
                   virtual public PortableServer::RefCountServantBase
{
    Hello_impl(const Hello_impl&);
    void operator=(const Hello_impl&);

    PortableServer::POA_var poa_;

public:

    Hello_impl(PortableServer::POA_ptr);
    ~Hello_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:Hello/say_hello:1.0
    //
    virtual void say_hello()
        throw(::CORBA::SystemException);

    //
    // IDL:Hello/shutdown:1.0
    //
    virtual void shutdown()
        throw(::CORBA::SystemException);
};

#endif
