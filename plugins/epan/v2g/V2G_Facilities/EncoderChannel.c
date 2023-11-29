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
 * File Name: EncoderChannel.c
 *
 * Description: Source file of EXI EncoderChannel
 *
************************************************************************************/


/*------------------------------------- File Includes ------------------------------------- */
#include "EncoderChannel.h"
#include "EXIOptions.h"
#include "BitOutputStream.h"
#include "EXITypes.h"
#include "ErrorCodes.h"
#include "MethodsBag.h"
/*#include "v2gEXICoder.h"*/

#ifndef ENCODER_CHANNEL_C
#define ENCODER_CHANNEL_C

/*---------------------------------- APIs Implementation -----------------------------------*/

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
int encodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	/* Switching on type to call the suitable encoding function
	 *
	 * Use [encodeUnsignedInteger32] to encode the stream if the number of bits <= 32
	 * else: use [encodeUnsignedInteger64]
	 */
	switch (iv->type) {
	/* Encoding unsigned integers*/
	/* Unsigned Integer 8 bits */
	case EXI_UNSIGNED_INTEGER_8:
		errn = encodeUnsignedInteger32(stream, iv->val.uint8);
		break;
		/* Unsigned Integer 16 bits */
	case EXI_UNSIGNED_INTEGER_16:
		errn = encodeUnsignedInteger32(stream, iv->val.uint16);
		break;
		/* Unsigned Integer 32 bits */
	case EXI_UNSIGNED_INTEGER_32:
		errn = encodeUnsignedInteger32(stream, iv->val.uint32);
		break;
		/* Unsigned Integer 64 bits */
	case EXI_UNSIGNED_INTEGER_64:
		errn = encodeUnsignedInteger64(stream, iv->val.uint64);
		break;
	/* Encoding (Signed) Integers */
		/* (Signed) Integer 8 bits */
	case EXI_INTEGER_8:
		/* If it's Negative value return error */
		if (iv->val.int8 < 0) {
			return EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE;
		}
		errn = encodeUnsignedInteger32(stream, (uint32_t)(iv->val.int8));
		break;
		/* (Signed) Integer 16 bits */
	case EXI_INTEGER_16:
		/* If it's Negative value return error */
		if (iv->val.int16 < 0) {
			return EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE;
		}
		errn = encodeUnsignedInteger32(stream, (uint32_t)(iv->val.int16));
		break;
		/* (Signed) Integer 32 bits */
	case EXI_INTEGER_32:
		/* If it's Negative value return error */
		if (iv->val.int32 < 0) {
			return EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE;
		}
		errn = encodeUnsignedInteger32(stream, (uint32_t)(iv->val.int32));
		break;
		/* (Signed) Integer 64 bits */
	case EXI_INTEGER_64:
		/* If it's Negative value return error */
		if (iv->val.int64 < 0) {
			return EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE;
		}
		errn = encodeUnsignedInteger64(stream, (uint64_t)(iv->val.int64));
		break;
	default:
		/* Return error in case Integer type passed is unsupported
		 * (Length is not 8, 16,32,64) */
		errn = EXI_UNSUPPORTED_INTEGER_VALUE_TYPE;
		break;
	}

	return errn;
}
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

int encodeUnsignedInteger16(bitstream_t* stream, uint16_t streamValue) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;
	/* If value of steam less than 128 just write the byte as it as using [encode] */
	if (streamValue < 128)
	{
		errn = encode(stream, (uint8_t) streamValue);
	}
	/*If value of steam greater than or equal 128 */
	else
	{
		/*n7BitBlocks variable holding value indicating the number of blocks to encode the stream */
		uint8_t n7BitBlocks = numberOf7BitBlocksToRepresent(streamValue);

		switch (n7BitBlocks) {
		/* Stream of 21 bits (3 Blocks will be encoded)*/
		case 3:
			/* Encoding first 7 data bits */
			errn = encode(stream, (uint8_t) (128 | streamValue));

			/*Shifting the value by 7 bits to get the next octet*/
			streamValue = streamValue >> 7;

			/*Exit the function in case of failure to encode the byte */
			if (errn != 0) {
				break;
			}
			/* no break to encode rest of the stream*
			 *
			 * Stream of 14 bits (2 Blocks will be encoded)*/
		case 2:
			/* Encoding next 7 data bits in case of 21 bits stream
			 * Encoding first 7 data bits in case of 14 bits stream */
			errn = encode(stream, (uint8_t) (128 | streamValue));

			/*Shifting the value by 7 bits to get the next octet*/
			streamValue = streamValue >> 7;

			/*Exit the function in case of failure to encode the byte */
			if (errn != 0) {
				break;
			}
			/* no break to encode rest of the stream
			 *
			 * 0 .. 7 (last byte)*/
		case 1:
			/* Encoding last byte(octet) of the stream
			 * The most significant bit of the last octet is set to
			 * zero to indicate sequence termination */
			errn = encode(stream, (uint8_t) (0 | streamValue));
			/* no break */
		}
	}

	return errn;
}
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

