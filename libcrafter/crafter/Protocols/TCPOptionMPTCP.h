/*
Copyright (c) 2013, Gregory Detal
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
#ifndef TCPOPTIONMPTCP_H_
#define TCPOPTIONMPTCP_H_

#include "TCPOption.h"

#ifndef TCPOPT_MPTCP
#define TCPOPT_MPTCP 30
#endif

namespace Crafter {

    class TCPOptionMPTCP: public TCPOptionLayer {

        void DefineProtocol();

        Constructor GetConstructor() const {
            return TCPOptionMPTCP::TCPOptionMPTCPConstFunc;
        };

        static Layer* TCPOptionMPTCPConstFunc() {
            return new TCPOptionMPTCP;
        };

    protected:

        void Craft();

        static const byte_ FieldKind = 0;
        static const byte_ FieldLength = 1;
        static const byte_ FieldSubtype = 2;

    public:

        enum { PROTO = 0x9006 };

        TCPOptionMPTCP();

        void SetKind(const byte_& value) {
            SetFieldValue(FieldKind,value);
        };

        void SetLength(const byte_& value) {
            SetFieldValue(FieldLength,value);
        };

        void SetSubtype(const word& value) {
            SetFieldValue(FieldSubtype,value);
        };

        byte_  GetKind() const {
            return GetFieldValue<byte_>(FieldKind);
        };

        byte_  GetLength() const {
            return GetFieldValue<byte_>(FieldLength);
        };

        byte_ GetSubtype(const word& value) {
            return GetFieldValue<word>(FieldSubtype);
        };

        ~TCPOptionMPTCP() { /* Destructor */ };

        /* Build MPTCP options from subopt */
        static TCPOptionLayer* Build(byte_ subopt);

    };

    class TCPOptionMPTCPJoin : public TCPOptionMPTCP {

        void DefineProtocol();

        Constructor GetConstructor() const {
            return TCPOptionMPTCPJoin::TCPOptionMPTCPJoinConstFunc;
        };

        static Layer* TCPOptionMPTCPJoinConstFunc() {
            return new TCPOptionMPTCPJoin;
        };

        static const byte_ Blank = 3;
        static const byte_ BackupPath = 4;
        static const byte_ AddrID = 5;
        static const byte_ ReceiverToken = 6;
        static const byte_ SenderRandomNumber = 7;

    public:

        TCPOptionMPTCPJoin();

        enum { PROTO = 0x9009 };

        void SetBackupPath(const word& value) {
            SetFieldValue(BackupPath,value);
        };

        void SetAddrID(const byte_& value) {
            SetFieldValue(AddrID,value);
        };

        void SetReceiverToken(const uint32_t& value) {
            SetFieldValue(ReceiverToken,value);
        };

        void SetSenderRandomNumber(const uint32_t& value) {
            SetFieldValue(SenderRandomNumber,value);
        };

        word GetBackupPath() const {
            return GetFieldValue<word>(BackupPath);
        };

        byte_ GetAddrID() const {
            return GetFieldValue<byte_>(AddrID);
        };

        uint32_t GetReceiverToken() const {
            return GetFieldValue<uint32_t>(ReceiverToken);
        };

        uint32_t GetSenderRandomNumber() const {
            return GetFieldValue<uint32_t>(SenderRandomNumber);
        };

        void EnableBackupPath() {
            SetBackupPath(1);
        }

        void DisableBackupPath() {
            SetBackupPath(0);
        }

        ~TCPOptionMPTCPJoin() { /* Destructor */ };

    };



    class TCPOptionMPTCPCapable : public TCPOptionMPTCP {

        void DefineProtocol();

        Constructor GetConstructor() const {
            return TCPOptionMPTCPCapable::TCPOptionMPTCPCapableConstFunc;
        };

        static Layer* TCPOptionMPTCPCapableConstFunc() {
            return new TCPOptionMPTCPCapable;
        };

        static const byte_ Version = 3;
        static const byte_ Checksum = 4;
        static const byte_ Flags = 5;
        static const byte_ Crypto = 6;
        static const byte_ SenderKey = 7;

    public:

        TCPOptionMPTCPCapable();

        enum { PROTO = 0x9007 };

        void SetVersion(const word& value) {
            SetFieldValue(Version,value);
        };

        void SetChecksum(const word& value) {
            SetFieldValue(Checksum,value);
        };

        void SetCrypto(const word& value) {
            SetFieldValue(Crypto,value);
        };

        void SetSenderKey(const uint64_t& value) {
            SetFieldValue(SenderKey,value);
        };

        void SetReceiverKey(const uint64_t& value);

        byte_ GetVersion() const {
            return GetFieldValue<word>(Version);
        };

        byte_ GetChecksum() const {
            return GetFieldValue<word>(Checksum);
        };

        uint64_t GetSenderKey() const {
            return GetFieldValue<uint64_t>(SenderKey);
        };

        uint64_t GetReceiverKey() const;

        void EnableChecksum() {
            SetChecksum(1);
        }

        void DisableChecksum() {
            SetChecksum(0);
        }

        ~TCPOptionMPTCPCapable() { /* Destructor */ };

    };

}

#endif /* TCPOPTIONMPTCP_ */
