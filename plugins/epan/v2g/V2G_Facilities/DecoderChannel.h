/*******************************************************************
 *
 * @author : Youssef Hussien and Tasneem Essmat
 * @version 20-10-2022
 * @contact: ysfhussien@gmail.com
 *			 tasneemessmat@gmail.com
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 * File Name: DecoderChannel.h
 * Description: This is an Decoder channel containing decoding functions for every data type.
 ********************************************************************/




#ifndef DECODER_CHANNEL_H
#define DECODER_CHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------- File Includes ---------------------------------- */

#include "EXIOptions.h"
#include "EXITypes.h"

/************************************************************************************
* Service Name: decode
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to data to write decoded data in
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   general decode function that is used internally in many decoding functions
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decode(bitstream_t* stream, uint8_t* b);


/************************************************************************************
* Service Name: decodeBoolean
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to data to write decoded data in
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:  Decode boolean data type
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeBoolean(bitstream_t* stream, int* b);


/************************************************************************************
* Service Name: decodeNbitUnsignedInteger
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, number of bits to read , pointer to data to write decoded data in
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:  Decode boolean data type
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeNBitUnsignedInteger(bitstream_t* stream, size_t nbits, uint32_t* uint32);

/************************************************************************************
* Service Name: decodeUnsignedInteger
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to iv structure.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function calls the _decodeUnsignedIntegar function, by passing 0
* 			   in sign argument indication postive data
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv);


/************************************************************************************
* Service Name: decodeUnsignedInteger16
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to uint16 variable to write the decoded
* 				   data in it.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function decodes the unisgned integar 16 data type.
* 			   all the illustrated decoding steps are standarized from w3c EXI decoding.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedInteger16(bitstream_t* stream, uint16_t* uint16);

/************************************************************************************
* Service Name: decodeUnsignedInteger32
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to uint32 variable to write the decoded
* 				   data in it.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function decodes the unisgned integar 32 data type.
* 			   all the illustrated decoding steps are standarized from w3c EXI decoding.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedInteger32(bitstream_t* stream, uint32_t* uint32);

/************************************************************************************
* Service Name: decodeUnsignedIntegerSizeT
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, variable indicates the size.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function allowes decoding of variable sizes based on configurations
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedIntegerSizeT(bitstream_t* stream, size_t* sizeT);

/************************************************************************************
* Service Name: decodeUnsignedInteger64
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to uint64 variable to write the decoded
* 				   data in it.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:  Decode an arbitrary precision non negative integer using a sequence of
				octets. The most significant bit of the last octet is set to zero to
				indicate sequence termination. Only seven bits per octet are used to
				store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedInteger64(bitstream_t* stream, uint64_t* uint64);

/************************************************************************************
* Service Name: decodeUnsignedIntegerBig
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, size , pointer to array of data to write decoded data in it, leng
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedIntegerBig(bitstream_t* stream, size_t size, uint8_t* data, size_t* len);


/************************************************************************************
* Service Name: decodeInteger
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to iv structure.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function calls the _decodeUnsignedIntegar function, by passing b
* 			   in sign argument indication of the sign of the data
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeInteger(bitstream_t* stream, exi_integer_t* iv);



/************************************************************************************
* Service Name: decodeInteger16
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to int16 data.
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeInteger16(bitstream_t* stream, int16_t* int16);

/************************************************************************************
* Service Name: decodeInteger32
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to int32 data.
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeInteger32(bitstream_t* stream, int32_t* int32);


/************************************************************************************
* Service Name: decodeInteger64
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to int64 data.
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeInteger64(bitstream_t* stream, int64_t* int64);


/************************************************************************************
* Service Name: decodeIntegerBig
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to sign , size , pointer to array of data , pointer to lenght
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeIntegerBig(bitstream_t* stream, int* negative, size_t size, uint8_t* data, size_t* len);

/************************************************************************************
* Service Name: decodeFloat
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_float structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: Decode a Float datatype as two consecutive Integers.
		       The first Integer represents the mantissa of the floating point
               number and the second Integer represents the base-10 exponent
               of the floating point number.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeFloat(bitstream_t* stream, exi_float_me_t* f);


/************************************************************************************
* Service Name: decodeDecimal
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_decimal structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:  Decode a decimal represented as a Boolean sign followed by two Unsigned
 	 	 	 	Integers. A sign value of zero (0) is used to represent positive Decimal
                values and a sign value of one (1) is used to represent negative Decimal
                values The first Integer represents the integral portion of the Decimal
                value. The second positive integer represents the fractional portion of
                the decimal with the digits in reverse order to preserve leading zeros.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeDecimal(bitstream_t* stream, exi_decimal_t* d);


/************************************************************************************
* Service Name: decodeStringOnly
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, lenght of string ,pointer to exi_String_t structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode a sequence of characters for a given length.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeStringOnly(bitstream_t* stream, size_t len, exi_string_t* s);


/************************************************************************************
* Service Name: decodeString
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_String_t structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode a length prefixed sequence of characters.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeString(bitstream_t* stream, exi_string_t* s);





/************************************************************************************
* Service Name: decodeCharacters
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, lenght of characters, pointer to array of exi_characters_t , charSize
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode a sequence of characters according to a given length.
 	 	 	 	 Each character is represented by its UCS [ISO/IEC 10646]
   	   	   	     code point encoded as an Unsigned Integer
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeCharacters(bitstream_t* stream, size_t len, exi_string_character_t* chars, size_t charsSize);


/**
 * \brief 		Decode restricted character set characters
 *
 * 				Decode a sequence of characters according to a given length and rcs code-length, size and set.
 *
 * \param       stream   		Input Stream
 * \param       len		   		Length
 * \param       chars   		Characters (out)
 * \param       charsSize		Size of possible characters
 * \param       rcsCodeLength   RCS code-length
 * \param       rcsCodeLength   RCS size
 * \param       rcsCodeLength   RCS set
 * \return                  	Error-Code <> 0
 *
 */
int decodeRCSCharacters(bitstream_t* stream, size_t len, exi_string_character_t* chars, size_t charsSize, size_t rcsCodeLength, size_t rcsSize, const exi_string_character_t rcsSet[]);


/************************************************************************************
* Service Name: decodeBinary
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_bytes_t  structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode a binary value as a length-prefixed sequence of octets.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeBinary(bitstream_t* stream, exi_bytes_t* bytes);


/************************************************************************************
* Service Name: decodeBytes
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, lenght of bytes , pointer to array of data to put decoded data in
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   decode number of bytes based on thier lenght
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeBytes(bitstream_t* stream, size_t len, uint8_t* data);

/************************************************************************************
* Service Name: decodeDateTime
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_datetime_type_t enum , pointer to exi_datetime_t structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode Date-Time as sequence of values representing the individual
  	  	  	     components of the Date-Time.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeDateTime(bitstream_t* stream, exi_datetime_type_t type, exi_datetime_t* datetime);


#ifdef __cplusplus
}
#endif

#endif
