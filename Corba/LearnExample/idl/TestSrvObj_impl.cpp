#include <OB/CORBA.h>
#include <TestSrvObj_impl.h>

//
// IDL:SERVICEOBJ:1.0
//

//
// IDL:SERVICEOBJ/A:1.0
//
SERVICEOBJ::A_impl::A_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

SERVICEOBJ::A_impl::~A_impl()
{
}

PortableServer::POA_ptr
SERVICEOBJ::A_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:SERVICEOBJ/A/opetater_a:1.0
//
void
SERVICEOBJ::A_impl::opetater_a()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:SERVICEOBJ/B:1.0
//
SERVICEOBJ::B_impl::B_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

SERVICEOBJ::B_impl::~B_impl()
{
}

PortableServer::POA_ptr
SERVICEOBJ::B_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:SERVICEOBJ/B/opetater_b:1.0
//
void
SERVICEOBJ::B_impl::opetater_b()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:SERVICEOBJ/CallBack:1.0
//
SERVICEOBJ::CallBack_impl::CallBack_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

SERVICEOBJ::CallBack_impl::~CallBack_impl()
{
}

PortableServer::POA_ptr
SERVICEOBJ::CallBack_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:SERVICEOBJ/CallBack/opetater_callBack:1.0
//
void
SERVICEOBJ::CallBack_impl::opetater_callBack(const char* message_)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:SERVICEOBJ/AB:1.0
//
SERVICEOBJ::AB_impl::AB_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

SERVICEOBJ::AB_impl::~AB_impl()
{
}

PortableServer::POA_ptr
SERVICEOBJ::AB_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:SERVICEOBJ/AB/a_:1.0
//
::SERVICEOBJ::A_ptr
SERVICEOBJ::AB_impl::a_()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::SERVICEOBJ::A_ptr _r = ::SERVICEOBJ::A::_nil();
    return _r;
}

void
SERVICEOBJ::AB_impl::a_(::SERVICEOBJ::A_ptr a)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:SERVICEOBJ/AB/b_:1.0
//
::SERVICEOBJ::B_ptr
SERVICEOBJ::AB_impl::b_()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::SERVICEOBJ::B_ptr _r = ::SERVICEOBJ::B::_nil();
    return _r;
}

void
SERVICEOBJ::AB_impl::b_(::SERVICEOBJ::B_ptr a)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:SERVICEOBJ/AB/opetater_setCallBack:1.0
//
void
SERVICEOBJ::AB_impl::opetater_setCallBack(::SERVICEOBJ::CallBack_ptr callback_)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}