int encodeUnsignedInteger32(bitstream_t* stream, uint32_t streamValue) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	/* If value of steam less than 128 just write the byte as it as using [encode] */
	if (streamValue < 128) {
		errn = encode(stream, (uint8_t) streamValue);
	}
	/*If value of steam greater than or equal 128 */
	else
	{
		/*n7BitBlocks variable holding value indicating the number of blocks to encode the stream */
		uint8_t n7BitBlocks = numberOf7BitBlocksToRepresent(streamValue);

		switch (n7BitBlocks) {
		/* Stream of 35 bits (5 Blocks will be encoded)*/
		case 5:
			/* Encoding first 7 data bits */
			errn = encode(stream, (uint8_t) (128 | streamValue));

			/*Shifting the value by 7 bits to get the next octet*/
			streamValue = streamValue >> 7;

			/*Exit the function in case of failure to encode the byte */
			if (errn != 0) {
				break;
			}
			/* no break to encode rest of the stream
			 *
			 * Stream of 28 bits (4 Blocks will be encoded) */
		case 4:
			/* Encoding first 7 data bits */
			errn = encode(stream, (uint8_t) (128 | streamValue));

			/*Shifting the value by 7 bits to get the next octet*/
			streamValue = streamValue >> 7;

			/*Exit the function in case of failure to encode the byte */
			if (errn != 0) {
				break;
			}
			/* no break to encode rest of the stream
			 *
			 * Stream of 21 bits (3 Blocks will be encoded) */
		case 3:
			/* Encoding first 7 data bits */
			errn = encode(stream, (uint8_t) (128 | streamValue));

			/*Shifting the value by 7 bits to get the next octet*/
			streamValue = streamValue >> 7;

			/*Exit the function in case of failure to encode the byte */
			if (errn != 0) {
				break;
			}
			/* no break to encode rest of the stream
			 *
			 * Stream of 14 bits (2 Blocks will be encoded)
			 * */
		case 2:
			/* Encoding 7 data bits */
			errn = encode(stream, (uint8_t) (128 | streamValue));

			/*Shifting the value by 7 bits to get the next octet*/
			streamValue = streamValue >> 7;
			if (errn != 0) {
				break;
			}
			/* no break to encode rest of the stream
			 *
			 * 0 .. 7 (last byte)*/
		case 1:
			/* Encoding last byte(octet) of the stream
			 * The most significant bit of the last octet is set to
			 * zero to indicate sequence termination */
			errn = encode(stream, (uint8_t) (0 | streamValue));
			/* no break */
		}
	}

	return errn;
}

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

int encodeUnsignedInteger64(bitstream_t* stream, uint64_t streamValue) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	/* lastEncode variable to hold the value of the current octet to be encoded*/
	uint8_t lastEncode = (uint8_t) streamValue;

	/*Shifting the value by 7 bits to get the next octet*/
	streamValue >>= 7;

	/*Encode while the stream is unfinished yet and No errors encountered*/
	while (streamValue != 0 && errn == 0) {

		/* Encode Current Octet */
		errn = encode(stream, lastEncode | 128);

		/*Getting Next Octet To Be Encoded*/
		lastEncode = (uint8_t) streamValue;

		/*Shifting the value by 7 bits to get the next octet*/
		streamValue >>= 7;
	}
	/*Encode Last Octet*/
	if (errn == 0) {
		errn = encode(stream, lastEncode);
	}

	return errn;
}

