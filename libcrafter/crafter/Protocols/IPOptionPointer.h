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
#ifndef IPOPTIONLSRR_H_
#define IPOPTIONLSRR_H_

#include "IPOptionLayer.h"

namespace Crafter {

    class IPOptionPointer: public IPOptionLayer {

    protected:

        void DefineProtocol();

        void Craft();

        void ReDefineActiveFields();

        void ParseLayerData(ParseInfo* info);

        static const byte_ FieldCopyFlag = 0;
        static const byte_ FieldClass = 1;
        static const byte_ FieldOption = 2;
        static const byte_ FieldLength = 3;
        static const byte_ FieldPointer = 4;

    public:

        IPOptionPointer() { /* */ };

        void SetCopyFlag(const word& value) {
            SetFieldValue(FieldCopyFlag,value);
        };

        void SetClass(const word& value) {
            SetFieldValue(FieldClass,value);
        };

        void SetOption(const word& value) {
            SetFieldValue(FieldOption,value);
        };

        void SetLength(const byte_& value) {
            SetFieldValue(FieldLength,value);
        };

        void SetPointer(const byte_& value) {
            SetFieldValue(FieldPointer,value);
        };

        word  GetCopyFlag() const {
            return GetFieldValue<word>(FieldCopyFlag);
        };

        word  GetClass() const {
            return GetFieldValue<word>(FieldClass);
        };

        word  GetOption() const {
            return GetFieldValue<word>(FieldOption);
        };

        byte_  GetLength() const {
            return GetFieldValue<byte_>(FieldLength);
        };

        byte_  GetPointer() const {
            return GetFieldValue<byte_>(FieldPointer);
        };

        virtual ~IPOptionPointer() { /* Destructor */ };

    };

    class IPOptionLSRR : public IPOptionPointer {

    	Constructor GetConstructor() const {
            return IPOptionLSRR::IPOptionLSRRConstFunc;
        };

        static Layer* IPOptionLSRRConstFunc() {
            return new IPOptionLSRR;
        };

    public:

        IPOptionLSRR();

        enum { PROTO = 0x5003 };

        ~IPOptionLSRR() { /* Destructor */ };
    };

    class IPOptionRR : public IPOptionPointer {

    	Constructor GetConstructor() const {
            return IPOptionRR::IPOptionRRConstFunc;
        };

        static Layer* IPOptionRRConstFunc() {
            return new IPOptionRR;
        };

    public:

        IPOptionRR();

        enum { PROTO = 0x5004 };

        ~IPOptionRR() { /* Destructor */ };

    };

    class IPOptionSSRR : public IPOptionPointer {

    	Constructor GetConstructor() const {
            return IPOptionSSRR::IPOptionSSRRConstFunc;
        };

        static Layer* IPOptionSSRRConstFunc() {
            return new IPOptionSSRR;
        };

    public:

        IPOptionSSRR();

        enum { PROTO = 0x5005 };

        ~IPOptionSSRR() { /* Destructor */ };

    };
}

#endif /* IPOPTIONLSRR_H_ */
