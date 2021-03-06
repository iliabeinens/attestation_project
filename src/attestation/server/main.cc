/*
 * \brief  Main program of the Attestation server
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
#include <base/heap.h>
#include <root/component.h>
#include <attestation_session/attestation_session.h>
#include <base/rpc_server.h>
#include <util/string.h>
namespace Attestation {
	struct Session_component;
	struct Root_component;
	struct Main;
}
typedef Genode::String<256> String;
char* myAtoi(int number)
{

	int copyNumber=number;
	int numberOfDigis=1;
	while(number/10 > 0)
	{
		numberOfDigis++;
		number/=10;
	}	
	number=copyNumber; //Restoring the value of number
	char result[numberOfDigis] ;
	for(int i=0;i<numberOfDigis;i++)
	{
		
		result[numberOfDigis-i-1]=number%10;
	}
	return result;
}

struct Attestation::Session_component : Genode::Rpc_object<Session>
{
	void say_attestation() {
		Genode::log("I am here... Attestation."); }

	int add(int a, int b) {
		return a + b; }
	char* app_to_comp(int ID, int TimeStamp, int nonce)
	{
		char* stringID = myAtoi(ID);
		char* stringTime = myAtoi(TimeStamp);
		char stringNonce = myAtoi(nonce);
		return stringID;
	}

};



class Attestation::Root_component
:
	public Genode::Root_component<Session_component>
{
	protected:

		Session_component *_create_session(const char *args)
		{
			Genode::log("creating attestation session");
			return new (md_alloc()) Session_component();
		}

	public:

		Root_component(Genode::Entrypoint &ep,
				Genode::Allocator &alloc)
			:
				Genode::Root_component<Session_component>(ep, alloc)
	{
		Genode::log("creating root component");
	}
};


struct Attestation::Main
{
	Genode::Env &env;

	/*
	 * A sliced heap is used for allocating session objects - thereby we
	 * can release objects separately.
	 */
	Genode::Sliced_heap sliced_heap { env.ram(), env.rm() };

	Attestation::Root_component root { env.ep(), sliced_heap };

	Main(Genode::Env &env) : env(env)
	{
		/*
		 * Create a RPC object capability for the root interface and
		 * announce the service to our parent.
		 */
		env.parent().announce(env.ep().manage(root));
	}
};


void Component::construct(Genode::Env &env)
{
	static Attestation::Main main(env);
}