/************************************************************************************
 * Service Name: _shiftRight7
 * Service ID[hex]: 0x05
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to Array to be shifted right,int value holding length of the array
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to shift right the array by 7 Bits
 * Available via: EncoderChannel.h
 * Requirement:
************************************************************************************/
void _shiftRight7(uint8_t* buf, int len) {
	/*shift variable holding shift value*/
	const int shift = 7;

    unsigned char tmp = 0x00, tmp2 = 0x00;
    for (int k = 0; k <= len; k++) {
        if (k == 0) {
            tmp = buf[k];

            buf[k] >>= shift;
        } else {
            tmp2 = buf[k];
            buf[k] >>= shift;
            buf[k] |= ((tmp & 0x7F) << (8 - shift));

            if (k != len) {
                tmp = tmp2;
            }
        }
    }
}

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
int encodeUnsignedIntegerBig(bitstream_t* stream, size_t size, uint8_t* data, size_t len) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	/*Index Variable For Looping */
	int i;

	/* lenM1 variable holding total number of bytes minus 1*/
	int lenM1 = len - 1;

	/* MAX_BIGINT_ARRAY variable holding maximum size of array*/
	const int MAX_BIGINT_ARRAY = 25;

	/* lastEncode variable to hold the value of the current octet to be encoded*/
	uint8_t lastEncode = 0;

	uint8_t bytesToShift[MAX_BIGINT_ARRAY]; // MAXIMUM

	/* bitsToEncode variable holding total number of bits to be encoded*/
	size_t bitsToEncode = len * 8;

	/* Ensuring that the BigInt is less than allowed maximum length
	 * Exiting the function if's greater than or equal maximum length*/
	if(MAX_BIGINT_ARRAY <= len) {
		return -1;
	}

	/* init */
	for(i=0; i<MAX_BIGINT_ARRAY; i++) {
		bytesToShift[i] = 0;
	}

	/* copy bytes first in same order for shifting */
	for(i=0; i < len; i++) {
		bytesToShift[i] = data[i];
	}

	while(bitsToEncode > 7) {
		/* Getting Current Byte to be encoded*/
		lastEncode = bytesToShift[lenM1];

		/*Setting last bit as it's not last octet*/
		lastEncode = lastEncode | 128;

		/*Encoding Current Byte*/
		errn = encode(stream, lastEncode);

		/*Shifting bytesToShift array by 7 bits to get the next octet to be encoded*/
		_shiftRight7(bytesToShift, len);

		/*Updating total number of bits after finishing the encoding of these 7 bits*/
		bitsToEncode -= 7;
	}

	if (errn == 0) {
		/*Encoding last Octet*/
		errn = encode(stream, bytesToShift[lenM1]);
	}

	return errn;
}
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
int encodeInteger(bitstream_t* stream, exi_integer_t* iv) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	/* Switching on type to call the suitable encoding function
	 *
	 * Use [encodeInteger32] to encode the stream if the number of bits <= 32
	 * else: use [encodeInteger64]
	 */
	switch (iv->type) {
	/* Encoding Unsigned Integer */
	/* Unsigned Integer 8 bits */
	case EXI_UNSIGNED_INTEGER_8:
		errn = encodeInteger32(stream, iv->val.uint8);
		break;
		/* Unsigned Integer 16 bits */
	case EXI_UNSIGNED_INTEGER_16:
		errn = encodeInteger32(stream, iv->val.uint16);
		break;
		/* Unsigned Integer 32 bits */
	case EXI_UNSIGNED_INTEGER_32:
		errn = encodeInteger64(stream, iv->val.uint32);
		break;
		/* Unsigned Integer 64 bits */
	case EXI_UNSIGNED_INTEGER_64:
		errn = encodeInteger64(stream, (int64_t)(iv->val.uint64));
		break;
		/* Encoding (Signed) Integers */
		/* (Signed) Integer 8 bits */
	case EXI_INTEGER_8:
		errn = encodeInteger32(stream, iv->val.int8);
		break;
		/* (Signed) Integer 16 bits */
	case EXI_INTEGER_16:
		errn = encodeInteger32(stream, iv->val.int16);
		break;
		/* (Signed) Integer 32 bits */
	case EXI_INTEGER_32:
		errn = encodeInteger32(stream, iv->val.int32);
		break;
		/* (Signed) Integer 64 bits */
	case EXI_INTEGER_64:
		errn = encodeInteger64(stream, iv->val.int64);
		break;
	default:
		/* Return error in case Integer type passed is unsupported
		 * (Length is not 8, 16,32,64) */
		errn = EXI_UNSUPPORTED_INTEGER_VALUE_TYPE;
		break;
	}

	return errn;
}
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

