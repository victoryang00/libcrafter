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
#ifndef SLL_H_
#define SLL_H_

#include "../Layer.h"

namespace Crafter {

    class SLL: public Layer {

        void DefineProtocol();

        Constructor GetConstructor() const {
            return SLL::SLLConstFunc;
        };

        static Layer* SLLConstFunc() {
            return new SLL;
        };

        void Craft();

        void ReDefineActiveFields();

		void ParseLayerData(ParseInfo* info);

        static const byte_ FieldPackeType = 0;
        static const byte_ FieldAddressType = 1;
        static const byte_ FieldAddressLength = 2;
        static const byte_ FieldSourceAddress = 3;
        static const byte_ FieldPad = 4;
        static const byte_ FieldProtocol = 5;

    public:

		enum { PROTO = 0xfff0 };

        SLL();

        void SetPackeType(const short_word& value) {
            SetFieldValue(FieldPackeType,value);
        };

        void SetAddressType(const short_word& value) {
            SetFieldValue(FieldAddressType,value);
        };

        void SetAddressLength(const short_word& value) {
            SetFieldValue(FieldAddressLength,value);
        };

        void SetSourceAddress(const std::string& value) {
            SetFieldValue(FieldSourceAddress,value);
        };

        void SetPad(const std::vector<byte_> & value) {
            SetFieldValue(FieldPad,value);
        };

        void SetProtocol(const short_word& value) {
            SetFieldValue(FieldProtocol,value);
        };

        short_word  GetPackeType() const {
            return GetFieldValue<short_word>(FieldPackeType);
        };

        short_word  GetAddressType() const {
            return GetFieldValue<short_word>(FieldAddressType);
        };

        short_word  GetAddressLength() const {
            return GetFieldValue<short_word>(FieldAddressLength);
        };

        std::string  GetSourceAddress() const {
            return GetFieldValue<std::string>(FieldSourceAddress);
        };

        std::vector<byte_>   GetPad() const {
            return GetFieldValue<std::vector<byte_> >(FieldPad);
        };

        short_word  GetProtocol() const {
            return GetFieldValue<short_word>(FieldProtocol);
        };

        ~SLL() { /* Destructor */ };

    };

}

#endif /* SLL_H_ */
