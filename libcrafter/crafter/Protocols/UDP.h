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
#ifndef UDP_H_
#define UDP_H_

#include "../Layer.h"

namespace Crafter {

    class UDP: public Layer {

        void DefineProtocol();

        Constructor GetConstructor() const {
            return UDP::UDPConstFunc;
        };

        static Layer* UDPConstFunc() {
            return new UDP;
        };

        void Craft();

        std::string MatchFilter() const;

        void ReDefineActiveFields();

        static const byte_ FieldSrcPort = 0;
        static const byte_ FieldDstPort = 1;
        static const byte_ FieldLength = 2;
        static const byte_ FieldCheckSum = 3;

    public:

		enum { PROTO = 0x11 };

        UDP();

        void SetSrcPort(const short_word& value) {
            SetFieldValue(FieldSrcPort,value);
        };

        void SetDstPort(const short_word& value) {
            SetFieldValue(FieldDstPort,value);
        };

        void SetLength(const short_word& value) {
            SetFieldValue(FieldLength,value);
        };

        void SetCheckSum(const short_word& value) {
            SetFieldValue(FieldCheckSum,value);
        };

        short_word  GetSrcPort() const {
            return GetFieldValue<short_word>(FieldSrcPort);
        };

        short_word  GetDstPort() const {
            return GetFieldValue<short_word>(FieldDstPort);
        };

        short_word  GetLength() const {
            return GetFieldValue<short_word>(FieldLength);
        };

        short_word  GetCheckSum() const {
            return GetFieldValue<short_word>(FieldCheckSum);
        };

        ~UDP() { /* Destructor */ };

    };

}

#endif /* UDP_H_ */