int encodeInteger16(bitstream_t* stream, int16_t n) {
	/*errn variable to hold the error value in case of any failure*/
	int errn;

	/* signalize sign in case negative number*/
	if (n < 0) {
		/*Encoding the sign bit 1 for negative values*/
		errn = encodeBoolean(stream, 1);

		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		n = (int16_t)((-n) - 1);

	} else {
		/*Encoding the sign bit 0 for positive values*/
		errn = encodeBoolean(stream, 0);
	}
	if (errn == 0) {

		/*Encode the magnitude of the value after encoding the sign bit*/
		errn = encodeUnsignedInteger16(stream, (uint16_t)n);
	}
	return errn;
}

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

int encodeInteger32(bitstream_t* stream, int32_t n) {
	/*errn variable to hold the error value in case of any failure*/
	int errn;

	/* signalize sign in case negative number*/
	if (n < 0) {
		/*Encoding the sign bit 1 for negative values*/
		errn = encodeBoolean(stream, 1);

		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		n = (-n) - 1;
	} else {
		/*Encoding the sign bit 0 for positive values*/
		errn = encodeBoolean(stream, 0);

	}
	if (errn == 0) {
		/*Encode the magnitude of the value after encoding the sign bit*/
		errn = encodeUnsignedInteger32(stream, (uint32_t)n);
	}
	return errn;
}

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

int encodeInteger64(bitstream_t* stream, int64_t n) {
	/*errn variable to hold the error value in case of any failure*/
	int errn;

	/* signalize sign in case negative number*/
	if (n < 0) {
		/*Encoding the sign bit 1 for negative values*/
		errn = encodeBoolean(stream, 1);

		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		n = (-n) - 1;
	} else {
		/*Encoding the sign bit 0 for positive values*/
		errn = encodeBoolean(stream, 0);

	}
	if (errn == 0) {
		/*Encode the magnitude of the value after encoding the sign bit*/
		errn = encodeUnsignedInteger64(stream, (uint64_t)n);
	}
	return errn;
}

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
int encodeIntegerBig(bitstream_t* stream, int negative, size_t size, uint8_t* data, size_t len) {
	/*errn variable to hold the error value in case of any failure*/
	int errn;

	/* signalize sign in case negative number*/
	if (negative) {
		/*Encoding the sign bit 1 for negative values*/
		errn = encodeBoolean(stream, 1);

	} else {
		/*Encoding the sign bit 0 for positive values*/
		errn = encodeBoolean(stream, 0);
	}
	if (errn == 0) {
		/*Encode the magnitude of the value after encoding the sign bit*/
		errn = encodeUnsignedIntegerBig(stream, size, data, len);
	}
	return errn;
}

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
int encodeFloat(bitstream_t* stream, exi_float_me_t* f) {
	/*Encoding the mantissa*/
	int errn = encodeInteger64(stream, f->mantissa);

	if (errn == 0) {
		/*Encoding the exponent*/
		errn = encodeInteger32(stream, f->exponent);
	}
	return errn;
}

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

int encodeDecimal(bitstream_t* stream, exi_decimal_t* d) {

	int errn = encodeBoolean(stream, d->negative);

	if (errn == 0) {
		/*Encoding integral part*/
		errn = encodeUnsignedInteger(stream, &d->integral);

		if (errn == 0) {
			/*Encoding reverse fractional part to preserve leading zeros*/
			errn = encodeUnsignedInteger(stream, &d->reverseFraction);
		}
	}
	return errn;
}

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

int encodeString(bitstream_t* stream, exi_string_t* string) {
	/*Step 1 - Encoding String length */
	int errn = encodeUnsignedInteger32(stream, string->len);

	if (errn == 0) {
		/*Step 2 - Encoding Characters of The string*/
		errn = encodeCharacters(stream, string->characters, string->len);
	}
	return errn;
}

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

