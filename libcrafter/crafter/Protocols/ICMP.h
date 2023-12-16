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
#ifndef ICMP_H_
#define ICMP_H_

#include "../Layer.h"
#include "ICMPLayer.h"

namespace Crafter {

    class ICMP: public ICMPLayer {

        void DefineProtocol();

		byte_ MapTypeNumber(short_word type);

        Constructor GetConstructor() const {
            return ICMP::ICMPConstFunc;
        };

        static Layer* ICMPConstFunc() {
            return new ICMP;
        };

        void Craft();

        std::string MatchFilter() const ;

        void ReDefineActiveFields();

        void ParseLayerData(ParseInfo* info);

        static const byte_ FieldType = 0;
        static const byte_ FieldCode = 1;
        static const byte_ FieldCheckSum = 2;
        static const byte_ FieldRestOfHeader = 3;
        static const byte_ FieldIdentifier = 4;
        static const byte_ FieldSequenceNumber = 5;
        static const byte_ FieldPointer = 6;
        static const byte_ FieldGateway = 7;
        static const byte_ FieldLength = 8;
        static const byte_ FieldMTUNextHop = 9;

    public:

		enum { PROTO = 0x01 };

		/* ------- Messages types --------- */

		/* +++ Other +++ */
		static const byte_ SourceQuench;
		static const byte_ EchoRedirect;

		/* +++ Error messages +++ */
		static const byte_ DestinationUnreachable;
		static const byte_ TimeExceeded;
		static const byte_ ParameterProblem;

		/* +++ Request and replies +++ */
		static const byte_ EchoRequest;
		static const byte_ EchoReply;

		static const byte_ TimeStampRequest;
		static const byte_ TimeStampReply;

		static const byte_ InformationRequest;
		static const byte_ InformationReply;

		static const byte_ AddressMaskRequest;
		static const byte_ AddressMaskReply;

        ICMP();

        void SetType(const byte_& value) {
            SetFieldValue(FieldType,value);
        };

        void SetCode(const byte_& value) {
            SetFieldValue(FieldCode,value);
        };

        void SetCheckSum(const short_word& value) {
            SetFieldValue(FieldCheckSum,value);
        };

        void SetRestOfHeader(const word& value) {
            SetFieldValue(FieldRestOfHeader,value);
        };

        void SetIdentifier(const short_word& value) {
            SetFieldValue(FieldIdentifier,value);
        };

        void SetSequenceNumber(const short_word& value) {
            SetFieldValue(FieldSequenceNumber,value);
        };

        void SetPointer(const byte_& value) {
            SetFieldValue(FieldPointer,value);
        };

        void SetGateway(const std::string& value) {
            SetFieldValue(FieldGateway,value);
        };

        void SetLength(const byte_& value) {
            SetFieldValue(FieldLength,value);
        };

        void SetMTU(const short_word& value) {
            SetFieldValue(FieldMTUNextHop,value);
        };

        byte_  GetType() const {
            return GetFieldValue<byte_>(FieldType);
        };

        byte_  GetCode() const {
            return GetFieldValue<byte_>(FieldCode);
        };

        short_word  GetCheckSum() const {
            return GetFieldValue<short_word>(FieldCheckSum);
        };

        word  GetRestOfHeader() const {
            return GetFieldValue<word>(FieldRestOfHeader);
        };

        short_word  GetIdentifier() const {
            return GetFieldValue<short_word>(FieldIdentifier);
        };

        short_word  GetSequenceNumber() const {
            return GetFieldValue<short_word>(FieldSequenceNumber);
        };

        byte_  GetPointer() const {
            return GetFieldValue<byte_>(FieldPointer);
        };

        std::string  GetGateway() const {
            return GetFieldValue<std::string>(FieldGateway);
        };

        byte_  GetLength() const {
            return GetFieldValue<byte_>(FieldLength);
        };

        short_word GetMTU() {
        	return GetFieldValue<short_word>(FieldMTUNextHop);
        };

        ~ICMP() { /* Destructor */ };

    };

}

#endif /* ICMP_H_ */
