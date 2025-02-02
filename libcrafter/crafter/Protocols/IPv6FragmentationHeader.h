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
#ifndef IPV6FRAGMENTATIONHEADER_H_
#define IPV6FRAGMENTATIONHEADER_H_

#include "../Layer.h"

namespace Crafter {

    class IPv6FragmentationHeader: public Layer {

        void DefineProtocol();

        Constructor GetConstructor() const {
            return IPv6FragmentationHeader::IPv6FragmentationHeaderConstFunc;
        };

        static Layer* IPv6FragmentationHeaderConstFunc() {
            return new IPv6FragmentationHeader;
        };

        void Craft();

        void ReDefineActiveFields();

        void ParseLayerData(ParseInfo* info);

        static const byte_ FieldNextHeader = 0;
        static const byte_ FieldReserved = 1;
        static const byte_ FieldFragmentOffset = 2;
        static const byte_ FieldRes = 3;
        static const byte_ FieldMflag = 4;
        static const byte_ FieldIdentification = 5;

    public:

        enum { PROTO = 0x2c };

        IPv6FragmentationHeader();

        void SetNextHeader(const byte_& value) {
            SetFieldValue(FieldNextHeader,value);
        };

        void SetReserved(const byte_& value) {
            SetFieldValue(FieldReserved,value);
        };

        void SetFragmentOffset(const word& value) {
            SetFieldValue(FieldFragmentOffset,value);
        };

        void SetRes(const word& value) {
            SetFieldValue(FieldRes,value);
        };

        void SetMflag(const word& value) {
            SetFieldValue(FieldMflag,value);
        };

        void SetIdentification(const word& value) {
            SetFieldValue(FieldIdentification,value);
        };

        byte_  GetNextHeader() const {
            return GetFieldValue<byte_>(FieldNextHeader);
        };

        byte_  GetReserved() const {
            return GetFieldValue<byte_>(FieldReserved);
        };

        word  GetFragmentOffset() const {
            return GetFieldValue<word>(FieldFragmentOffset);
        };

        word  GetRes() const {
            return GetFieldValue<word>(FieldRes);
        };

        word  GetMflag() const {
            return GetFieldValue<word>(FieldMflag);
        };

        word  GetIdentification() const {
            return GetFieldValue<word>(FieldIdentification);
        };

        ~IPv6FragmentationHeader() { /* Destructor */ };

    };

}

#endif /* IPV6FRAGMENTATIONHEADER_H_ */
