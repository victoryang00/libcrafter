/*
Copyright (c) 2012, Esteban Pellegrino
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ESTEBAN PELLEGRINO BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef IPV6ADDRESS_H_
#define IPV6ADDRESS_H_

#include <iostream>
#include <ostream>
#include <string>
#include "FieldInfo.h"
#include <arpa/inet.h>
#include <netinet/in.h>

namespace Crafter {

	class IPv6Address : public Field<std::string> {

		size_t nword;
		size_t nbyte;
		size_t offset;
        struct in6_addr addr;

		void PrintValue(std::ostream& str) const;

	public:

		IPv6Address(const std::string& name, size_t nword, size_t nbyte);

		void Write(byte_* raw_data) const;

		void Read(const byte_* raw_data);

		void SetField(const std::string& ip_address);

		FieldInfo* Clone() const;

        operator byte_*() {return (byte_*)&addr.s6_addr;}

		virtual ~IPv6Address();
	};

}

#endif /* IPV6ADDRESS_H_ */
