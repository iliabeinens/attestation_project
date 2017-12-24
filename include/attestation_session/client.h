/*
 * \brief  Client-side interface of the Attestation service
 * \author Björn Döbel
 * \date   2008-03-20
 */

/*
 * Copyright (C) 2008-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__HELLO_SESSION_H__CLIENT_H_
#define _INCLUDE__HELLO_SESSION_H__CLIENT_H_

#include <attestation_session/attestation_session.h>
#include <base/rpc_client.h>
#include <base/log.h>

namespace Attestation { struct Session_client; }


struct Attestation::Session_client : Genode::Rpc_client<Session>
{
	Session_client(Genode::Capability<Session> cap)
	: Genode::Rpc_client<Session>(cap) { }

	void say_attestation()
	{
		Genode::log("issue RPC for saying attestation");
		call<Rpc_say_attestation>();
		Genode::log("returned from 'say_attestation' RPC call");
	}

	int add(int a, int b)
	{
		return call<Rpc_add>(a, b);
	}
	char* testIlya(int a)
	{
		return call<Rpc_testIlya>(a);
	}
};

#endif /* _INCLUDE__HELLO_SESSION_H__CLIENT_H_ */
