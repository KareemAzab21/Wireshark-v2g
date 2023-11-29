/************************************************************************************
 *
 * @author : Youssef Hussien and Tasneem Essmat
 *
 * @version 20-10-2022
 *
 * @contact ysfhussien@gmail.com
 *			tasneemessmat@gmail.com
 *
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 * File Name: EncoderChannel.h
 *
 * Description: header file of EXI Encoder Channel
 *
************************************************************************************/

/**
 * \file 	EncoderChannel.h
 * \brief 	EXI Encoder Channel
 *
 */

#ifndef ENCODER_CHANNEL_H
#define ENCODER_CHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------- File Includes ------------------------------------- */
#include "EXITypes.h"

/*---------------------------------- APIs declarations -----------------------------------*/


/************************************************************************************
 * Service Name: encode
 * Service ID[hex]: 0x12
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,byte value needed to be encoded
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode a single byte value of data with a given value
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/

int encode(bitstream_t* stream, uint8_t b);

/************************************************************************************
 * Service Name: encodeBoolean
 * Service ID[hex]: 0x13
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,boolean value needed to be encoded
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode a single boolean value.
				A false value is encoded as bit 0
				and true value is encode as bit 1.
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/

int encodeBoolean(bitstream_t* stream, int b);


/************************************************************************************
 * Service Name: encodeNBitUnsignedInteger
 * Service ID[hex]: 0x14
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Output stream container
					nbits  - Number of bits that will be encoded
 	 	 	 	 	val    - int value needed to be encoded
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode n-bit unsigned integer. The n least significant
				bits of parameter b starting with the most significant,
				i.e. from left to right.
				The n-bit unsigned integer is used for representing event codes,
				the prefix component of QNames and certain value content items
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeNBitUnsignedInteger(bitstream_t* stream, size_t nbits, uint32_t val);


/************************************************************************************
 * Service Name: encodeUnsignedInteger
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container, Pointer to Unsigned integer value container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to determine the unsigned integer value type that will be used in encoding
 * Available via: EncoderChannel.h
 * Requirement:
************************************************************************************/
int encodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv);


/************************************************************************************
 * Service Name: encodeUnsignedInteger16
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Unsigned integer value 16 bits holding
 	 	 	 	 	the value of the stream
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode an arbitrary precision non negative integer
 	 	 	 	using a sequence of octets. The most significant bit of the last octet is set to
 	 	 	 	zero to indicate sequence termination. Only seven bits per octet are used to
				store the integer's value and the most significant bit of all octets is 1
 	 	 	 	except last octet as mentioned before, It supports numbers less than 2097152
 * Available via: EncoderChannel.h
 * Requirement:
************************************************************************************/

int encodeUnsignedInteger16(bitstream_t* stream, uint16_t streamValue);



/************************************************************************************
 * Service Name: encodeUnsignedInteger32
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Unsigned integer value 32 bits holding
 	 	 	 	 	the value of the stream
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of any failure)
 * Return value: int
 * Description: Function to Encode an arbitrary precision non negative integer
  	  	  	  	using a sequence of octets. The most significant bit of the last octet is set to
 	 	 	 	zero to indicate sequence termination. Only seven bits per octet are used to
 	 	 	 	store the integer's value and the most significant bit of all octets is 1
 	 	 	    except last octet as mentioned before,It supports numbers less than 2147483648
 * Available via: EncoderChannel.h
 * Requirement:
************************************************************************************/
int encodeUnsignedInteger32(bitstream_t* stream, uint32_t n);


/************************************************************************************
 * Service Name: encodeUnsignedInteger64
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Unsigned integer value 64 bits holding
					the value of the stream
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of any failure)
 * Return value: int
 * Description: Function to Encode an arbitrary precision non negative integer
  	  	  	  	using a sequence of octets. The most significant bit of the last octet is set to
 	 	 	 	zero to indicate sequence termination. Only seven bits per octet are used to
 	 	 	 	store the integer's value and the most significant bit of all octets is 1
 	 	 	    except last octet as mentioned before.
 * Available via: EncoderChannel.h
 * Requirement:
************************************************************************************/
int encodeUnsignedInteger64(bitstream_t* stream, uint64_t streamValue);

/************************************************************************************
 * Service Name: encodeUnsignedIntegerBig
 * Service ID[hex]: 0x06
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Output Stream container
 					size -   size array
  	  	  	  	  	data -   Pointer to data array
  	  	  	  	  	len - 	 length array indicating total number of bytes to be encoded
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of any failure)
 * Return value: int
 * Description: Function to Encode an arbitrary precision non negative integer
  	  	  	  	using a sequence of octets. The most significant bit of the last octet is set to
 	 	 	 	zero to indicate sequence termination. Only seven bits per octet are used to
 	 	 	 	store the integer's value and the most significant bit of all octets is 1
 	 	 	    except last octet as mentioned before.
 * Available via: EncoderChannel.h
 * Requirement:
************************************************************************************/
int encodeUnsignedIntegerBig(bitstream_t* stream, size_t size, uint8_t* data, size_t len);


/************************************************************************************
 * Service Name: encodeInteger
 * Service ID[hex]: 0x07
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container, Pointer to Integer value container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to determine the integer value type that will be used in encoding
 * Available via: EncoderChannel.h
 * Requirement:
************************************************************************************/
int encodeInteger(bitstream_t* stream, exi_integer_t* iv);