int encodeCharacters(bitstream_t* stream, exi_string_character_t* chars, size_t len) {
	/*Index Variable For Looping over characters*/
	unsigned int i;

	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	for (i = 0; i < len && errn == 0; i++) {
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
		errn = encode(stream, (uint8_t)chars[i]);
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
		/* Encode the UCS representation of every character till end of sequence
		 * uses four bytes (total 32 bits) to encode a single character of the codespace.
		 * UCS-4.*/
		errn = encodeUnsignedInteger32(stream, chars[i]);

#endif /* STRING_REPRESENTATION_UCS */
	}
	return errn;
}

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
int encodeRCSCharacters(bitstream_t* stream, exi_string_character_t* chars, size_t len, size_t rcsCodeLength, size_t rcsSize, const exi_string_character_t rcsSet[]) {
	unsigned int i;
	unsigned int k;
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;
	size_t rcsCode = SIZE_MAX;

	for (i = 0; i < len && errn == 0; i++) {
		/* try to find short code */
		rcsCode = SIZE_MAX;
		for(k=0; k<rcsSize && rcsCode == SIZE_MAX; k++) {
			if(rcsSet[k] == chars[i]) {
				rcsCode = k;
			}
		}

		if( rcsCode == SIZE_MAX) {

			/* RCS mis-match
			 * Characters that are not in this set are represented by the n-bit Unsigned Integer N
			 * (N is the number of characters in the restricted character set)
			 * followed by the Unicode code point of the character represented as an Unsigned Integer.
			 */
			errn = encodeNBitUnsignedInteger(stream, rcsCodeLength, rcsSize);

#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
			errn = encode(stream, (uint8_t)chars[i]);
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
			errn = encodeUnsignedInteger32(stream, chars[i]);
#endif /* STRING_REPRESENTATION_UCS */

		} else {

			/* RCS match
			 * If the resulting set of characters contains less than 256 characters and contains only BMP characters,
			 * the string value has a restricted character set and
			 * Each character is represented using an n-bit Unsigned Integer*/
			errn = encodeNBitUnsignedInteger(stream, rcsCodeLength, (uint32_t)rcsCode);
		}
	}
	return errn;
}

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
int encodeBinary(bitstream_t* stream, exi_bytes_t* bytes) {
	/*Step 1 - Encoding bytes array length */
	int errn = encodeUnsignedInteger32(stream, bytes->len);


	if(errn == 0) {
		/*Step 2 - Encoding sequence of octets*/
		errn = encodeBytes(stream, bytes->data, bytes->len);
	}

	return errn;
}

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
int encodeBytes(bitstream_t* stream, uint8_t* data, size_t len) {
	/*Index variable for looping over the octets*/
	unsigned int i;

	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	/*Encoding Sequence Of Octets Till The End Of The Array*/
	for (i = 0; i < len && errn == 0; i++) {

		/*Encode Current Octet*/
		errn = encode(stream, data[i]);

	}
	return errn;
}

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
int encodeDateTime(bitstream_t* stream, exi_datetime_t* datetime) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	switch (datetime->type) {
	case EXI_DATETIME_GYEAR: /* Year, [Time-Zone] */
		errn = encodeInteger32(stream, datetime->year - DATETIME_YEAR_OFFSET);
		break;
	case EXI_DATETIME_GYEARMONTH: /* Year, MonthDay, [TimeZone] */
	case EXI_DATETIME_DATE: /* Year, MonthDay, [TimeZone] */
		errn = encodeInteger32(stream, datetime->year - DATETIME_YEAR_OFFSET);
		if (errn == 0) {
			errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY,
					datetime->monthDay);
		}
		break;
	case EXI_DATETIME_DATETIME: /* Year, MonthDay, Time, [FractionalSecs], [TimeZone] */
		errn = encodeInteger32(stream, datetime->year - DATETIME_YEAR_OFFSET);
		if (errn == 0) {
			errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY,
					datetime->monthDay);
			if (errn != 0) {
				break;
			}
		}
		/* no break */
	case EXI_DATETIME_TIME: /* Time, [FractionalSecs], [TimeZone] */
		errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_TIME,
				datetime->time);
		if (errn == 0) {
			if (datetime->presenceFractionalSecs) {
				errn = encodeBoolean(stream, 1);
				if (errn == 0) {
					errn = encodeUnsignedInteger32(stream, datetime->fractionalSecs);
				}
			} else {
				errn = encodeBoolean(stream, 0);
			}
		}
		break;
	case EXI_DATETIME_GMONTH: /* MonthDay, [TimeZone] */
	case EXI_DATETIME_GMONTHDAY: /* MonthDay, [TimeZone] */
	case EXI_DATETIME_GDAY: /* MonthDay, [TimeZone] */
		errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY,
				datetime->monthDay);
		break;
	default:
		errn = EXI_UNSUPPORTED_DATETIME_TYPE;
		break;
	}
	if (errn == 0) {
		/* [TimeZone] */
		if (datetime->presenceTimezone) {
			errn = encodeBoolean(stream, 1);
			if (errn == 0) {
				errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_TIMEZONE,
						datetime->timezone + DATETIME_TIMEZONE_OFFSET_IN_MINUTES);
			}
		} else {
			errn = encodeBoolean(stream, 0);
		}
	}

	return errn;
}

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

