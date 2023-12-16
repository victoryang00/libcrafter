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

#include "DNS.h"

using namespace Crafter;
using namespace std;

void DNS::ReDefineActiveFields() {
}

void DNS::Craft() {
	/* Set the number of Queries */
	if (!IsFieldSet(FieldTotalQuestions)) {
		SetTotalQuestions(Queries.size());
		ResetField(FieldTotalQuestions);
	}

	/* Set the number of Answers */
	if (!IsFieldSet(FieldTotalAnswer)) {
		SetTotalAnswer(Answers.size());
		ResetField(FieldTotalAnswer);
	}

	/* Set the number of Authority data */
	if (!IsFieldSet(FieldTotalAuthority)) {
		SetTotalAuthority(Authority.size());
		ResetField(FieldTotalAuthority);
	}

	/* Set the number of Additional data */
	if (!IsFieldSet(FieldTotalAdditional)) {
		SetTotalAdditional(Additional.size());
		ResetField(FieldTotalAdditional);
	}

	/* Iterate through each Query to get the total size of the payload */
	vector<DNSQuery>::iterator it_query;
	size_t payload_size = 0;

	for(it_query  = Queries.begin() ; it_query != Queries.end() ; it_query++)
		payload_size += (*it_query).GetSize();

	/* Iterate through each Answer to get the total size of the payload */
	vector<DNSAnswer>::iterator it_ans;

	for(it_ans  = Answers.begin() ; it_ans != Answers.end() ; it_ans++)
		payload_size += (*it_ans).GetSize();

	/* Iterate through each Authority to get the total size of the payload */
	vector<DNSAnswer>::iterator it_auth;

	for(it_auth  = Authority.begin() ; it_auth != Authority.end() ; it_auth++)
		payload_size += (*it_auth).GetSize();

	/* Iterate through each Additional to get the total size of the payload */
	vector<DNSAnswer>::iterator it_add;

	for(it_add  = Additional.begin() ; it_add != Additional.end() ; it_add++)
		payload_size += (*it_add).GetSize();

	/* Create the raw data to add as a payload */
	byte_ *raw_payload = new byte_[payload_size];
	byte_ *cpy_ptr = raw_payload;

	/* Iterate through each Query and write the raw data */
	for(it_query  = Queries.begin() ; it_query != Queries.end() ; it_query++) {
		/* Write data */
		size_t nwrite = (*it_query).Write(cpy_ptr);
		/* Update the pointer */
		cpy_ptr += nwrite;
	}

	for(it_ans  = Answers.begin() ; it_ans != Answers.end() ; it_ans++) {
		/* Write data */
		size_t nwrite = (*it_ans).Write(cpy_ptr);
		/* Update the pointer */
		cpy_ptr += nwrite;
	}

	for(it_auth  = Authority.begin() ; it_auth != Authority.end() ; it_auth++) {
		/* Write data */
		size_t nwrite = (*it_auth).Write(cpy_ptr);
		/* Update the pointer */
		cpy_ptr += nwrite;
	}

	for(it_add  = Additional.begin() ; it_add != Additional.end() ; it_add++) {
		/* Write data */
		size_t nwrite = (*it_add).Write(cpy_ptr);
		/* Update the pointer */
		cpy_ptr += nwrite;
	}

	/* Set the payload of the layer */
	SetPayload(raw_payload,payload_size);

	delete[] raw_payload;
}

