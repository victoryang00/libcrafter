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

#include "IPOption.h"

using namespace Crafter;
using namespace std;

static IPOptionPad SetOptionValue(byte_ value) {
	IPOptionPad pad;
	pad.SetOption(value);
	return pad;
}

const IPOptionPad IPOption::NOP = SetOptionValue(0x01);
const IPOptionPad IPOption::EOL = SetOptionValue(0x00);

IPOption::IPOption() {

    allocate_bytes(2);
    SetName("IPOption");
    SetprotoID(0x5000);
    DefineProtocol();

    SetCopyFlag(1);
    SetClass(0);
    SetOption(0);
    SetLength(0);

    ResetFields();

}

void IPOption::DefineProtocol() {
    Fields.push_back(new BitsField<1,0>("CopyFlag",0));
    Fields.push_back(new BitsField<2,1>("Class",0));
    Fields.push_back(new BitsField<5,3>("Option",0));
    Fields.push_back(new ByteField("Length",0,1));
}