int encode(bitstream_t* stream, uint8_t b) {

	/*Alignment of event codes and content items is bit-packed according to W3C EXI 1.0*/
#if EXI_OPTION_ALIGNMENT == BIT_PACKED
	return writeBits(stream, 8, b);
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */
#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	int errn = 0;
#if EXI_STREAM == BYTE_ARRAY
	if ( (*stream->pos) < stream->size ) {
		stream->data[(*stream->pos)++] = b;
	} else {
		errn = EXI_ERROR_OUTPUT_STREAM_EOF;
	}
#endif /* EXI_STREAM == BYTE_ARRAY */
#if EXI_STREAM == FILE_STREAM
	if ( putc(b, stream->file) == EOF ) {
		errn = EXI_ERROR_OUTPUT_STREAM_EOF;
	}
#endif /* EXI_STREAM == FILE_STREAM */
	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}

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
int encodeBoolean(bitstream_t* stream, int b) {

	/*Alignment of event codes and content items is bit-packed according to W3C EXI 1.0*/
#if EXI_OPTION_ALIGNMENT == BIT_PACKED
	uint8_t val = b ? 1 : 0;
	return writeBits(stream, 1, val);
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */
#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	uint8_t val = b ? 1 : 0;
	return encode(stream, val);
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}

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
int encodeNBitUnsignedInteger(bitstream_t* stream, size_t nbits, uint32_t val)  {

	/*Alignment of event codes and content items is bit-packed according to W3C EXI 1.0*/
#if EXI_OPTION_ALIGNMENT == BIT_PACKED
	int errn = 0;
	if (nbits > 0) {
		errn = writeBits(stream, nbits, val);
	}
	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */
#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	int errn = 0;
	if (nbits > 0) {
		if (nbits < 9) {
			/* 1 byte */
			errn = encode(stream, val & 0xff);
		} else if (nbits < 17) {
			/* 2 bytes */
			errn = encode(stream, val & 0x00ff);
			if(errn == 0) {
				errn = encode(stream, (uint8_t)((val & 0xff00) >> 8));
			}
		} else if (nbits < 25) {
			/* 3 bytes */
			errn = encode(stream, val & 0x0000ff);
			if(errn == 0) {
				errn = encode(stream, (uint8_t)((val & 0x00ff00) >> 8));
				if(errn == 0) {
					errn = encode(stream, (uint8_t)((val & 0xff0000) >> 16));
				}
			}
		} else if (nbits < 33) {
			/* 4 bytes */
			errn = encode(stream, val & 0x000000ff);
			if(errn == 0) {
				errn = encode(stream, (uint8_t)((val & 0x0000ff00) >> 8));
				if(errn == 0) {
					errn = encode(stream, (uint8_t)((val & 0x00ff0000) >> 16));
					if(errn == 0) {
						errn = encode(stream, (uint8_t)((val & 0xff000000) >> 24));
					}
				}
			}
		} else {
			/* TODO Currently not more than 4 Bytes allowed for NBitUnsignedInteger */
			errn = EXI_UNSUPPORTED_NBIT_INTEGER_LENGTH;
		}
	}
	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}

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
int encodeFinish(bitstream_t* stream) {
#if EXI_OPTION_ALIGNMENT == BIT_PACKED
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */
	return flush(stream);
#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	/* no pending bits in byte-aligned mode */
	return 0;
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}



#endif

