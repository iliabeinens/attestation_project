/*
 * \brief  Test client for the Attestation RPC interface
 * \author Björn Döbel
 * \author Norman Feske
 * \date   2008-03-20
 */

/*
 * Copyright (C) 2008-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/component.h>
#include <base/log.h>
#include <attestation_session/connection.h>


void Component::construct(Genode::Env &env)
{
	Attestation::Connection attestation(env);

	attestation.say_attestation();

	int const sum = attestation.add(2, 5);
	attestation.app_to_comp(2,2,2);
	Genode::log("added 2 + 5 = ", sum);
	Genode::log("attestation test completed");
}