void SetContainerSection(vector<DNS::DNSAnswer>& container, ns_sect section, ns_msg* handle) {
	/* Allocate memory for buffer */
	char buff[MAXDNAME];

	/* Parse the Answers */
	for(size_t i = 0 ; i < ns_msg_count(*handle,section) ; i++) {
		/* RR data structure */
		ns_rr rr;
		/* Parse the data */
		if (ns_parserr(handle,section,i,&rr) < 0)
			throw std::runtime_error("DNS::SetContainerSection() : Error Parsing the Answers");

		/* Put zeros on the buffer */
		memset(buff, 0, MAXDNAME);

		/* Get the name associated with the answer */
        string qname = string(ns_rr_name(rr));

        /* Get the type */
        short_word qtype = ns_rr_type(rr);

        /* String for the RData */
        string rdata;

        if (qtype == DNS::TypeA || qtype == DNS::TypeAAAA) {
			/* Parse the IP address */
			const byte_* rdata_ptr = ns_rr_rdata(rr);

			char str[INET6_ADDRSTRLEN];
			inet_ntop(qtype == DNS::TypeA ? AF_INET : AF_INET6, rdata_ptr,
					str, sizeof(str));
			rdata = string(str);
		} else if(qtype == DNS::TypeOPT) {
			/* NO data */
			rdata="";
		} else {

			/* Expand the name domain name */
			if (ns_name_uncompress(
						ns_msg_base(*handle),/* Start of the message    */
						ns_msg_end(*handle), /* End of the message      */
						ns_rr_rdata(rr),     /* Position in the message */
						buff,                /* Result                  */
						MAXDNAME)            /* Size of buffer   */
								  < 0) {
				throw std::runtime_error("DNS::SetContainerSection() : Error Uncompressing the RData");
			}

			/* Put the data into a string */
			rdata = string(buff);
        }

	    /* Create the answer and push it into the container */
        DNS::DNSAnswer dns_answer(qname,rdata);

	    /* Set the Class */
        dns_answer.SetClass(ns_rr_class(rr));
        /* Set the type */
        dns_answer.SetType(qtype);
        /* Set the TTL */
        dns_answer.SetTTL(ns_rr_ttl(rr));

        container.push_back(dns_answer);
	}
}

void DNS::PrintPayload(ostream& str) const {
	str << "Payload = " << endl;

	vector<DNSQuery>::const_iterator it_query;
	for(it_query  = Queries.begin() ; it_query != Queries.end() ; it_query++) {
		(*it_query).Print(str);str << endl;
	}

	vector<DNSAnswer>::const_iterator it_ans;
	for(it_ans  = Answers.begin() ; it_ans != Answers.end() ; it_ans++) {
		(*it_ans).Print(str);str << endl;
	}

	vector<DNSAnswer>::const_iterator it_auth;
	for(it_auth  = Authority.begin() ; it_auth != Authority.end() ; it_auth++) {
		(*it_auth).Print(str);str << endl;
	}

	vector<DNSAnswer>::const_iterator it_add;
	for(it_add  = Additional.begin() ; it_add != Additional.end() ; it_add++) {
		(*it_add).Print(str);str << endl;
	}

}

void DNS::ParseFromBuffer(const byte_ *buf, size_t len)
{
	/* Initialize the response parser */
	ns_msg handle;
	if (ns_initparse(buf, len, &handle) < 0)
		throw std::runtime_error("DNS::ParseFromBuffer() : Error initializing the parsing routines");

	/* First, parse the queries... Simple */
	for(size_t i = 0 ; i < GetTotalQuestions() ; i++) {
		/* RR data structure */
		ns_rr rr;
		/* Parse the data */
		if (ns_parserr(&handle,ns_s_qd,i,&rr) < 0)
			throw std::runtime_error("DNS::ParseFromBuffer() : Error Parsing the Queries");
		/* Set the Query name */
        string qname = string(ns_rr_name(rr));
        /* Create a DNS Query and push it into the container */
        DNSQuery dns_query(qname);
        /* Set the class */
        dns_query.SetClass(ns_rr_class(rr));
        /* Set the type */
        dns_query.SetType(ns_rr_type(rr));

        Queries.push_back(dns_query);
	}

	SetContainerSection(Answers,ns_s_an,&handle);
	SetContainerSection(Authority,ns_s_ns,&handle);
	SetContainerSection(Additional,ns_s_ar,&handle);

	/* Kept from earlier ParseLayerInfo implementation, not sure why needed ? */
	Craft();
}

void DNS::FromRaw(const RawLayer& raw_layer) {
	if (raw_layer.GetSize() < GetHeaderSize())
		throw std::runtime_error("Cannot construct a DNS header from a too "
				"short RawLayer!");
	/* Parse the header */
	PutData(raw_layer.GetRawPointer());
	/* Parse the rest of it */
	ParseFromBuffer(raw_layer.GetRawPointer(), raw_layer.GetSize());
}

void DNS::ParseLayerData(ParseInfo* info) {
	ParseFromBuffer(info->raw_data + info->offset - GetHeaderSize(),
			info->total_size - info->offset + GetHeaderSize());
	info->offset = info->total_size;
	/* No more layers, default */
	info->top = 1;
}
