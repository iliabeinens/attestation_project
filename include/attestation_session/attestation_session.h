/*
 * \brief  Interface definition of the Attestation service
 * \author Björn Döbel
 * \date   2008-03-20
 */

/*
 * Copyright (C) 2008-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__HELLO_SESSION__HELLO_SESSION_H_
#define _INCLUDE__HELLO_SESSION__HELLO_SESSION_H_

#include <session/session.h>
#include <base/rpc.h>
#include <util/string.h>
typedef Genode::String<256> String;

namespace Attestation { struct Session; }


struct Attestation::Session : Genode::Session
{
	static const char *service_name() { return "Attestation"; }

	enum { CAP_QUOTA = 3 };

	virtual void say_attestation() = 0;
	virtual int add(int a, int b) = 0;
	virtual char* app_to_comp(int ID, int TimeStamp, int nonce) = 0;

	/*******************
	 ** RPC interface **
	 *******************/

	GENODE_RPC(Rpc_say_attestation, void, say_attestation);
	GENODE_RPC(Rpc_add, int, add, int, int);
	GENODE_RPC(Rpc_app_to_comp, char* , app_to_comp, int, int,int);
	GENODE_RPC_INTERFACE(Rpc_say_attestation, Rpc_add,Rpc_app_to_comp);
};

#endif /* _INCLUDE__HELLO_SESSION__HELLO_SESSION_H_ */
