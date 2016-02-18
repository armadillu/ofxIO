// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofx/IO/HexBinaryEncoding.h"
#include <stdint.h>
#include "Poco/HexBinaryEncoder.h"
#include "Poco/HexBinaryDecoder.h"
#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace IO {


HexBinaryEncoding::HexBinaryEncoding()
{
}


HexBinaryEncoding::~HexBinaryEncoding()
{
}


std::size_t HexBinaryEncoding::encode(const ByteBuffer& buffer,
                                      ByteBuffer& encodedBuffer)
{
    std::stringstream ss;
    Poco::HexBinaryEncoder _encoder(ss);
    ByteBuffer byteBuffer(buffer.readBytes());
    ByteBufferUtils::copyBufferToStream(byteBuffer, _encoder);
    _encoder.close(); // Flush bytes.
    encodedBuffer.writeBytes(ss.str());
    return encodedBuffer.size();
}

std::size_t HexBinaryEncoding::decode(const ByteBuffer& buffer,
                                      ByteBuffer& decodedBuffer)
{
    ByteBuffer byteBuffer(buffer.readBytes());
    std::stringstream ss;
    ss << byteBuffer;
    Poco::HexBinaryDecoder _decoder(ss);
    ByteBuffer decoded;
    ByteBufferUtils::copyStreamToBuffer(_decoder, decoded);
    decodedBuffer.writeBytes(decoded);
    return decodedBuffer.size();
}


} }  // namespace ofx::IO
