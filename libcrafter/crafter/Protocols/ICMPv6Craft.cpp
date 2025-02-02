/*
Copyright (c) 2012, Esteban Pellegrino
All rights reserved.

 + ICMP Extensions
Copyright (c) 2012, Bruno Nery

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

#include "ICMPv6.h"
#include "ICMPLayer.h"

using namespace Crafter;
using namespace std;

/* ------- Messages types --------- */

/* +++ Error messages +++ */
const byte_ ICMPv6::DestinationUnreachable = 1;
const byte_ ICMPv6::PacketTooBig = 2;
const byte_ ICMPv6::TimeExceeded = 3;
const byte_ ICMPv6::ParameterProblem = 4;

/* +++ Request and replies +++ */
const byte_ ICMPv6::EchoRequest = 128;
const byte_ ICMPv6::EchoReply = 129;

byte_ ICMPv6::MapTypeNumber(short_word type) {
	/* Get the type of message in function of the base type */
	if(type == ICMPLayer::DestinationUnreachable)
		return ICMPv6::DestinationUnreachable;
	else if(type == ICMPLayer::TimeExceeded)
		return ICMPv6::TimeExceeded;
	else if(type == ICMPLayer::ParameterProblem)
		return ICMPv6::ParameterProblem;
	else if(type == ICMPLayer::EchoReply)
		return ICMPv6::EchoReply;
	else if(type == ICMPLayer::EchoRequest)
		return ICMPv6::EchoRequest;
	return type;
}

void ICMPv6::ReDefineActiveFields() {
	/* Get the type of message and redefine fields */
	switch(GetType()) {

	case DestinationUnreachable:
                RedefineField(FieldLength);
		break;

	case PacketTooBig:
                RedefineField(FieldMTU);
		break;

	case TimeExceeded:
                RedefineField(FieldLength);
                break;

	case ParameterProblem:
		RedefineField(FieldPointer);
		break;

	case EchoReply:
		RedefineField(FieldIdentifier);
		RedefineField(FieldSequenceNumber);
		break;

	case EchoRequest:
		RedefineField(FieldIdentifier);
		RedefineField(FieldSequenceNumber);
		break;

	default:
		break;
	}
}

void ICMPv6::Craft() {
    word type = GetType();
    /* RFC4884: DestinationUnreachable and TimeExceeded can have extensions on IPv6 */
    if ((type == DestinationUnreachable || type == TimeExceeded) && !IsFieldSet(FieldLength)) {
        word length = 0;
        Layer* layer = GetTopLayer();
        /* Whatever comes before the ICMPExtension layer is counted on the length field */
        while (layer && layer->GetName() != "ICMPExtension") {
            length += layer->GetSize();
            /* Cheat: every sibling is a friend ;) */
            layer = layer->GetTopLayer();
        }
        SetLength(length / 8);
		if (layer && layer->GetName() == "ICMPExtension"
				&& (length < 128 || length % 8))
			PrintMessage(PrintCodes::PrintWarning,
					"Missing padding bytes between ICMP "
					"payload and extensions! (see RFC 4884)");
    }

    /* Checksum is handled by parent class */
    ICMPv6Layer::Craft();
}

string ICMPv6::MatchFilter() const {
	short_word type = GetType();

	if ( type == EchoRequest) {
		short_word ident = GetIdentifier();
		char str_ident[6];
		sprintf(str_ident,"%d",ident);
		str_ident[5] = 0;
		string ret_string = "(icmp6 and ip6[40]=129 and ip6[44:2] == " + string(str_ident) + ") ";
		return ret_string;
	} else
		return " icmp6 ";
}

void ICMPv6::ParseLayerData(ParseInfo* info) {
    word icmp_type = GetType();

	/* Per RFC 4884, §5.5/5.4, specific ICMP types may have extensions,
	 * beside their "original datagram" field */
    if (icmp_type == ICMPv6::DestinationUnreachable
				|| icmp_type == ICMPv6::TimeExceeded)
		ICMPLayer::parseExtensionHeader(info, 8 * GetLength());
	else
		/* No more layers */
		info->top = 1;
}