/************************************************************************************
 * Service Name: encodeInteger16
 * Service ID[hex]: 0x08
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Integer value 16 bits holding the value of the stream
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode an arbitrary precision integer using a sign bit followed
 	 	 	 	by a sequence of octets. The most significant bit of the last octet is set
 	 	 	 	to zero to indicate sequence termination. Only seven bits per octet are used
				to store the integer's value.
				A sign value of zero (0) is used to represent positive values and
				a sign value of one (1) is used to represent negative values
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeInteger16(bitstream_t* stream, int16_t n);

/************************************************************************************
 * Service Name: encodeInteger32
 * Service ID[hex]: 0x09
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Integer value 32 bits holding the value of the stream
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode an arbitrary precision integer using a sign bit followed
 	 	 	 	by a sequence of octets. The most significant bit of the last octet is set
 	 	 	 	to zero to indicate sequence termination. Only seven bits per octet are used
				to store the integer's value.
				A sign value of zero (0) is used to represent positive values and
				a sign value of one (1) is used to represent negative values
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeInteger32(bitstream_t* stream, int32_t n);


/************************************************************************************
 * Service Name: encodeInteger64
 * Service ID[hex]: 0x0A
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Integer value 64 bits holding the value of the stream
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode an arbitrary precision integer using a sign bit followed
 	 	 	 	by a sequence of octets. The most significant bit of the last octet is set
 	 	 	 	to zero to indicate sequence termination. Only seven bits per octet are used
				to store the integer's value.
				A sign value of zero (0) is used to represent positive values and
				a sign value of one (1) is used to represent negative values
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeInteger64(bitstream_t* stream, int64_t n);

/************************************************************************************
 * Service Name: encodeIntegerBig
 * Service ID[hex]: 0x0B
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream   - Pointer to Output Stream container
 	 	 	 	 	negative - integer to indicate the sign
 	 	 	 	 	size -   size array
 	 	 	 	 	data - Pointer to data array
  	  	  	  	  	len  - length array indicating total number of bytes to be encoded
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode an arbitrary precision integer using a sign bit followed
 	 	 	 	by a sequence of octets. The most significant bit of the last octet is set
 	 	 	 	to zero to indicate sequence termination. Only seven bits per octet are used
				to store the integer's value.
				A sign value of zero (0) is used to represent positive values and
				a sign value of one (1) is used to represent negative values
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeIntegerBig(bitstream_t* stream, int negative, size_t size, uint8_t* data, size_t len);

/************************************************************************************
 * Service Name: encodeFloat
 * Service ID[hex]: 0x0C
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Pointer to float value container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode float numbers, The Float datatype representation is
				two consecutive Integers.The first Integer represents the mantissa of the
				floating point number and the second Integer represents the base-10 exponent
				of the floating point number.
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeFloat(bitstream_t* stream, exi_float_me_t* f);


/************************************************************************************
 * Service Name: encodeDecimal
 * Service ID[hex]: 0x0D
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Pointer to decimal value container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode a decimal represented as a Boolean sign followed by two Unsigned
 	 	 	 	Integers. A sign value of zero (0) is used to represent positive Decimal
				values and a sign value of one (1) is used to represent negative Decimal
				values The first Integer represents the integral portion of the Decimal
				value. The second positive integer represents the fractional portion of
				the decimal with the digits in reverse order to preserve leading zeros.
				It has more precision than float.
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeDecimal(bitstream_t* stream, exi_decimal_t* d);


/************************************************************************************
 * Service Name: encodeString
 * Service ID[hex]: 0x0D
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Pointer to UCS string container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode a length prefixed sequence of characters.
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeString(bitstream_t* stream, exi_string_t* string);


/************************************************************************************
 * Service Name: encodeCharacters
 * Service ID[hex]: 0x0E
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Output Stream container
 	 	 	 	 	chars  - Pointer to string character container
					len	   - Number of characters
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode a sequence of characters according to a given length.
 	 	 	 	Each character is represented by its UCS [ISO/IEC 10646]
				code point encoded as an Unsigned Integer
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeCharacters(bitstream_t* stream, exi_string_character_t* chars, size_t len);


/************************************************************************************
 * Service Name: encodeRCSCharacters
 * Service ID[hex]: 0x0F
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Output Stream container
					chars  - Pointer to string character container
					len	   - Number of characters.
					rcsCodeLength -  RCS code-length
					rcsSize       -  RCS size
					rcsSet[]	  -  RCS set Array
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode restricted character set value according to a given length.
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeRCSCharacters(bitstream_t* stream, exi_string_character_t* chars, size_t len, size_t rcsCodeLength, size_t rcsSize, const exi_string_character_t rcsSet[]);



/************************************************************************************
 * Service Name: encodeBinary
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container,Pointer to byte value container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode a binary value as a length-prefixed sequence of octets.
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeBinary(bitstream_t* stream, exi_bytes_t* bytes);


/************************************************************************************
 * Service Name: encodeBytes
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Output Stream container
 	 	 	 	 	 data  - Pointer to bytes array data container
				     len   - Bytes array length.
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode a binary value as sequence of octets.
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeBytes(bitstream_t* stream, uint8_t* data, size_t len);

/************************************************************************************
 * Service Name: encodeDateTime
 * Service ID[hex]: 0x11
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream   - Pointer to Output Stream container,
 	 	 	 	 	datetime - Pointer to date time value container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Encode a datetime representation which is a sequence of values
				representing the individual components of the Date-Time
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeDateTime(bitstream_t* stream, exi_datetime_t* datetime);


/************************************************************************************
 * Service Name: encodeFinish
 * Service ID[hex]: 0x15
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Output Stream container.
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to write the remaining bits in buffer
 * 				Flush underlying output stream.
 * Available via: EncoderChannel.h
 * Requirement:
 ************************************************************************************/
int encodeFinish(bitstream_t* stream);

#ifdef __cplusplus
}
#endif

#endif
