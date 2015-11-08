// **********************************************************************
//
// Copyright (c) 2002
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

#include <OB/CORBA.h>

#include <PIDemo_impl.h>

// ----------------------------------------------------------------------
// PIDemo_impl constructor and destructor
// ----------------------------------------------------------------------

PIDemo_impl::PIDemo_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
    : orb_(CORBA::ORB::_duplicate(orb)),
      poa_(PortableServer::POA::_duplicate(poa))
{
}

// ----------------------------------------------------------------------
// PIDemo_impl public member implementation
// ----------------------------------------------------------------------

void
PIDemo_impl::setOtherObj(PIDemo_ptr obj)
{
    otherObj_ = PIDemo::_duplicate(obj);
}


//
// IDL:PIDemo/noargs:1.0
//
void
PIDemo_impl::noargs()
    throw(CORBA::SystemException)
{
}

//
// IDL:PIDemo/noargs_oneway:1.0
//
void
PIDemo_impl::noargs_oneway()
    throw(CORBA::SystemException)
{
}

//
// IDL:PIDemo/noargs_return:1.0
//
char*
PIDemo_impl::noargs_return()
    throw(CORBA::SystemException)
{
    return CORBA::string_dup("PIDemo");
}

//
// IDL:PIDemo/withargs:1.0
//
void
PIDemo_impl::withargs(const char* param1, char*& param2,
		      CORBA::String_out param3)
    throw(CORBA::SystemException)
{
    CORBA::string_free(param2);
    param2 = CORBA::string_dup("PIDemo");
    param3 = CORBA::string_dup("PIDemo");
}

//
// IDL:PIDemo/systemexception:1.0
//
void
PIDemo_impl::systemexception()
    throw(CORBA::SystemException)
{
    throw CORBA::NO_IMPLEMENT();
}

//
// IDL:PIDemo/userexception:1.0
//
void
PIDemo_impl::userexception()
    throw(PIDemo::User, CORBA::SystemException)
{
    throw PIDemo::User();
}

//
// IDL:PIDemo/switch_to_static_impl:1.0
//
void
PIDemo_impl::switch_to_static_impl()
    throw(CORBA::SystemException)
{
}

//
// IDL:PIDemo/switch_to_dynamic_impl:1.0
//
void
PIDemo_impl::switch_to_dynamic_impl()
    throw(CORBA::SystemException)
{
}

//
// IDL:PIDemo/call_other_impl:1.0
//
void
PIDemo_impl::call_other_impl(CORBA::Short level)
    throw(CORBA::SystemException)
{
    if(!CORBA::is_nil(otherObj_) && level > 0)
	otherObj_ -> call_other_impl(--level);
}

//
// IDL:PIDemo/deactivate:1.0
//
void
PIDemo_impl::deactivate()
    throw(CORBA::SystemException)
{
    orb_ -> shutdown(false);
}

