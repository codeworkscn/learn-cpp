#include <OB/CORBA.h>
#include <hello_impl.h>

//
// IDL:Hello:1.0
//
Hello_impl::Hello_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

Hello_impl::~Hello_impl()
{
}

PortableServer::POA_ptr
Hello_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:Hello/say_hello:1.0
//
void
Hello_impl::say_hello()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:Hello/shutdown:1.0
//
void
Hello_impl::shutdown()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}
